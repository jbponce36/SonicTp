#include "Circulo.h"

namespace std{

Circulo::Circulo() : radio()
{

}

Circulo::Circulo(int radio, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ)
: Entidad(id, color, rutaImagen, x, y, indexZ), radio(radio)
{

}

Circulo::~Circulo() {
	// TODO Auto-generated destructor stub
}

void Circulo::dibujar(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (tieneRutaImagen())
	{
		cargarImagen(renderer);
		dibujarImagen(renderer);
	}
	else
	{
		dibujarColorSolido(renderer);
	}
}

void Circulo::dibujarColorSolido(SDL_Renderer *renderer)
{
	setearColor(renderer);
	int diametro=radio*2;
	int difX, difY=0;

	//Para cada punto dentro del cuadrado que encierra al circulo
	for (int xPunto=0; xPunto<diametro; xPunto++)
	{		for (int yPunto=0; yPunto<diametro; yPunto++)
		{
			difX=radio-xPunto;
			difY=radio-yPunto;
			if ((difX*difX + difY*difY) <= (radio*radio)) //Si el punto esta dentro del circulo
			{
				SDL_RenderDrawPoint(renderer, obtenerX()+difX, obtenerY()+difY);
			}
		}
	}
}

void Circulo::dibujarImagen(SDL_Renderer *renderer)
{
	int diametro=radio*2;
	int difX, difY=0;
	SDL_Rect puntoADibujar = {0, 0, 0, 0};
	SDL_Rect puntoDestino = {0, 0, 0, 0};

	int  anchoImagen, altoImagen;
	SDL_QueryTexture(obtenerImagen(), NULL, NULL, &anchoImagen, &altoImagen);

	setearColor(renderer);

	//Para cada punto dentro del cuadrado que encierra al circulo
	for (int xPunto=0; xPunto<diametro; xPunto++)
	{
		for (int yPunto=0; yPunto<diametro; yPunto++)
		{
			difX=radio-xPunto;
			difY=radio-yPunto;
			if ((difX*difX + difY*difY) <= (radio*radio)) //Si el punto esta dentro del circulo
			{
				 //Empieza desde la esquina superior izquierda de la imagen
				puntoADibujar.x = xPunto;
				puntoADibujar.y = yPunto;
				puntoADibujar.w = 1;
				puntoADibujar.h = 1;

				puntoDestino.x = obtenerX()-radio+xPunto;
				puntoDestino.y = obtenerY()-radio+yPunto;
				puntoDestino.w = 1;
				puntoDestino.h = 1;

				if ((xPunto <= anchoImagen) && (yPunto <= altoImagen))
				{
					SDL_RenderCopy(renderer, obtenerImagen(), &puntoADibujar, &puntoDestino);
				}
				else
				{
					SDL_RenderDrawPoint(renderer, puntoDestino.x, puntoDestino.y);
				}
			}
		}
	}
}

}
