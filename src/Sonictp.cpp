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
#include "Juego.h"
#include "Hilo.h"

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

void *iniciarJuegoCliente(void *datos)
{
	Juego *juego = (Juego*)datos;
	juego->iniciarJuego();
	return NULL;
}

int main(int argc, char *argv[]) {

	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv), "PRINCIPAL");
	log->iniciarLog("INICIAR LOGGER");

/*<--------------------------------------------->*/
	ConexCliente cliente = ConexCliente(log);

	/*<------Aca van las cosas de conectar y eso------*/

	Juego juego = Juego(&cliente, log);
	juego.iniciarJuego();

	//Creo que asi se llamaria desde un hilo llamando a la funcion de arriba del main
	//Hilo hilo = Hilo();
	//hilo.Create((void *)iniciarJuegoCliente, (void*)&juego);

	delete log;
	return 0;
}
