/*
 * parseadorJson.h
 *
 *  Created on: 20 mar. 2017
 *      Author: pato
 */

#ifndef PARSEADORJSON_H_
#define PARSEADORJSON_H_


#include <iostream>
#include <string.h>
#include "Logger.h"
#include "jescenarioJuego.h"
#include <jansson.h>
#include "jcirculo.h"
#include "jrectangulo.h"
#include "jcuadrado.h"
#include "jventana.h"
#include "jservidor.h"
#include "ConexServidor.h"


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
    jescenarioJuego *getJuego() const;
    void setJuego(jescenarioJuego *juego);
	char* getFiguraparser() const;
	void setFiguraparse(int level);
	bool leerValorVentana(json_t *dimension, const char *ancho, const char *alto);
	jescenarioJuego* getescenario();
	void validarDimensionesVentana(jescenarioJuego *escenarioJuego);
	// devuelvo solo el puerto
	int CargarPuertoServidor();
	//devuelve solo la cantclientes
	int CargarCantClientes();

	void setraiz(json_t*);
	json_t* getraiz();

	int cargarPuerto(json_t* raiz);
	char* cargarIP(json_t* raiz);
    std::string intToString(int number);

private:
	Logger *log;
	json_t* raiz;

	jescenarioJuego *juego;
	jventana* cargarVentana(json_t* raiz);
	jconfiguracion* cargarConfiguracion(json_t* raiz);
	jescenario* cargarEscenario(json_t* raiz);
	jservidor* cargarServidor(json_t* raiz);
	double leerValorEntero(json_t* padre, const char* nombre,int valorPorDefecto);
    double leeValorEnteroServer(json_t* padre, const char* nombre,const char* nombrep,int valorPorDefecto);
	bool tryLeerValorEntero(json_t* padre, const char* nombre, double* valorLeido);
    std::string leerValorStringCapas(json_t* padre,const char* nombre,std::string valorPorDefecto);
    list<capas> DevolverCapasPorDefecto();
    list<jentidades> DevolverEntidadesPorDefecto();


};

} /* namespace std */

#endif /* PARSEADORJSON_H_ */
