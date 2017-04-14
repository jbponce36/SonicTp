#ifndef JPRUEBAS_H_
#define JPRUEBAS_H_
#include <iostream>
#include </usr/include/SDL2/SDL.h>
#include <jansson.h>
#include "jventana.h"
#include "jconfiguracion.h"
#include "jescenario.h"
#include "capas.h"
#include "jentidades.h"
#include <list>
#include "dimensiones.h"
#include "parseadorJson.h"
#include <list>
#include "Sockets.h"
namespace std {

class jpruebas {
public:

	jpruebas();
	virtual ~jpruebas();
    void prueba(jescenarioJuego* escenario);
    void pruebasocket();
};

} /* namespace std */

#endif /* JPRUEBAS_H_ */
