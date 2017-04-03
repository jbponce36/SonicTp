#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <jansson.h>
#include <string.h>
#include "VistaSDL.h"
#include "Textura.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"
#include "jventana.h"
#include "Rectangulo.h"
#include "Circulo.h"
#include "jescenario.h"
#include "ConstructorEntidades.h"
#include "Logger.h"
#include "jpruebas.h"
#include "Personaje.h"
#include "Control.h"

#define MODULO 'PRINCIPAL'
using namespace std;

int getNivelLogger(int argc, char *argv[]){
	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO

	char *nivelLog = (char*)"2";
	if(argc>1){
		nivelLog = argv[1];
	}

	char *nivel= (char*)nivelLog;
	return atoi(nivel);
}

int main(int argc, char *argv[]) {

	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "PRINCIPAL");
	log->iniciarLog();

	//Se lee del json el nombre de la ventana
	parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
    jescenarioJuego* jparseador = parseador->parsearArchivo(file);

    //jpruebas* jpru = new jpruebas();
    //jpru->prueba(jparseador);

    log->setModulo("PRINCIPAL");
	log->addLogMessage("Se empieza a cargar la vista.",1);
    VistaSDL *vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log);

	Personaje *sonic = new Personaje(vista->obtenerVelocidadDeScroll(),vista->obtenerRender(),vista->obtenerAltoEscenario());
    Control *control = new Control(0, 0);
    control->ControlarJuego(vista,sonic);

	parseador->getLog()->addLogMessage("Se termina de cargar la vista.",1);
	vista->cerrar();
	log->iniciarLog();

	return 0;
}
