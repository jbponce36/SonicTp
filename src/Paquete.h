/*
 * Paquete.h
 *
 *  Created on: 24 abr. 2017
 *      Author: cristian
 */

#ifndef PAQUETE_H_
#define PAQUETE_H_
#include <iostream>
#include <string.h>
#include <queue>
#include "Posicion.h"

namespace std{
struct nodo{
	char nodo[40];
	struct nodo *siguiente;
};
typedef struct nodo *Puntero;
class Paquete {
public:
	Paquete();
	~Paquete();
	void agregar(char *buffer);
	//void agregarPosicion(Posicion *pos);

	std::queue<char*> getColaPaquetes();
	//std::queue<Posicion *> getColaPaquetes();

	char* obtenerElementoDelaCola();
	//Posicion* obtenerElementoDelaCola();

	void eliminarElPrimetoDeLaCola();

private:
	std::queue<char*> colaPaquetes;
	//std::queue<Posicion *> colaPaquetes;
	//Puntero delante;
	//Puntero atras;

};

#endif /* PAQUETE_H_ */
}
