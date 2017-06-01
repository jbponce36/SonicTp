#include "Rectangulo.h"

namespace std{

Rectangulo::Rectangulo() : ancho(), alto()
{

}

Rectangulo::Rectangulo(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log)
: Entidad(id, color, rutaImagen, x, y, indexZ, log), ancho(ancho), alto(alto)
{
	getLog()->setModulo("RECTANGULO");
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
		SDL_Rect destino = {obtenerX() - camara->x, obtenerY() - camara->y, ancho, alto};
		SDL_RenderFillRect(renderer, &destino);
	}
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

std::string Rectangulo::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

string Rectangulo::toString(){
	return "id: " +intToString(getId())+ ", " +"dimesiones-> ancho:"+ intToString(ancho)+", alto:"+
			intToString(alto)+ ", coordenadas-> x:"+intToString(getX())+
	", y: "+intToString(getY())+", index_z: "+ intToString(getIndexZ())+", ruta_imagen: "+ getRutaImagen();
}

SDL_Rect Rectangulo::obtenerLimites()
{
	SDL_Rect limites = { obtenerX(), obtenerY(), ancho, alto };
	return limites;
}

/*bool Rectangulo::intersecta(Rectangulo &otroRectangulo)
{
	SDL_Rect esteRectangulo = obtenerLimites();
	SDL_Rect elOtroRectangulo = otroRectangulo.obtenerLimites();

	SDL_bool intersecta = SDL_HasIntersection(&esteRectangulo, &elOtroRectangulo);

	if (intersecta == SDL_TRUE){
		return true;
	}
	else{
		return false;
	}
}*/

int Rectangulo::obtenerAncho()
{
	return ancho;
}

int Rectangulo::obtenerAlto()
{
	return alto;
}

void Rectangulo::interactuar(Personaje *sonic, Mundo* mundo)
{
	return; //Si la entidad es solo un Rectangulo, no hace nada
}

std::string Rectangulo::getNombre()
{
	return RECTANGULO;
}

}

int Rectangulo::getAlto() const {
	return alto;
}

void Rectangulo::setAlto(int alto) {
	this->alto = alto;
}

int Rectangulo::getAncho() const {
	return ancho;
}

void Rectangulo::setAncho(int ancho) {
	this->ancho = ancho;
}
