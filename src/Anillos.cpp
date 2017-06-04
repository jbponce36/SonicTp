/*
 * Anillos.cpp
 *
 *  Created on: 23 may. 2017
 *      Author: patricia
 */

#include "Anillos.h"


Anillos::Anillos(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ, Logger *log/*,SDL_Renderer *render*/)
: Entidad(id, color, rutaImagen, x, y, indexZ, log), ancho(ancho), alto(alto), texturaAnillo(NULL)
{
	getLog()->setModulo("ANILLO");

}


Anillos::~Anillos() {
	// TODO Auto-generated destructor stub
}


std::string Anillos::getRuta(){
		return this->ruta;
	}

void Anillos::setRuta(std::string Ruta) {
		this->ruta = Ruta;
}

void Anillos::cargardatos(SDL_Renderer *render){
	if(texturaAnillo == NULL){
		cout<<"ANILLOS"<<endl;
		this->texturaAnillo = new Textura();

		this->texturaAnillo->cargarImagen(getRutaImagen(),getRutaImagen(),render,this->getLog());

		this->cargarspriteanillo();
	}
}



void Anillos::Comenzar(){
	this->Anianillo->comenzar();

}
void Anillos::dibujar(SDL_Renderer *renderer, SDL_Rect *camara){

//this->Anianillo->comenzar();
/*	if (obtenerImagen() == NULL)
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


*/

}

SDL_Rect Anillos::obtenerLimites()
{
	SDL_Rect limites = { obtenerX(), obtenerY(), ancho, alto };
	return limites;
}

bool Anillos::intersecta(Anillos &otroRectangulo)
{
	SDL_Rect esteRectangulo = obtenerLimites();
	SDL_Rect elOtroRectangulo = otroRectangulo.obtenerLimites();

    SDL_bool intersecta = SDL_HasIntersection(&esteRectangulo, &elOtroRectangulo);
	if (intersecta == SDL_TRUE){
		return true;
		cout<<"INTERSECTO"<<endl;
	}
	else{
		return false;
		cout<<"NOINTERSECTO"<<endl;
	}
}

int Anillos::getAncho() {
	return this->ancho;
}

void Anillos::setAncho(int ancho) {
	this->ancho = ancho;
}

int Anillos::getAlto() {
	return this->alto;
}

void Anillos::setAlto(int Alto) {
	this->alto = Alto;
}

int Anillos::getIndexZ() {
	return this->indexZ;
}

void Anillos::setIndexZ(int iZ) {
		this->indexZ = iZ;
}
int Anillos::getCoorx() {
	return x;
}

void Anillos::setCoorx(int Coorx) {
	this->x = Coorx;
}

int Anillos::getCoory(){
	return y;
}

void Anillos::setCoory(int Coory) {
	this->y = Coory;
}

void Anillos::cargarspriteanillo(){

	Anianillo = new Animacion(texturaAnillo,ancho,1,ANILLOS);
	Anianillo->cargarSprites(0,0,8);
	Anianillo->cargarSprites(0,1,8);
	Anianillo->cargarSprites(0,2,8);
	Anianillo->cargarSprites(0,3,6);

	animacionActual = Anianillo;
	animacionActual->comenzar();



}

void Anillos::render(int camX, int camY){
	SDL_Rect cuadroDeVentana;

	cuadroDeVentana.x=(obtenerX()-camX);
	cuadroDeVentana.y=(obtenerY()-camY);
	cuadroDeVentana.w=ancho;
	cuadroDeVentana.h=alto;
	animacionActual->dibujar(cuadroDeVentana);
}

std::string Anillos::getNombre(){
	return ANILLOS;
}
std::string Anillos::intToStringConPadding(int number)
{
  ostringstream oss;
  oss<< number;
  std::string numero = oss.str();
  while(numero.length() < MAX_CANT_DIGITOS_POS){
	  numero = PADDING + numero;
  }
  return numero;
}

std::string Anillos::intToStringConPaddingID(int number){

	ostringstream oss;
	  oss<< number;
	  std::string numero = oss.str();
	  while(numero.length() < 2){
		  numero = PADDING + numero;
	  }
	  return numero;
}

int Anillos::getId() {
		return id;
	}

void Anillos::setId(int Id) {
		this->id = Id;
	}

std::string Anillos::obtenerMensajeEstado(){

	/*std::string a = "Anill";
	//std::string a = "Aid";
	std::string numx = "x";
	std::string numy = "y";


	return(a + numx + intToStringConPadding(x) + numy + intToStringConPadding(y));
*/


	std::string a = "Aid";
		//std::string a = "Aid";
		std::string numx = "x";
		std::string numy = "y";


		return(a + this->intToStringConPaddingID(id) + numx + intToStringConPadding(x) + numy + intToStringConPadding(y));

}

std::string Anillos::obtenerMsjAnillaBorrada(int numero){

		std::string a = "BORRAR_ANILLA";
		//std::string numx = "x";
		//std::string numy = "y";
		return(a +  intToStringConPaddingID(numero));



}

int Anillos::getIdb(){
		return idb;
	}

void Anillos::setIdb(int Idb) {
		this->idb = Idb;
	}
