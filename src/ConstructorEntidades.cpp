/*
 * ConstructorEntidades.cpp
 *
 *  Created on: 25 mar. 2017
 *      Author: julieta
 */

#include "ConstructorEntidades.h"

namespace std
{

ConstructorEntidades::ConstructorEntidades() : log()
{

}

ConstructorEntidades::ConstructorEntidades(Logger *log) : log(log)
{

}

ConstructorEntidades::~ConstructorEntidades()
{
	list<Entidad*>::iterator pos;
	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		delete (*pos);
	}
	entidades.clear();
}


void ConstructorEntidades::cargarEntidades(list<jentidades> jEntidades, SDL_Renderer *renderizador)
{
	list<jentidades>::iterator pos;
	int id;
	std::string color;
	int ancho, alto;
	int coordX, coordY, indexZ;
	std::string rutaImagen;
	int radio;

	this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Iniciado.", 2);

	for(pos = jEntidades.begin();pos != jEntidades.end();pos++)
	{
		if(((*pos).gettipo() == "rectangulo") || ((*pos).gettipo() == "cuadrado"))
		{
			this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Procesando rectangulo.", 2);
			id = (*pos).getid();
			color = (*pos).getcolor();
			ancho = (*pos).getDim()->getvalor1();
			alto = (*pos).getDim()->getvalor2();
			coordX = (*pos).getcoorx();
			coordY = (*pos).getcoory();
			rutaImagen = (*pos).getruta();
			indexZ = (*pos).getindex();

			validarDatosNumericos(id, coordX, coordY, indexZ);
			validar(ancho, 0, MAX_ANCHO);
			validar(alto, 0, MAX_ALTO);

			if ((*pos).gettipo() == "cuadrado")
			{
				validarCuadrado(ancho, alto);
			}
			Rectangulo *rectangulo = new Rectangulo(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ);

			entidades.push_back(rectangulo);

			this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Fin proceso rectangulo.", 2);
		}

		if((*pos).gettipo() == "circulo")
		{
			this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Procesando circulo.", 2);
			id = (*pos).getid();
			color = (*pos).getcolor();
			radio = (*pos).getDim()->getvalor1();
			coordX = (*pos).getcoorx();
			coordY = (*pos).getcoory();
			rutaImagen = (*pos).getruta();
			indexZ = (*pos).getindex();

			validarDatosNumericos(id, coordX, coordY, indexZ);
			validar(radio, 0, MAX_RADIO);

			Circulo *circulo = new Circulo(radio, id, color, rutaImagen, coordX, coordY, indexZ);

			entidades.push_back(circulo);

			this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Fin proceso circulo.", 2);
		}
	}

	cargarImagenes(renderizador);
	ordenarSegunIndexZ();

	this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Terminado.", 2);
}


void ConstructorEntidades::cargarImagenes(SDL_Renderer *renderizador)
{
	list<Entidad*>::iterator pos;

	this->log->addLogMessage("ENTIDADES", "[MOSTRAR ENTIDADES] Iniciado.", 2);

	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		if ((*pos)->tieneRutaImagen())
		{
			(*pos)->cargarImagen(renderizador, log);
		}
	}

	this->log->addLogMessage("ENTIDADES", "[MOSTRAR ENTIDADES] Terminado.", 2);
}
void ConstructorEntidades::mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ)
{
	list<Entidad*>::iterator pos;

	std::string mensaje = "[MOSTRAR ENTIDADES] Index Z: "+ indexZ;
	log->addLogMessage("ENTIDAD", mensaje, 2);

	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		if ((*pos)->indexZes(indexZ))
		{
			(*pos)->dibujar(renderizador, camara);
		}
	}

	this->log->addLogMessage("ENTIDADES", "[MOSTRAR ENTIDADES] Terminado.", 2);
}

bool compararIndexZ(const Entidad *primera, const Entidad *segunda)
{
	return primera->indexZMenorA(segunda);
}

void ConstructorEntidades::ordenarSegunIndexZ()
{
	entidades.sort(compararIndexZ);
}

void ConstructorEntidades::validarDatosNumericos(int &id, int &coordX, int &coordY, int &indexZ)
{
	validar(id, 0, MAX_ID);
	validar(coordX, 0, MAX_COORDX);
	validar(coordY, 0, MAX_COORDY);
	validar(indexZ, 0, MAX_INDEXZ);
}

void ConstructorEntidades::validar(int &numero, int minimo, int maximo)
{
	if (numero < minimo)
	{
		numero = (-numero);
	}
	else if (numero > maximo)
	{
		numero = maximo;
	}
}

void ConstructorEntidades::validarCuadrado(int &ancho, int &alto)
{
	//El cuadrado es de dimensiones ancho x ancho
	if (ancho != alto)
	{
		alto = ancho;
	}
}

}
