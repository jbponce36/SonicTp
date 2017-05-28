/*
 * Colicion.cpp
 *
 *  Created on: 23 may. 2017
 *      Author: patricia
 */

#include "Colicion.h"

Colicion::Colicion() {
	// TODO Auto-generated constructor stub

}

Colicion::~Colicion() {
	// TODO Auto-generated destructor stub
}

bool Colicion::intersectaAnilloPersonaje(Anillos* anillo,Personaje* sonic){

	SDL_Rect RectanguloAnillo = anillo->obtenerLimites();
	SDL_Rect RectanguloPersonaje = sonic->obtenerLimites();

	 SDL_bool intersecta = SDL_HasIntersection(&RectanguloAnillo, &RectanguloPersonaje);

	 if (intersecta == SDL_TRUE){
		 cout<<"COLICION"<<endl;
		 return true;

	 }
	 else{
		 //cout<<"COLICION"<<endl;
		 return false;

	 }
}

