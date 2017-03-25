#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
using namespace std;
#include <string>
#include "VistaSDL.h"
#include "Textura.h"


#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include "Personaje.h"

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
int main( int argc, char* args[] )
{
	/*SDL_Window *ventana=SDL_CreateWindow( "SONIC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGO_VENTANA, ANCHO_VENTANA, SDL_WINDOW_SHOWN );;
	SDL_Renderer *render= SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );;
	Personaje sonic=Personaje();
	Ctextura texturaSonic=Ctextura();
	texturaSonic.cargarImagen("sonicSprite.bmp",render);
	Ctextura texturaMapa=Ctextura();
	texturaMapa.cargarImagen("sonic2.png",render);

	//Main loop flag
	bool quit = false;

	SDL_Event e;

	SDL_Rect camera = { 0, 0, LARGO_VENTANA, ANCHO_VENTANA };

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			//Handle input for the dot
			sonic.handleEvent( e );
		}

		//Move the dot
		sonic.move();

		//Center the camera over the dot
		camera.x = ( sonic.getPosicionX() + sonic.getLargo() / 2 ) - LARGO_VENTANA / 2;
		camera.y = ( sonic.getPosicionY() + sonic.getAncho() / 2 ) - ANCHO_VENTANA / 2;

		//Keep the camera in bounds
		if( camera.x < 0 )
		{
			camera.x = 0;
		}
		if( camera.y < 0 )
		{
			camera.y = 0;
		}
		if( camera.x > MAXIMO_LARGO - camera.w )
		{
			camera.x = MAXIMO_LARGO - camera.w;
		}
		if( camera.y > MAXIMO_ANCHO - camera.h )
		{
			camera.y = MAXIMO_ANCHO - camera.h;
		}

		//Clear screen
		SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( render );

		//dibujo la primera capa
		texturaMapa.render( 0, 0, render,&camera );

		//dibujo ek personaje
		sonic.render( camera.x, camera.y,texturaSonic,render );

		//muestro la imagen
		SDL_RenderPresent( render );
	}
	texturaMapa.free();
	texturaSonic.free();

	SDL_DestroyRenderer(render);
	SDL_DestroyWindow( ventana);
	render=NULL;
	ventana=NULL;*/


	 VistaSDL *vista = new VistaSDL();
	vista->cargarTexturas();
	vista->mostrarVentana();
	vista->cerrar();

	return 0;
}
