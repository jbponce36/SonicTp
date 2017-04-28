/*
 * Juego.cpp
 *
 *  Created on: 22 abr. 2017
 *      Author: julieta
 */

#include "JuegoCliente.h"

JuegoCliente::JuegoCliente()
: vista(NULL), sonic(NULL), control(NULL), cliente(NULL), log(NULL),
  hiloRecibir(NULL), hiloEnviar(NULL), hiloJuego(NULL){
	//Las variables se setean al llamar a iniciarJuegoCliente desde el thread
}

JuegoCliente::~JuegoCliente() {
	delete vista;
	delete sonic;
	delete control;
}

JuegoCliente::JuegoCliente(ConexCliente *cliente, Logger *log)
: vista(NULL), sonic(NULL), control(NULL), cliente(cliente), log(log),
  hiloRecibir(NULL), hiloEnviar(NULL), hiloJuego(NULL){
	//Vista, sonic y control se setean al llamar a iniciarJuegoCliente desde el thread
}

void *JuegoCliente::iniciarJuegoCliente(void *datos)
{
	//struct Datos* misDatos = (struct Datos*)datos;
	//JuegoCliente juego = JuegoCliente(misDatos->cliente, misDatos->log);
	JuegoCliente *juego = (JuegoCliente*)datos;
	juego->iniciarJuego();
}

void JuegoCliente::iniciarHilos()
{
	hiloRecibir = new HiloRecibirCliente();
	hiloRecibir->parametros.cliente = cliente;
	hiloRecibir->parametros.continuar = true;
	hiloRecibir->IniciarHilo();

	hiloEnviar = new HiloEnviarCliente();
	hiloEnviar->parametros.cliente = cliente;
	hiloEnviar->IniciarHilo();

	hiloJuego = new Hilo();

	//struct Datos datos;
	//datos.cliente = cliente;
	//datos.log = log;

	hiloJuego->Create((void *)iniciarJuegoCliente, (void *)this);
}

void JuegoCliente::terminarHilos()
{
	hiloJuego->Join();
	//hiloRecibir->Join();
	//hiloEnviar->Join();
}

void JuegoCliente::inicializarJuegoCliente(/*std::jescenarioJuego *jparseador*/)
{
	//vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, false);

	sonic = new Personaje(1, vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario(), log);
	//Pasarle el id correcto, no 1!!
	control = new Control(0, 0, log);
}

void JuegoCliente::iniciarJuegoControlCliente()
{
	control->ControlarJuegoCliente(vista, sonic, cliente);
}

//se agrego esto para poder la vista afuera y poder usar el menu
void JuegoCliente::CargarVistaParaElMenu(){
	parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se inicia el juego.",1);

	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, false);
}

void JuegoCliente::iniciarJuego()
{
	//------------esto se cambio al metodo CargarVistaParaElMenu()-------------
	//Se leen los datos del json
	/*parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se inicia el juego.",1);*/
	//----------------------------------------------------

	//Inicia el juego
	inicializarJuegoCliente(/*jparseador*/); //Inicializa vista, sonic y control.

	iniciarJuegoControlCliente();

	log->setModulo("JUEGO_CLIENTE");
	log->addLogMessage("Se termina el juego.",1);
}

int JuegoCliente::elegirOpcionDeMenu(Logger *log){
	return this->vista->mostraMenuInicial(log);
}
