/*
 * parseadorJson.h
 *
 *  Created on: 20 mar. 2017
 *      Author: pato
 */

#ifndef PARSEADORJSON_H_
#define PARSEADORJSON_H_

#include <string>

#include "jescenarioJuego.h"

namespace std {

class parseadorJson {

public:

	parseadorJson();
	virtual ~parseadorJson();
	jescenarioJuego* parsearArchivo(char*  nombreArchivo);
	//char* getFiguraparser() const;
	//void setFiguraparse(int level);
private:


	jventana* cargarVentana(json_t* raiz);
	jconfiguracion* cargarConfiguracion(json_t* raiz);
	jescenario* cargarEscenario(json_t* raiz);


};

} /* namespace std */

#endif /* PARSEADORJSON_H_ */
