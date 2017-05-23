/*
 * ConstructorEntidades.cpp
 *
 *  Created on: 25 mar. 2017
 *      Author: julieta
 */

#define MODULO 'PARSEADOR JSON'
#include "ConstructorEntidades.h"

namespace std
{

ConstructorEntidades::ConstructorEntidades()
:log()
{

}

ConstructorEntidades::ConstructorEntidades(Logger *log)
{
	this->log = log;
	this->log->setModulo("CONSTRUCTOR ENTIDADES");
}

ConstructorEntidades::~ConstructorEntidades()
{
	list<Entidad*>::iterator pos;
	for(pos = entidades.begin();pos != entidades.end();pos++){
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

	this->log->addLogMessage("[CARGA DE ENTIDADES] Iniciado.", 2);

	for(pos = jEntidades.begin();pos != jEntidades.end();pos++)
	{
		if(((*pos).gettipo() == "rectangulo") || ((*pos).gettipo() == "cuadrado"))
		{
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

			if ((*pos).getruta() == "images/Anilla.png"){


				coordX = 0;
				ancho = (*pos).getDim()->getvalor1();
				int espacio = ancho + 10;

				int cantidadAnillas = (rand() % 7) + 3;

				for(int i=0;i<cantidadAnillas;i++){

					id = (*pos).getid();
					color = (*pos).getcolor();
					//ancho = (*pos).getDim()->getvalor1();
					alto = (*pos).getDim()->getvalor2();
					coordX = /*i * (*pos).getcoorx() +*/ coordX + (*pos).getcoorx() + (i*5);
					coordX = coordX + espacio;

					coordY = (*pos).getcoory();
					rutaImagen = (*pos).getruta();
					indexZ = (*pos).getindex();


				    Anillos* anillo = new Anillos(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);


					entidades.push_back(anillo);
			    }
			         //entidades.push_back(anillo);

			}
		else{
			Rectangulo *rectangulo = new Rectangulo(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
			entidades.push_back(rectangulo);
			this->log->setModulo("CONSTRUCTOR ENTIDADES");
			this->log->addLogMessage("[CARGAR ENTIDADES] Rectangulo->"+rectangulo->toString(), 3);
		}
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

			validarDatosNumericos(id, coordX, coordY, indexZ);
			validar(radio, 0, MAX_RADIO);

			Circulo *circulo = new Circulo(radio, id, color, rutaImagen, coordX, coordY, indexZ, this->log);
			entidades.push_back(circulo);
			this->log->setModulo("CONSTRUCTOR ENTIDADES");
			this->log->addLogMessage("[CARGAR ENTIDADES] Circulo->"+circulo->toString(), 3);
		}
	}

	cargarImagenes(renderizador);
	ordenarSegunIndexZ();

	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGA DE ENTIDADES] Terminado.\n", 2);
}

Logger *ConstructorEntidades::getLog() const
{
	return log;
}

void ConstructorEntidades::setLog(Logger *log)
{
	this->log = log;
}

void ConstructorEntidades::cargarImagenes(SDL_Renderer *renderizador)
{
	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGAR IMAGENES] Iniciado.",2);
	list<Entidad*>::iterator pos;
	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		if ((*pos)->tieneRutaImagen())
		{
			(*pos)->cargarImagen(renderizador, log);
			this->log->setModulo("CONSTRUCTOR ENTIDADES");
			this->log->addLogMessage("[CARGAR IMAGENES] Imagen cargada en ruta: "+(*pos)->getRutaImagen(),3);
		}
	}

	this->log->setModulo("CONSTRUCTOR ENTIDADES");
	this->log->addLogMessage("[CARGAR IMAGENES] Terminado.",2);

}
void ConstructorEntidades::mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara, int indexZ)
{
	list<Entidad*>::iterator pos;
	//this->log->addLogMessage("[MOSTRAR IMAGENES] Iniciado",2);
	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		if ((*pos)->indexZes(indexZ))
		{
			(*pos)->dibujar(renderizador, camara);
		}
	}

	//this->log->addLogMessage("[MOSTRAR IMAGENES] Terminado",2);
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
	this->log->addLogMessage("[VALIDAR DATOS NUMERICOS] Iniciado.",2);

	validar(id, 0, MAX_ID);
	validar(coordX, 0, MAX_COORDX);
	validar(coordY, 0, MAX_COORDY);
	validar(indexZ, 0, MAX_INDEXZ);

	this->log->addLogMessage("[VALIDAR DATOS NUMERICOS] Terminado.",2);
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

list<Entidad*> ConstructorEntidades::getEntidades() {
		return entidades;
}

void ConstructorEntidades::setEntidades(list<Entidad*> Entidades) {
		this->entidades = Entidades;
}
}
