/*
 * AdministradorDeNiveles.h
 *
 *  Created on: 22 may. 2017
 *      Author: cristian
 */

#ifndef ADMINISTRADORDENIVELES_H_
#define ADMINISTRADORDENIVELES_H_
#include "VistaSDL.h"
#include "Camara.h"

class AdministradorDeNiveles {

	public:
		AdministradorDeNiveles();
		void pasarDeNivel();
		void cargarNivel(VistaSDL* vista);
		void mostrarNivel(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrarS);
		void setNivel(int);
		int getNivel();
		~AdministradorDeNiveles();

	private:
		int nivelActual;
		Textura* capa0;
		Textura* capa1;

};
#endif /* ADMINISTRADORDENIVELES_H_ */
