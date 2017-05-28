#include "Circulo.h"

namespace std{

Circulo::Circulo() : radio()
{

}

Circulo::Circulo(int radio, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log)
: Entidad(id, color, rutaImagen, x, y, indexZ, log), radio(radio)
{
	getLog()->setModulo("CIRCULO");
}

Circulo::~Circulo()
{
	destruirTexturas();
}

void Circulo::dibujar(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (tieneRutaImagen())
	{
		if (texturaImagen == NULL)
		{
			crearImagen(renderer);
		}
		dibujarImagen(renderer, camara, texturaImagen);
	}
	else
	{
		if (texturaColor == NULL)
		{
			crearImagenColorSolido(renderer);
		}
		dibujarImagen(renderer, camara, texturaColor);
	}
}

void Circulo::dibujarImagen(SDL_Renderer *renderer, SDL_Rect *camara, SDL_Texture *textura)
{
	int diametro = radio*2;
	SDL_Rect destino = {obtenerX() - camara->x - radio, obtenerY() - camara->y - radio, diametro, diametro};
	SDL_RenderCopy(renderer, textura, NULL, &destino);
}

void Circulo::crearImagen(SDL_Renderer *renderer)
{
	int diametro=radio*2;
	int difX, difY=0;
	SDL_Rect puntoADibujar = {0, 0, 0, 0};
	SDL_Rect puntoDestino = {0, 0, 0, 0};

	int  anchoImagen, altoImagen;
	SDL_QueryTexture(obtenerImagen(), NULL, NULL, &anchoImagen, &altoImagen);

	texturaImagen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, radio*2, radio*2);
	SDL_SetTextureBlendMode(texturaImagen, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, texturaImagen);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	setearColor(renderer);

	//Para cada punto dentro del cuadrado que encierra al circulo
	for (int xPunto=0; xPunto<diametro; xPunto++)
	{
		for (int yPunto=0; yPunto<diametro; yPunto++)
		{
			if((obtenerX()-radio+xPunto >= 0) && (obtenerY()-radio+yPunto >= 0))
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

					puntoDestino.x = xPunto;
					puntoDestino.y = yPunto;
					puntoDestino.w = 1;
					puntoDestino.h = 1;

					if ((xPunto <= anchoImagen) && (yPunto <= altoImagen))
					{
						SDL_SetRenderTarget(renderer, texturaImagen);
						SDL_RenderCopy(renderer, obtenerImagen(), &puntoADibujar, &puntoDestino);
					}
					else
					{
						SDL_SetRenderTarget(renderer, texturaImagen);
						SDL_RenderDrawPoint(renderer, puntoDestino.x, puntoDestino.y);
					}
				}
			}
		}
	}
	SDL_SetRenderTarget(renderer, NULL);

}

void Circulo::crearImagenColorSolido(SDL_Renderer *renderer)
{
	int diametro=radio*2;
	int difX, difY=0;

	texturaColor = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, radio*2, radio*2);
	SDL_SetTextureBlendMode(texturaColor, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, texturaColor);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	setearColor(renderer);

	//Para cada punto dentro del cuadrado que encierra al circulo
	for (int xPunto=0; xPunto<diametro; xPunto++)
	{
		for (int yPunto=0; yPunto<diametro; yPunto++)
		{
			if((obtenerX()-radio+xPunto >= 0) && (obtenerY()-radio+yPunto >= 0))
			{
				difX=radio-xPunto;
				difY=radio-yPunto;
				if ((difX*difX + difY*difY) <= (radio*radio)) //Si el punto esta dentro del circulo
				{
					SDL_RenderDrawPoint(renderer, xPunto, yPunto);
				}
			}
		}
	}
	SDL_SetRenderTarget(renderer, NULL);

}

void Circulo::destruirTexturas()
{
	if (texturaColor != NULL)
	{
		SDL_DestroyTexture(texturaColor);
	}

	if (texturaColor != NULL)
	{
		SDL_DestroyTexture(texturaImagen);
	}
}

int Circulo::getRadio() const
{
	return radio;
}

std::string Circulo::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

string Circulo::toString(){
	return "id: "+intToString(getId())+" ," +"dimesiones-> radio:"+ intToString(getRadio())+
			", coordenadas-> x:"+intToString(getX())+
		", y: "+intToString(getY())+", index_z: "+ intToString(getIndexZ())+", ruta_imagen: "+ getRutaImagen();
}

SDL_Rect Circulo::obtenerLimites()
{
	SDL_Rect limites = { obtenerX() - radio, obtenerY() - radio, 2*radio, 2*radio};
	return limites;
}

void Circulo::interactuar(Personaje *sonic, Mundo* mundo)
{
	return; //Si la entidad es solo un Circulo, no hace nada
}

}
