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
        for(pos = jEntidades.begin();pos != jEntidades.end();pos++){
            if((*pos).gettipo() == "rectangulo"){
                this->log->addLogMessage("[CARGA DE ENTIDADES] Procesando rectangulo.", 2);
                id = (*pos).getid();
                color = (*pos).getcolor();
                ancho = (*pos).getDim()->getvalor1();
                alto = (*pos).getDim()->getvalor2();
                coordX = (*pos).getcoorx();
                coordY = (*pos).getcoory();
                rutaImagen = (*pos).getruta();
                indexZ = (*pos).getindex();
                Rectangulo *rectangulo = new Rectangulo(ancho, alto, id, color, rutaImagen, coordX, coordY, indexZ);
                entidades.push_back(rectangulo);
                this->log->addLogMessage("[CARGA DE ENTIDADES] Fin proceso rectangulo.", 2);
            }
            if((*pos).gettipo() == "circulo"){
                this->log->addLogMessage("[CARGA DE ENTIDADES] Procesando circulo.", 2);
                id = (*pos).getid();
                color = (*pos).getcolor();
                radio = (*pos).getDim()->getvalor1();
                coordX = (*pos).getcoorx();
                coordY = (*pos).getcoory();
                rutaImagen = (*pos).getruta();
                indexZ = (*pos).getindex();
                Circulo *circulo = new Circulo(radio, id, color, rutaImagen, coordX, coordY, indexZ);
                entidades.push_back(circulo);
                this->log->addLogMessage("[CARGA DE ENTIDADES] Fin proceso circulo.", 2);
            }
        }

        cargarImagenes(renderizador);
        ordenarSegunIndexZ();
        this->log->addLogMessage("[CARGA DE ENTIDADES] Terminado.", 2);
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
	list<Entidad*>::iterator pos;

	this->log->addLogMessage( "[MOSTRAR ENTIDADES] Iniciado.", 2);

	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		if ((*pos)->tieneRutaImagen())
		{
			(*pos)->cargarImagen(renderizador, log);
		}
	}

	this->log->addLogMessage("[MOSTRAR ENTIDADES] Terminado.", 2);
}
void ConstructorEntidades::mostrarEntidades(SDL_Renderer* renderizador, SDL_Rect *camara)
{
	list<Entidad*>::iterator pos;

	this->log->addLogMessage("[MOSTRAR ENTIDADES] Iniciado.", 2);

	for(pos = entidades.begin(); pos != entidades.end(); pos++)
	{
		(*pos)->dibujar(renderizador, camara);
	}

	this->log->addLogMessage( "[MOSTRAR ENTIDADES] Terminado.", 2);
}

bool compararIndexZ(const Entidad *primera, const Entidad *segunda)
{
	return primera->indexZMenorA(segunda);
}

void ConstructorEntidades::ordenarSegunIndexZ()
{
	entidades.sort(compararIndexZ);
}

}
