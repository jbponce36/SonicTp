/*
 * JuegoCliente.cpp
 *
 *  Created on: 22 abr. 2017
 *      Author: julieta
 */

#include "JuegoCliente.h"

JuegoCliente::~JuegoCliente() {
	cout << "vista\n";
	if(vista != NULL)
		delete vista;
	cout << "control\n";
	if(control != NULL)
		delete control;

	cout << "hiloJuego\n";
	if(hiloJuego != NULL)
		delete hiloJuego;
	cout << "hiloRecibir \n";
	if(hiloRecibir != NULL)
		delete hiloRecibir;
	cout << "hiloEnviar \n";
	if(hiloEnviar != NULL)
		delete hiloEnviar;

	cout << "sonics\n";
	if(!sonics.empty()){
		std::vector<Personaje*>::iterator pos;
		for(pos = sonics.begin();pos != sonics.end();pos++){
			cout << (*pos)->getId() <<"\n";
			delete (*pos);
		}
	}
}

JuegoCliente::JuegoCliente(ConexCliente *cliente, Logger *log, int &opcionMenu)
: vista(NULL), sonic(NULL), control(NULL), cliente(cliente), log(log),
  hiloRecibir(NULL), hiloEnviar(NULL), hiloJuego(NULL), maxJugadores(0), sonics(),
  juegoIniciado(false), opcionMenu(opcionMenu){
	//Vista, sonic y control se setean al llamar a iniciarJuegoCliente desde el thread

	CargarVistaParaElMenu();
}

void *JuegoCliente::iniciarJuegoCliente(void *datos)
{
	//Thread que inicia iniciar juego
	JuegoCliente *juego = (JuegoCliente*)datos;
	juego->iniciarJuego();
	return NULL;
}

void JuegoCliente::iniciarHilos()
{
	juegoIniciado = false;

	hiloRecibir = new HiloRecibirCliente();
	hiloRecibir->parametros.cliente = cliente;
	hiloRecibir->parametros.continuar = true;
	//hiloRecibir->parametros.alc = alc;
	hiloRecibir->IniciarHilo();

	hiloEnviar = new HiloEnviarCliente();
	//hiloEnviar->parametros.alc=alc;
	hiloEnviar->parametros.cliente = cliente;
	hiloEnviar->iniciarHiloQueue();

	hiloLatido = new HilolatidoSer();
	hiloLatido->parametros.cliente = cliente;
	hiloLatido->IniciarHilo();


	hiloJuego = new Hilo();

	hiloJuego->Create((void *)iniciarJuegoCliente, (void *)this);

	vista->mostrarEsperarJugadores(log, juegoIniciado);
}

std::string intToString(int number)
{
	ostringstream oss;
	oss<< number;
	return oss.str();
}

void JuegoCliente::terminarHilos()
{
	cout << "Voy a terminar el hilo juego \n";
	hiloJuego->Join();
	cout << "Termine bien hilo juego \n";

	if(!juegoIniciado){
		std::string mensaje = MENSAJE_DESCONEXION_CLIENTE + intToString(sonic->getId());
		char buffer[LARGO_MENSAJE_POSICION_CLIENTE] = "";
		strcpy(buffer, mensaje.c_str());
		cliente->enviar(buffer, strlen(buffer));
	}
	cout << "Voy a terminar el hilo recibir \n";
	hiloRecibir->Join();
	cout << "Voy a terminar el hilo enviar \n";
	hiloEnviar->Join();
	cout << "Voy a terminar el hilo latidos \n";
	hiloLatido->terminarHilo();
	cout << "Termine todos los hilos. Todo ok \n";
}

int JuegoCliente::inicializarJuegoCliente()
{
	//Espera hasta recibir el primer mensaje que debe ser el id.
	std::string mensaje = hiloRecibir->obtenerElementoDeLaCola();
	while (mensaje.substr(0, 3) != MENSAJE_ID){
		mensaje = hiloRecibir->obtenerElementoDeLaCola();
		if ((mensaje.compare("Conex rechazada") == 0) || (mensaje.compare("Servidor Desconectado") == 0))
		{
			cout << "Mensaje: " << mensaje << endl;
			juegoIniciado = true; //Para que salga del menu
			return CONEXION_RECHAZADA;
		}
	}

	std::string ident = mensaje.substr(3,1);
	std::string maxJug = mensaje.substr(4,1);
	int id = atoi(ident.c_str());
	maxJugadores = atoi(maxJug.c_str());

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se crea el personaje.",2);

	cout << "Se crea personaje con id " << id << " Max jugadores: "<< maxJugadores <<endl;
	sonic = new Personaje(id, vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log, cliente);

	inicializarOtrosSonics(id);
	control = new Control(0, 0, maxJugadores, &sonics, log);

	return 0;
}

void JuegoCliente::inicializarOtrosSonics(int id)
{
	int idPropio = sonic->getId();

	for (int i = 1; i < idPropio; i++)
	{
		Personaje *otroSonic = new Personaje(i, vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log);
		sonics.push_back(otroSonic);
	}

	sonics.push_back(sonic);

	for (int i = idPropio+1; i <= maxJugadores; i++)
	{
		Personaje *otroSonic = new Personaje(i, vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log);
		sonics.push_back(otroSonic);
	}


}

void JuegoCliente::iniciarJuegoControlCliente()
{
	cout << "Esperando que se conecten jugadores..." << endl;
	hiloRecibir->setVariableCondicional(&vcIniciarJuego);
	vcIniciarJuego.bloquearMutex();
	while (!juegoIniciado)
	{
		vcIniciarJuego.esperarCondicion();
		juegoIniciado = true;
	}

	vcIniciarJuego.desbloquearMutex();
	std::string mensaje = hiloRecibir->obtenerElementoDeLaCola(); //Saca el mensaje [INICIAR JUEGO] de la cola

	cout << "Inicio el juego." << endl;
	control->ControlarJuegoCliente(vista, sonic, hiloEnviar, hiloRecibir, hiloLatido, opcionMenu);
}

void JuegoCliente::CargarVistaParaElMenu(){
	parseadorJson parseador = parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador.parsearArchivo(file);

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se inicia el menu del juego.",2);

	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, false);

}

void JuegoCliente::iniciarJuego()
{
	//Inicia el juego
	int result = inicializarJuegoCliente(); //Inicializa vista, sonic y control.
	if (result == CONEXION_RECHAZADA)
	{
		cout << "[JUEGO CLIENTE] Conexion rechazada. El cliente se cerrara..." << endl;
		log->setModulo("JUEGO_CLIENTE");
		log->addLogMessage("Error. Conexion rechazada. Se termina el juego.",1);
		return;
	}

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se inicia el juego.",1);

	iniciarJuegoControlCliente();

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se termina el juego.",1);
}

int JuegoCliente::elegirOpcionDeMenu(Logger *log){
	return this->vista->mostraMenuInicial(log);
}
