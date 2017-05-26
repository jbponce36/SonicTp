/*
 * Mundo.cpp
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#include "Mundo.h"
#include "Colicion.h"

Mundo::Mundo(std::map<int, Personaje*> *sonics, VistaSDL *vista)
: sonics(sonics), vista(vista), constructorEntidades(vista->getConstructorEntidades()), bonus()
{

}

Mundo::~Mundo()
{

}

void Mundo::enviarATodos(std::vector<Hiloenviar*> *hilosEnviar, std::string mensaje)
{
	//Envia el mensaje a todos los hilos enviar para que se lo mande a todos los clientes
	char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
	strcpy(buffer, mensaje.c_str());

	int id = 1;
	std::vector<Hiloenviar*>::iterator pos;
	for(pos = hilosEnviar->begin();pos != hilosEnviar->end();pos++)
	{
		if(!sonics->at(id)->estaCongelado())
		{
			(*pos)->enviarDato(buffer);
		}
		id++;
	}

	/*------------------------------------------------------------------------------------------------*/
	//Info: Pensaba usarlo para mandares la posicion de los bonus, piedras, anillos, etc a los clientes.
	//Porque son random y solo el server sabe donde estan y el resuelve las colisiones

}

void Mundo::manejarColisiones()
{
	std::map<int, Personaje*>::iterator pos;
	list<Anillos*>:: iterator posanillo;

	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		//Por cada sonic, fijarse si se intersecta con alguna de las cosas...?

         for(posanillo = this->constructorEntidades->anillos.begin(); posanillo!= this->constructorEntidades->anillos.end();posanillo++){



         }


	}
}

