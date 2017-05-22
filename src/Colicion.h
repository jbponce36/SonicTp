/*
 * Colicion.h
 *
 *  Created on: 22 may. 2017
 *      Author: patricia
 */

#ifndef COLICION_H_
#define COLICION_H_
#include <vector>
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Anillos.h"


class Colicion {

public:
	Colicion();
	virtual ~Colicion();

	std::vector<SDL_Rect> getSaltoDerecha();

	void setSaltoDerecha(std::vector<SDL_Rect>Saltard);

	bool ColicionAnillo(Anillos anillo,std::vector<SDL_Rect> saltoder);




private:
	std::vector<SDL_Rect> saltard;


};

#endif /* COLICION_H_ */
