/*
 * Util.h
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <iostream>
#include <sstream>
#include "Definiciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <SDL2/SDL.h>

class Util {
public:
	static std::string intToString(int numero);
	static std::string intToStringConPadding(int numero);
	static std::string intToStringConPadding(int numero, int largo);
	static int stringConPaddingToInt(std::string mensaje);
	static int numeroRandom(int hasta);
	static void dibujarRecuadro(SDL_Rect *entidad, SDL_Renderer *renderizador, SDL_Rect *camara);
};

#endif /* UTIL_H_ */
