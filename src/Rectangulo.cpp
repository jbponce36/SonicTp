#include "Rectangulo.h"

namespace std{

Rectangulo::Rectangulo() : ancho(), alto()
{

}

Rectangulo::Rectangulo(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ)
: Entidad(id, color, rutaImagen, x, y, indexZ), ancho(ancho), alto(alto)
{
	this->rectanguloSDL.x = x;
	this->rectanguloSDL.y = y;
	this->rectanguloSDL.w = ancho;
	this->rectanguloSDL.h = alto;
}

Rectangulo::~Rectangulo() {
	// TODO Auto-generated destructor stub
}

void Rectangulo::dibujar(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (tieneRutaImagen())
	{
		mostrarImagen(renderer, camara);
	}
	else
	{
		setearColor(renderer);
		SDL_RenderFillRect(renderer, &rectanguloSDL);
	}
}

    Logger *Rectangulo::getLog() const
    {
        return log;
    }

    void Rectangulo::setLog(Logger *log)
    {
        this->log = log;
        this->log->setModulo("RECTANGULO");
    }

void Rectangulo::mostrarImagen(SDL_Renderer *renderer, SDL_Rect *camara)
{
	if (obtenerImagen() == NULL)
	{
		std::cout << "No se cargo la imagen" << std::endl;
		return;
	}

	int  anchoImagen, altoImagen;
	SDL_QueryTexture(obtenerImagen(), NULL, NULL, &anchoImagen, &altoImagen);

	if ((anchoImagen >= ancho) && (altoImagen >= alto))
	{
		//Recorta la imagen
		SDL_Rect recorte = {0, 0, ancho, alto}; //Toma desde la esquina superior izquierda de la imagen
		SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, ancho, alto};
		SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
		return;
	}
	else
	{
		setearColor(renderer);

		if (ancho > anchoImagen)
		{
			//Rellena a la derecha de la imagen
			SDL_Rect relleno = {obtenerX() + anchoImagen - camara->x, obtenerY() - camara->y, ancho - anchoImagen, alto};
			SDL_RenderFillRect(renderer, &relleno);
		}

		if (alto > altoImagen)
		{
			//Rellena abajo de la imagen
			SDL_Rect relleno = {obtenerX() - camara->x, obtenerY() + altoImagen - camara->y, ancho, alto - altoImagen};
			SDL_RenderFillRect(renderer, &relleno);
		}

		//Muestra la imagen
		if ((ancho > anchoImagen) && (alto > altoImagen))
		{
			//Muestra toda la imagen
			SDL_Rect recorte = {0, 0, anchoImagen, altoImagen};
			SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, anchoImagen, altoImagen};
			SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
		}
		else if (ancho > anchoImagen)
		{
			//Muestra la parte superior de la imagen
			SDL_Rect recorte = {0, 0, anchoImagen, alto};
			SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, anchoImagen, alto};
			SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
		}
		else if (alto > altoImagen)
		{
			//Muestra la parte izquierda de la imagen
			SDL_Rect recorte = {0, 0, ancho, altoImagen};
			SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, ancho, altoImagen};
			SDL_RenderCopy(renderer, obtenerImagen(), &recorte, &destino);
		}

		return;
	}
}

}

