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
	bool validarVentana(json_t* raiz,const char* nomvent,const char* nomdim,const char* nomancho,const char* nomalto);
	bool validarConfiguracion(json_t* raiz,const char* config,const char* velscroll);
	bool validarEscenario(json_t* raiz,const char* nomesce,const char* nomdim,const char* ancho,const char* alto);
    void validarEntidadesEscenario(json_t* raizentidad,const char* id,const char* tipo,const char* color,const char* dim,const char* coor,const char* ruta,const char* index);
    Logger *getLog() const;
    void setLog(Logger *log);


private:
	Logger *log;
	jventana* cargarVentana(json_t* raiz);
	jconfiguracion* cargarConfiguracion(json_t* raiz);
	jescenario* cargarEscenario(json_t* raiz);

	double leerValorEntero(json_t* padre, const char* nombre,int valorPorDefecto);
    bool  leerValorVentana(json_t* dimension, const char* ancho,const char* alto);

};

} /* namespace std */

#endif /* PARSEADORJSON_H_ */
