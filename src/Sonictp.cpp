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
#include "Personaje.h"
#include "Control.h"
using namespace std;
/*
const int MAXIMO_LARGO = 8098;
const int MAXIMO_ANCHO = 1280;
const int LARGO_VENTANA=640;
const int ANCHO_VENTANA=480;

//cambiar despues a una funcion q tenga a toda la vista
bool inicializacion(SDL_Renderer *render, SDL_Window *ventana){
	bool inicializacionCorrecta = true;

	//se fija si se pudo inicializar la libreria SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "no se pudo inicializar SDL: %s\n", SDL_GetError() );
		inicializacionCorrecta = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( " no se pudo habilitgar el filtrado de textura" );
		}

		//crea la ventana
		ventana = SDL_CreateWindow( "SONIC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGO_VENTANA, ANCHO_VENTANA, SDL_WINDOW_SHOWN );
		if( ventana  == NULL )
		{
			printf( "no se pudo crear la ventana, SDL Error: %s\n", SDL_GetError() );
			inicializacionCorrecta = false;
		}
		else
		{
			//asocia la ventana al render(pantalla)
			render = SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( render == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				inicializacionCorrecta = false;
			}
			else
			{
				//inicializa el color de dibujo
				SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );

				//Inicializa la libreria SDL_image
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "error en inicializacion libreria SDL_image : %s\n", IMG_GetError() );
					inicializacionCorrecta = false;
				}
			}
		}
	}

	return inicializacionCorrecta;
}
*/
int main(int argc, char *argv[]) {

	//SE LEE DE LOS ARGUMENTOS EL NIVEL DE LOG, SI NO ESTA, EMPIEZA A LOGGEAR EN MODO MEDIO
	char *nivelLog = (char*)"2";
	if(argc>1){
		nivelLog = argv[1];
	}

	char *archivoLog=(char*)"configuracion/log.txt";
	char *nivel= (char*)nivelLog;
	Logger *log = new Logger(archivoLog, atoi(nivel));
	log->addLogMessage("JSON", "Se empieza a leer el archivo de confiuracion");

	//Se lee del json el nombre de la ventana
	parseadorJson* parseador = new parseadorJson();
	//jescenarioJuego* jparseador = parseador.
	char *file=(char*)"configuracion/configuracion.json";
    jescenarioJuego* jparseador = parseador->parsearArchivo(file);
    VistaSDL *vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario());
    Personaje *sonic = new Personaje(vista->obtenerVelocidadDeScroll());
    Control *control = new Control(0, 0);
    control->ControlarJuego(vista,sonic);


    //Se muestran las entidades
    list<Rectangulo> rectangulos;
    list<Circulo> circulos;
    ConstructorEntidades constructorEntidades = ConstructorEntidades(jparseador->getEscenario(), &rectangulos, &circulos);

    //vista->cargarTexturas();
	//vista->mostrarVentana();
	vista->cerrar();

	return 0;
}
