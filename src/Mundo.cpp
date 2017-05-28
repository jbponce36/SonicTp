/*
 * Mundo.cpp
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#include "Mundo.h"
#include "Colicion.h"

Mundo::Mundo(std::map<int, Personaje*> *sonics, VistaSDL *vista)
: sonics(sonics), vista(vista), constructorEntidades(vista->getConstructorEntidades())
{

}

Mundo::~Mundo()
{

}

void Mundo::enviarATodos(std::vector<Hiloenviar*> *hilosEnviar, std::string mensaje)
{
	//Envia el mensaje a todos los hilos enviar para que se lo mande a todos los clientes
	char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
	mensaje = mensaje + SEPARADOR_DE_MENSAJE;
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
	//Info: Pensaba usarlo para mandarles la posicion de los bonus, piedras, anillos, etc a los clientes.
	//Porque son random y solo el server sabe donde estan y el resuelve las colisiones

}

void Mundo::enviarDatosEscenario(std::vector<Hiloenviar*> *hilosEnviar)
{
	//Le envia a todos los clientes las posiciones de los objetos al principio de la partida
	std::string mensaje;

	/*std::vector<Bonus*>::iterator pos;
	for(pos = bonus->begin();pos != bonus->end();pos++){
		mensaje = BONUS + Util::intToStringConPadding((*pos)->getId())
			+ "x" + Util::intToStringConPadding((*pos)->obtenerX())
			+ "y" + Util::intToStringConPadding((*pos)->obtenerY());
		enviarATodos(hilosEnviar, mensaje);
	}*/ //Ej: BON---1x--10y--20   Este mensaje lo recibe el cliente y dibuja el bonus donde corresponda.


	//... Otros for...



	///
	mensaje = FIN_MENSAJE_ESCENARIO;
	enviarATodos(hilosEnviar, mensaje);

}

void Mundo::manejarColisiones()
{
	std::map<int, Personaje*>::iterator pos;

	for(pos = sonics->begin();pos != sonics->end();pos++)
	{
		//Por cada sonic, fijarse si se intersecta con alguna de las cosas...?
		Personaje *sonic = (*pos).second;

		list<Entidad*>::iterator ent;
		for(ent = constructorEntidades->entidades.begin(); ent != constructorEntidades->entidades.end(); ent++)
		{
			if((*ent)->intersecta(sonic))
			{
				//Depende de que entidad sea, cada una interactua de forma diferente
				//Y le puede preguntar cosas al Sonic y afectar el mundo
				(*ent)->interactuar(sonic, this);
			}
		}
	}
}

