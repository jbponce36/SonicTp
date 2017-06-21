/*
 * Enemigo.h
 *
 *  Created on: 21 may. 2017
 *      Author: julian
 */

#ifndef ENEMIGO_H_
#define ENEMIGO_H_
#include "VistaSDL.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "Util.h"
class Enemigo {
private:
	std::string tipoEnemigo;
	//Animacion animacionEnemigo;
	//SDL_Rect posicionesYdimensones;
	float posicioneX;
	float posicioneY;
	//SDL_Rect SpriteActual;
	//float velocidad;
	bool vivo;

	int numeroSprite;
	bool seguirEnviandoMensajes;
	int puntaje;
	//Uint32 tiempo;
public:
	//ladoServidor
	Enemigo(int x, int y, std::string tipo/*, int maximoX,int minimoX, char tipo*/);
	void setVivo(bool cambiarVivo);
	std::string obteneMensajeEstadoInicial();
	std::string obteneMensajeEstado();
	std::string intToStringConPadding4(int number);
	std::string intToStringConPadding2(int number);
	virtual void actualizarPosicion();
	virtual int getPosicionDeEnemigo();
	//void calcularNumeroDeSprite();
	virtual SDL_Rect obtenerDimensiones();
	bool getSeguirEnviandoMensajes();
	void setSeguirEnviandoMensajes(bool seguir);
	void setNumeroSprite(int numero);
	int getNumeroSprite();
	std::string getTipoEnemigo();
	void setTipoEnemigo(std::string tipo);
	virtual void restarVida();
	virtual void comienzo();


	//ladoCliente
	//Enemigo(int x, int y/*VistaSDL *vista, int dimension, Logger *log*/);
	virtual void renderizar(int camaraX, int camaraY);
	void cargarCaracteristicas(int x,int y, int h, int w, char tipo);
	bool getVivo();
	void parsearMensajeInicial(std::string mensaje);
	void parsearMensaje(std::string mensaje);
	virtual ~Enemigo();

	float getPosicionesX();
	float getPosicionesY();
	void setPosicionesX(float posicion);
	void setPosicionesY(float posicion);
	void setPuntaje(int puntaje);
	int getPuntaje();
};

#endif /* ENEMIGO_H_ */
