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
#include "Definiciones.h"

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
	void agregarAlaColaSoloUnProceso(int tamanioBuffRecibido,char *bufferRecibido);
	//void agregarPosicion(Posicion *pos);
	void colaInicializar();
	std::queue<char*> getColaPaquetes();
	//std::queue<Posicion *> getColaPaquetes();

	char* obtenerElementoDelaCola();
	char* obtenerUltimoElementoDelaCola();
	//Posicion* obtenerElementoDelaCola();

	void eliminarElPrimetoDeLaCola();
	bool estaVacia();
	void vaciarCola();

private:
	std::queue<char*> colaPaquetes;
	pthread_mutex_t mutex;
	char buffAuxiliar[16];
	int ContadorBuffAuxiliar;
	//std::queue<Posicion *> colaPaquetes;
	//Puntero delante;
	//Puntero atras;

};
}
#endif /* PAQUETE_H_ */

