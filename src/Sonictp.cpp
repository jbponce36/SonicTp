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


int main(int argc, char *argv[]) {

	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO
	char *nivelLog = (char*)"2";
	if(argc>1){
		nivelLog = argv[1];
	}

	char *archivoLog=(char*)"configuracion/log.txt";
	char *nivel= (char*)nivelLog;
	Logger *log = new Logger(archivoLog, atoi(nivel), "PRINCIPAL");

	//Se lee del json el nombre de la ventana
	parseadorJson* parseador = new parseadorJson(log);


	char *file=(char*)"configuracion/configuracion.json";
	parseador->getLog()->addLogMessage("Se inicia el juego.",1);
    jescenarioJuego* jparseador = parseador->parsearArchivo(file);

    jpruebas* jpru = new jpruebas();
    jpru->prueba(jparseador);

    VistaSDL *vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log);

    Personaje *sonic = new Personaje(vista->obtenerVelocidadDeScroll(),vista->obtenerRender());
    parseador->getLog()->setModulo("PRINCIPAL");
	parseador->getLog()->addLogMessage("Se carga la vista.",1);
    Control *control = new Control(0, 0);

    control->ControlarJuego(vista,sonic);


	vista->cerrar();
	parseador->getLog()->addLogMessage("Se termina el juego.",1);

	return 0;
}
