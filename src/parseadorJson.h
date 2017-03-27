/*
 * parseadorJson.h
 *
 *  Created on: 20 mar. 2017
 *      Author: pato
 */

#ifndef PARSEADORJSON_H_
#define PARSEADORJSON_H_

#include <string>
#include "Logger.h"
#include "jescenarioJuego.h"
#include <jansson.h>
#include "jcirculo.h"
#include "jrectangulo.h"

namespace std {

class parseadorJson {

public:

	parseadorJson();
	parseadorJson(Logger *log);
	virtual ~parseadorJson();
	jescenarioJuego* parsearArchivo(char*  nombreArchivo);
    Logger *getLog() const;
    void setLog(Logger *log);
private:
	Logger *log;
	jventana* cargarVentana(json_t* raiz);
	jconfiguracion* cargarConfiguracion(json_t* raiz);
	jescenario* cargarEscenario(json_t* raiz);


};

} /* namespace std */

#endif /* PARSEADORJSON_H_ */
