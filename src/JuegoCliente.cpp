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
	this->log = log;
	this->log->setModulo("JUEGO CLIENTE");

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
	this->log->addLogMessage("[INICIAR HILOS] Iniciado.",2);

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

	this->log->addLogMessage("[INICIAR JUEGO CLIENTE] Iniciado.",2);
	hiloJuego->Create((void *)iniciarJuegoCliente, (void *)this);

	this->log->addLogMessage("[INICIAR JUEGO CLIENTE] Terminado.",2);

	vista->mostrarEsperarJugadores(log, juegoIniciado);
	this->log->addLogMessage("[INICIAR HILOS] Terminado.",2);
}

std::string JuegoCliente::intToString(int number)
{
	ostringstream oss;
	oss<< number;
	return oss.str();
}

void JuegoCliente::terminarHilos()
{
	this->log->addLogMessage("[TERMINAR HILOS] Iniciado",2);
	//cout << "Voy a terminar el hilo juego \n";
	hiloJuego->Join();
	//cout << "Termine bien hilo juego \n";

	if(!juegoIniciado){
		std::string mensaje = MENSAJE_DESCONEXION_CLIENTE + intToString(sonic->getId());
		char buffer[LARGO_MENSAJE_POSICION_CLIENTE] = "";
		strcpy(buffer, mensaje.c_str());
		cliente->enviar(buffer, strlen(buffer));
		this->log->addLogMessage("[TERMINAR HILOS] Se desconecto el jugador "+intToString(sonic->getId()),2);
	}

	//cout << "Voy a terminar el hilo recibir \n";
	hiloRecibir->Join();
	//cout << "Voy a terminar el hilo enviar \n";
	hiloEnviar->Join();
	//cout << "Voy a terminar el hilo latidos \n";
	hiloLatido->terminarHilo();
	//cout << "Termine todos los hilos. Todo ok \n";
	this->log->addLogMessage("[TERMINAR HILOS] Terminado",2);
}

int JuegoCliente::inicializarJuegoCliente()
{
	this->log->addLogMessage("[INICIALIZAR JUEGO CLIENTE] Iniciado.",2);
	//Espera hasta recibir el primer mensaje que debe ser el id.
	std::string mensaje = hiloRecibir->obtenerElementoDeLaCola();
	while (mensaje.substr(0, 3) != MENSAJE_ID){
		mensaje = hiloRecibir->obtenerElementoDeLaCola();
		if ((mensaje.compare("Conex rechazada") == 0) || (mensaje.compare("Servidor Desconectado") == 0))
		{
			cout << "Mensaje: " << mensaje << endl;
			juegoIniciado = true; //Para que salga del menu
			this->log->addLogMessage("[INICIALIZAR JUEGO CLIENTE] Error, "+mensaje ,1);
			return CONEXION_RECHAZADA;
		}
	}

	std::string ident = mensaje.substr(3,1);
	std::string maxJug = mensaje.substr(4,1);
	int id = atoi(ident.c_str());
	maxJugadores = atoi(maxJug.c_str());

	log->addLogMessage("Se crea el personaje.",2);

	cout << "Se crea personaje con id " << id << " Max jugadores: "<< maxJugadores <<endl;
	sonic = new Personaje(id, vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log, cliente);
	this->log->addLogMessage("[INICIALIZAR JUEGO CLIENTE] Se crea personaje con id: "+sonic->intToString(sonic->getId()) ,3);

	inicializarOtrosSonics(id);
	control = new Control(0, 0, maxJugadores, &sonics, log);

	this->log->addLogMessage("[INICIALIZAR JUEGO CLIENTE] Terminado.",2);
	return 0;
}

void JuegoCliente::inicializarOtrosSonics(int id)
{
	this->log->addLogMessage("[INICIALIZAR OTROS SONICS] Iniciado.",2);
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

	this->log->addLogMessage("[INICIALIZAR  OTROS SONICS] Terminado.",2);
}

void JuegoCliente::iniciarJuegoControlCliente()
{
	this->log->addLogMessage("[INICIAR JUEGO CONTROL CLIENTE] Iniciado.",2);

	cout << "Esperando que se conecten jugadores..." << endl;
	if(!juegoIniciado){
		hiloRecibir->setVariableCondicional(&vcIniciarJuego);
		vcIniciarJuego.bloquearMutex();
		while (!juegoIniciado)
		{
			vcIniciarJuego.esperarCondicion();
			juegoIniciado = true;
		}

		vcIniciarJuego.desbloquearMutex();
		std::string mensaje = hiloRecibir->obtenerElementoDeLaCola(); //Saca el mensaje [INICIAR JUEGO] de la cola
	}
	cout << "Inicio el juego." << endl;
	control->ControlarJuegoCliente(vista, sonic, hiloEnviar, hiloRecibir, hiloLatido, opcionMenu);

	this->log->addLogMessage("[INICIAR JUEGO CONTROL CLIENTE] Iniciado.",2);
}

void JuegoCliente::CargarVistaParaElMenu(){
	this->log->addLogMessage("[CARGAR VISTA PARA EL MENU] Iniciado.",2);
	parseadorJson parseador = parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador.parsearArchivo(file);

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se inicia el menu del juego.",2);

	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, false);
	this->log->addLogMessage("[CARGAR VISTA PARA EL MENU] Terminado.",2);
}

void JuegoCliente::iniciarJuego()
{
	//Inicia el juego

	this->log->addLogMessage("[INICIAR JUEGO] Iniciado.",1);
	int result = inicializarJuegoCliente(); //Inicializa vista, sonic y control.
	if (result == CONEXION_RECHAZADA)
	{
		cout << "[JUEGO CLIENTE] Conexion rechazada. El cliente se cerrara." << endl;
		log->addLogMessage("[JUEGO CLIENTE] Error. Conexion rechazada. Se termina el juego.",1);
		return;
	}

	log->addLogMessage("Se inicia el juego.",1);
	iniciarJuegoControlCliente();

	this->log->addLogMessage("[INICIAR JUEGO] Terminado.",1);
}

int JuegoCliente::elegirOpcionDeMenu(Logger *log){
	return this->vista->mostraMenuInicial(log);
}

Personaje* JuegoCliente::getSonic(){
	return sonic;
}
