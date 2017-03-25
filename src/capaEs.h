/*
 * capaEs.h
 *
 *  Created on: 25 mar. 2017
 *      Author: cristian
 */
#ifndef CAPAES_H_
#define CAPAES_H_

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include <string>
#include "Textura.h"
#include "jventana.h"
#include "jconfiguracion.h"
#include "jescenario.h"
#include "capas.h"

using namespace std;


class capaEs{

private:
	int id;
	int index_z;
	std::string rutaImagen;

public:
	int getId();
	int getIndex();
	std::string getRutaImagen();

	void setId(int);
	void setIndex_z(int);
	void setRutaImagen(std::string);

};



#endif /* CAPAES_H_ */
