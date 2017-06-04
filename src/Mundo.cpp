/*
 * Mundo.cpp
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#include "Mundo.h"
#include "Colicion.h"
#include "Entidad.h"

Mundo::Mundo(std::map<int, Personaje*> *sonics, VistaSDL *vista, std::vector<Hiloenviar*> *hilosEnviar)
: sonics(sonics), vista(vista), constructorEntidades(vista->getConstructorEntidades()), hilosEnviar(hilosEnviar)
{

}

Mundo::~Mundo()
{

}

void Mundo::enviarATodos(std::string mensaje)
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
			//cout << "Envie: " << mensaje << "\n";
		}
		id++;
	}

	/*------------------------------------------------------------------------------------------------*/
	//Info: Pensaba usarlo para mandarles la posicion de los bonus, piedras, anillos, etc a los clientes.
	//Porque son random y solo el server sabe donde estan y el resuelve las colisiones

}

void Mundo::enviarAUno(std::string mensaje, Hiloenviar *unHilo)
{
	char buffer[LARGO_MENSAJE_POSICION_SERVIDOR] = "";
	mensaje = mensaje + SEPARADOR_DE_MENSAJE;
	strcpy(buffer, mensaje.c_str());

	unHilo->enviarDato(buffer);
}

void Mundo::enviarDatosEscenario(std::vector<Hiloenviar*> *hilosEnviar)
{
	//Le envia a todos los clientes las posiciones de los objetos al principio de la partida
	std::string mensaje;

	std::list<Entidad*>::iterator pos;
	for(pos = constructorEntidades->entidades.begin();pos != constructorEntidades->entidades.end();pos++){
		mensaje = (*pos)->getNombre() + Util::intToStringConPadding((*pos)->getId(), MAX_CANT_DIGITOS_POS - 1)
			+ "x" + Util::intToStringConPadding((*pos)->obtenerX())
			+ "y" + Util::intToStringConPadding((*pos)->obtenerY());
		enviarATodos(mensaje);
	} //Ej: EA--1x--10y--20   Este mensaje lo recibe el cliente y dibuja el bonus donde corresponda.

	mensaje = FIN_MENSAJE_ESCENARIO;
	enviarATodos(mensaje);

}

void Mundo::enviarDatosEscenario(Hiloenviar *unHilo)
{
	//Le envia a todos los clientes las posiciones de los objetos al principio de la partida
	std::string mensaje;

	std::list<Entidad*>::iterator pos;
	for(pos = constructorEntidades->entidades.begin();pos != constructorEntidades->entidades.end();pos++){
		mensaje = (*pos)->getNombre() + Util::intToStringConPadding((*pos)->getId(), MAX_CANT_DIGITOS_POS - 1)
			+ "x" + Util::intToStringConPadding((*pos)->obtenerX())
			+ "y" + Util::intToStringConPadding((*pos)->obtenerY());
		enviarAUno(mensaje, unHilo);
	} //Ej: EA--1x--10y--20   Este mensaje lo recibe el cliente y dibuja el bonus donde corresponda.

	mensaje = FIN_MENSAJE_ESCENARIO;
	enviarAUno(mensaje, unHilo);

}

void Mundo::manejarColisiones()
{
	bool eliminar = false;
	int idAEliminar = 0;
	std::string nombreAEliminar;
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
				(*ent)->interactuar(sonic, this, eliminar);
				if (eliminar)
				{
					idAEliminar = (*ent)->getId();
					nombreAEliminar = (*ent)->getNombre();
				}
			}
		}

		//Se supone un Sonic solo va a interactuar con una sola entidad por tick
		if(eliminar)
		{
			eliminarEntidad(nombreAEliminar, idAEliminar);
		}

	}
}

void Mundo::eliminarEntidad(std::string nombre, int id)
{
	constructorEntidades->quitarEntidad(nombre, id);

	std::string mensaje;
	mensaje = nombre + Util::intToStringConPadding(id, MAX_CANT_DIGITOS_POS - 1) + "-----------";
	enviarATodos(mensaje);
}


