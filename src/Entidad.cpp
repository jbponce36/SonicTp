#include "Entidad.h"

Entidad::Entidad() : id(), rutaImagen(""), x(), y(), indexZ(), imagen(NULL)
{

}

Entidad::Entidad(unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ)
: id(id), rutaImagen(rutaImagen), x(x), y(y), indexZ(indexZ), imagen(NULL)
{
	SDL_Color colorSDL = convertirColor(color);
	this->color=colorSDL;
}

Entidad::~Entidad()
{
	destruirImagen();
}

SDL_Color Entidad::convertirColor(std::string color)
{
	SDL_Color colorSDL = {0, 0, 0, 0};
	if (color == "amarillo"){
		colorSDL.r = 255; colorSDL.g = 255; colorSDL.b = 0; colorSDL.a = 255;
	}
	else if (color == "azul"){
		colorSDL.r = 0; colorSDL.g = 0; colorSDL.b = 255; colorSDL.a = 255;
	}
	else if (color == "rojo"){
		colorSDL.r = 255; colorSDL.g = 0; colorSDL.b = 0; colorSDL.a = 255;
	}
	else if (color == "verde"){
		colorSDL.r = 0; colorSDL.g = 255; colorSDL.b = 0; colorSDL.a = 255;
	}
	else
	{
		//Color por default: azul
		colorSDL.r = 0; colorSDL.g = 0; colorSDL.b = 255; colorSDL.a = 255;
	}
	return colorSDL;
}

void Entidad::setearColor(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

int Entidad::obtenerX()
{
	return x;
}

int Entidad::obtenerY()
{
	return y;
}

SDL_Texture* Entidad::obtenerImagen()
{
	return imagen;
}

bool Entidad::tieneRutaImagen()
{
	if (rutaImagen == "")
		return false;
	else
		return true;
}

int Entidad::cargarImagen(SDL_Renderer *renderer)
{
	if ((rutaImagen != "") && (imagen != NULL))
	{
		//Imagen ya cargada
		return 0;
	}

	SDL_Surface *imagenCargada = NULL;
/////////////////TODO: Ver si tiene la / adelante de la ruta. Sacarla
	imagenCargada=IMG_Load(rutaImagen.c_str()); //SDL_LoadBMP(rutaImagen.c_str()); //Para cargar BMP

	if(imagenCargada == NULL)
	{
		std::cout << "Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	imagen = SDL_CreateTextureFromSurface(renderer, imagenCargada);
	SDL_FreeSurface(imagenCargada);

	return 0;
}

void Entidad::destruirImagen()
{
	if (imagen != NULL)
	{
		SDL_DestroyTexture(imagen);
	}
}


