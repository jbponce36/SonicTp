#include "Entidad.h"
#define MODULO 'ENTIDAD'

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

int Entidad::cargarImagen(SDL_Renderer *renderer, Logger *log)
{
	int error = 0;
	if ((rutaImagen != "") && (imagen != NULL))
	{
		//Imagen ya cargada
		return error;
	}

	SDL_Surface *imagenCargada = NULL;
	std::string rutaSinBarra;
	const char* barra = "/";

	//Si la rutaImagen empieza con una / se la saca
	if (strncmp(rutaImagen.c_str(), barra, 1) == 0)
	{
		rutaSinBarra = rutaImagen.substr(1, rutaImagen.length() - 1);
		imagenCargada=IMG_Load(rutaSinBarra.c_str());
	}
	else
	{
		imagenCargada=IMG_Load(rutaImagen.c_str());
	}

	if(imagenCargada == NULL)
	{
		//std::cout << "Error: " << SDL_GetError() << std::endl;
		rutaImagen = "images/default.png";
		imagenCargada=IMG_Load(rutaImagen.c_str());

		std::string mensaje = "[CARGAR IMAGEN ENTIDAD] Se cargo una imagen por default. Id: "+id;
		log->addLogMessage(mensaje, 2);

		error = 1;
	}

	imagen = SDL_CreateTextureFromSurface(renderer, imagenCargada);
	SDL_FreeSurface(imagenCargada);

	return error;
}

Logger *Entidad::getLog() const
{
    return log;
}

void Entidad::setLog(Logger *log)
{
    this->log = log;
    this->log->setModulo("ENTIDAD");
}

void Entidad::destruirImagen()
{
	if (imagen != NULL)
	{
		SDL_DestroyTexture(imagen);
	}
}

bool Entidad::indexZMenorA(const Entidad *otraEntidad) const
{
	if (indexZ < otraEntidad->indexZ)
	{
		return true;
	}
	return false;
}

