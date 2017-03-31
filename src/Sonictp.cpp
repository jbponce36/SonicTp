#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <jansson.h>
#include <string>
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
using namespace std;


int main(int argc, char *argv[]) {

	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO
	char *nivelLog = (char*)"2";
	if(argc>1){
		nivelLog = argv[1];
	}

	char *archivoLog=(char*)"configuracion/log.txt";
	char *nivel= (char*)nivelLog;
	Logger *log = new Logger(archivoLog, atoi(nivel));

	//Se lee del json el nombre de la ventana
	parseadorJson* parseador = new parseadorJson(log);
	//jescenarioJuego* jparseador = parseador.
	char *file=(char*)"configuracion/configuracion.json";
	parseador->getLog()->addLogMessage("PRINCIPAL","Se inicia el juego.",1);
    jescenarioJuego* jparseador = parseador->parsearArchivo(file);

    VistaSDL *vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log);

    Personaje *sonic = new Personaje(vista->obtenerVelocidadDeScroll(),vista->obtenerRender());
    Control *control = new Control(0, 0);

    control->ControlarJuego(vista,sonic);


	vista->cerrar();
	parseador->getLog()->addLogMessage("PRINCIPAL","Se termina el juego.",1);

	return 0;
}
