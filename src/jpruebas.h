/*
 * jpruebas.h
 *
 *  Created on: 21 mar. 2017
 *      Author: pato
 */

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

namespace std {

class jpruebas {
public:
	jpruebas();
	virtual ~jpruebas();
    void prueba(jescenarioJuego* escenario);
};

} /* namespace std */

#endif /* JPRUEBAS_H_ */
