#include <iostream>
#include <jansson.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
using namespace std;
#include <string>
#include "VistaSDL.h"
#include "Textura.h"
#include "parseadorJson.h"
#include "jescenarioJuego.h"
#include "jventana.h"
#include "Rectangulo.h"
#include "Circulo.h"
using namespace std;

int main() {

	parseadorJson* parseador = new parseadorJson();
	//jescenarioJuego* jparseador = parseador.
	char* file= "configuracion/f.json";

    jescenarioJuego* jparseador = parseador->parsearArchivo(file);

	VistaSDL *vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario());
	vista->cargarTexturas();
	vista->mostrarVentana();
	vista->cerrar();

	return 0;
}
