//============================================================================
// Name        : TpTallerSonic.cpp
// Author      : Joha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


//#include </usr/include/SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
using namespace std;
#include <string>
#include "VistaSDL.h"
#include "Textura.h"

using namespace std;

int main() {

	VistaSDL *vista = new VistaSDL();
	vista->cargarTexturas();
	vista->mostrarVentana();
	vista->cerrar();

	return 0;
}
