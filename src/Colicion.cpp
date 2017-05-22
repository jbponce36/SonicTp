/*
 * Colicion.cpp
 *
 *  Created on: 22 may. 2017
 *      Author: patricia
 */

#include "Colicion.h"

Colicion::Colicion() {
	// TODO Auto-generated constructor stub

}

Colicion::~Colicion() {
	// TODO Auto-generated destructor stub
}

std::vector<SDL_Rect> Colicion::getSaltoDerecha(){
		return saltard;
}

void Colicion::setSaltoDerecha(std::vector<SDL_Rect> Saltard) {
		this->saltard = Saltard;
}

bool Colicion::ColicionAnillo(Anillos anillo,std::vector<SDL_Rect> saltoder){

	//if( ((x1 + w1) > x2) && ((y1 + h1) > y2) && ((x2 + w2) > x1) && ((y2 + h2) > y1))
	//anillo.
   for(int i=0;i<saltoder.size();i++){

	   if( ((saltoder[i].x  + saltoder[i].w) > anillo.getX())
			 && ((saltoder[i].y + saltoder[i].h) > anillo.getY())
			 && ((anillo.getX() + anillo.getAncho()) > saltoder[i].x)
			 && ((anillo.getY() + anillo.getAlto()) > saltoder[i].y)){
		   return true;
	   }
	  // if(((saltoder[i].x + saltoder[i].w) > anillo.getX())) && ((anillo.getX() + anillo.getAncho()) && ())
   }

   return false;

}
