/*
 * ConstructorEntidades.cpp
 *
 *  Created on: 25 mar. 2017
 *      Author: julieta
 */

#include "ConstructorEntidades.h"

/* CAPAS_H_ */
//	virtual void settipo(int) = 0;
//virtual int gettipo() = 0;
//int tipo;
// id
//tipo
// color
// dimension ancho
//int getancho();
//void setancho(int);
// dimension alto
//int getalto();
//void setalto(int);
// coordenada x
// coordenada y
//rutaimagen
//index
//ancho
//alto
//capas
//entidades
/* MENSAJE_H_ */
//archivo donde el logger va a escribir todos los mensajes
namespace std
{
    ConstructorEntidades::ConstructorEntidades()
    {
    }

    ConstructorEntidades::ConstructorEntidades(jescenario *jescenario)
    {
        cargarEntidades(jescenario->getentidades(), &rectangulos, &circulos);
    }

    ConstructorEntidades::ConstructorEntidades(jescenario *jescenario, list<Rectangulo> *rectangulos, list<Circulo> *circulos, Logger *log)
    {
    	this->log = log;
        cargarEntidades(jescenario->getentidades(), rectangulos, circulos);

    }

    Logger *ConstructorEntidades::getLog() const
    {
        return log;
    }

    void ConstructorEntidades::setLog(Logger *log)
    {
        this->log = log;
    }

    ConstructorEntidades::~ConstructorEntidades()
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
        this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Iniciado.", 2);
        for(pos = entidades.begin();pos != entidades.end();pos++){
            if((*pos).gettipo() == "rectangulo"){
            	this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Procesando rectangulo.", 2);
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
                this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Procesando rectangulo.", 2);
            }
            if((*pos).gettipo() == "circulo"){
            	this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Procesando circulo.", 2);
                id = (*pos).getid();
                color = (*pos).getcolor();
                radio = (*pos).getDim()->getvalor1();
                coordX = (*pos).getcoorx();
                coordY = (*pos).getcoory();
                rutaImagen = (*pos).getruta();
                indexZ = (*pos).getindex();
                Circulo circulo = Circulo(radio, id, color, rutaImagen, coordX, coordY, indexZ);
                circulos->push_back(circulo);
                this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Procesando circulo.", 2);
            }
        }

        this->log->addLogMessage("ENTIDADES", "[CARGA DE ENTIDADES] Terminado.", 2);
    }

    void ConstructorEntidades::mostrarEntidades(SDL_Renderer *renderizador)
    {
        list<Rectangulo>::iterator posRect;
        this->log->addLogMessage("ENTIDADES", "[MOSTRAR RECTANGULOS] Iniciado.", 2);
        for(posRect = rectangulos.begin();posRect != rectangulos.end();posRect++){
            (*posRect).dibujar(renderizador);
        }
        this->log->addLogMessage("ENTIDADES", "[MOSTRAR RECTANGULOS] Terminado.", 2);
        list<Circulo>::iterator posCirc;
        this->log->addLogMessage("ENTIDADES", "[MOSTRAR CIRCULOS] Iniciado.", 2);
        for(posCirc = circulos.begin();posCirc != circulos.end();posCirc++){
            (*posCirc).dibujar(renderizador);
        }
        this->log->addLogMessage("ENTIDADES", "[MOSTRAR RECTANGULOS] Terminado.", 2);
    }

    // TODO Auto-generated constructor stub
    // TODO Auto-generated destructor stub
    //Rectangulo(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen, int x, int y, unsigned int indexZ);
} //Namespace
