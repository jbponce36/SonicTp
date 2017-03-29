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
	bool validarEscenario(json_t* raiz,const char* nomesce,const char* nomdim,const char* ancho,const char* alto);
    void validarEntidadesEscenario(json_t* raizentidad,const char* id,const char* tipo,const char* color,const char* dim,const char* coor,const char* ruta,const char* index);
	char* getFiguraparser() const;
	void setFiguraparse(int level);
    void ValidarCapas(json_t* raiz,list<capas>ca);
	Logger* getLog() const;

	void setLog(Logger* log);

private:
	Logger *log;
	int banderacapas;
	jventana* cargarVentana(json_t* raiz);
	jconfiguracion* cargarConfiguracion(json_t* raiz);
	jescenario* cargarEscenario(json_t* raiz);
    list<double>validadores;
	double leerValorEntero(json_t* padre, const char* nombre,int valorPorDefecto);
	double leerValorEnteroaux(json_t* padre, const char* nombre,int valorPorDefecto);
    std::string leerValorStringCapas(json_t* padre,const char* nombre,std::string valorPorDefecto);
    int leerEntidadid(json_t* entidad,const char* nombre);
    int leerEntidadtipo(json_t* entidad,const char* nombre);
    int leerEntidadcolor(json_t* entidad,const char* nombre);
    int leerEntidaddimensionr(json_t* entidad,const char* nombred,const char* nombrean,const char* nombreal);
    int leerEntidaddimensionc(json_t* entidad,const char* nombred,const char* nombrer);
    int leerEntidadrutaimagen(json_t* entidad,const char* nombre);

};

} /* namespace std */

#endif /* PARSEADORJSON_H_ */
