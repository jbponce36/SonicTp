//============================================================================
// Name        : Sonictp.cpp
// Author      : Joha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <jansson.h>
#include </usr/include/SDL2/SDL.h>
#include "Logger.h"
#include "jconfiguracion.h"
#include "jescenario.h"
#include "capas.h"
#include "jentidades.h"
#include "jescenarioJuego.h"
#include <list>
#include "dimensiones.h"
#include "parseadorJson.h"

#include "jpruebas.h"

using namespace std;

int main() {

	char *file = "configuracion/log.txt";
		Logger *log = new Logger(file, 1);
		string apertura = "Se abrio el archivo.";
		string cierre = "Se cerro el archivo.";
		string modulo = "CAPAS";

		log->addLogMessage(modulo,apertura);

		log->setLevel(2);
		string procesando = "Se esta procensando";
		log->addLogMessage(modulo,procesando);

		log->setLevel(3);
		modulo = "ENTIDADES";
		string continua = "continua procesando";
		log->addLogMessage(modulo,continua);
		log->addLogMessage(modulo,cierre);
		json_t *json;



		    parseadorJson* parseador = new parseadorJson();
			jescenarioJuego* jparseador = parseador->parsearArchivo("./configuracion/f.json");


			jpruebas* prueba = new jpruebas();
			prueba->prueba(jparseador);
		return 0;


}
