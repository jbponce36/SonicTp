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
		 return true;

	 }
	 else{
		 //cout<<"COLICION"<<endl;
		 return false;

	 }
}

bool Colicion::intersectaPiedraPersonaje(Piedra* piedra,Personaje* sonic){

	SDL_Rect RectanguloPiedra = piedra->obtenerLimites();
	SDL_Rect RectanguloPersonaje = sonic->obtenerLimites();

	SDL_bool intersecta = SDL_HasIntersection(&RectanguloPiedra, &RectanguloPersonaje);

	if (intersecta == SDL_TRUE){
	    return true;

	}
	else{
			 //cout<<"COLICION"<<endl;
		return false;

	}

}

bool Colicion::intersectaPinchePersonaje(Pinche* pinche,Personaje* sonic){

	SDL_Rect RectanguloPinche = pinche->obtenerLimites();
	SDL_Rect RectanguloPersonaje = sonic->obtenerLimites();

		SDL_bool intersecta = SDL_HasIntersection(&RectanguloPinche, &RectanguloPersonaje);

		if (intersecta == SDL_TRUE){
		    return true;

		}
		else{
				 //cout<<"COLICION"<<endl;
			return false;

		}

}
