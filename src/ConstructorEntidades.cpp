/*
 * ConstructorEntidades.cpp
 *
 *  Created on: 25 mar. 2017
 *      Author: julieta
 */

#include "ConstructorEntidades.h"

namespace std {

ConstructorEntidades::ConstructorEntidades() {
	// TODO Auto-generated constructor stub

}

ConstructorEntidades::ConstructorEntidades(jescenario *jescenario)
{
	//this->cargarEntidades(jescenario->getentidades(), &rectangulos, &circulos);
}

ConstructorEntidades::ConstructorEntidades(jescenario *jescenario, list<Rectangulo> *rectangulos, list<Circulo> *circulos)
{
	//cargarEntidades(jescenario->getentidades(), rectangulos, circulos);
}

ConstructorEntidades::~ConstructorEntidades() {
	// TODO Auto-generated destructor stub
}

void ConstructorEntidades::cargarEntidades(list<jentidades> entidades)
{

}

void ConstructorEntidades::cargarEntidades(list<jentidades> entidades, list<Rectangulo> *rectangulos, list<Circulo> *circulos)
{
	list<jentidades>::iterator pos;
	int id;
	std::string color;
	int ancho, alto;
	int coordX, coordY, indexZ;
	std::string rutaImagen;
	int radio;

	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		if((*pos).gettipo() == "rectangulo")
		{
			//Rectangulo(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ);
			id = (*pos).getid();
			color = (*pos).getcolor();
			ancho = (*pos).getDim()->getvalor1();
			alto = (*pos).getDim()->getvalor2();
			coordX = (*pos).getcoorx();
			coordY = (*pos).getcoory();
			rutaImagen = (*pos).getruta();
			indexZ = (*pos).getindex();

			Rectangulo rectangulo = Rectangulo(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ);

			rectangulos->push_back(rectangulo);
		}

		if((*pos).gettipo() == "circulo")
		{
			id = (*pos).getid();
			color = (*pos).getcolor();
			radio = (*pos).getDim()->getvalor1();
			coordX = (*pos).getcoorx();
			coordY = (*pos).getcoory();
			rutaImagen = (*pos).getruta();
			indexZ = (*pos).getindex();

			Circulo circulo = Circulo(radio, id, color, rutaImagen, coordX, coordY, indexZ);

			circulos->push_back(circulo);
		}
	}

}

void ConstructorEntidades::mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara)
{
	list<Rectangulo>::iterator posRect;

	for(posRect = rectangulos.begin(); posRect != rectangulos.end(); posRect++)
	{
		(*posRect).dibujar(renderizador, camara);
	}

	list<Circulo>::iterator posCirc;

	for(posCirc = circulos.begin(); posCirc != circulos.end(); posCirc++)
	{
		(*posCirc).dibujar(renderizador, camara);
	}
}

} //Namespace
