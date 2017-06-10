/*
 * parseadorJsonSer.h
 *
 *  Created on: 17 abr. 2017
 *      Author: pato
 */

#ifndef PARSEADORJSONSER_H_
#define PARSEADORJSONSER_H_

#include <iostream>
#include <jansson.h>
#include "Logger.h"
#include <string>
#include <sstream>

namespace std {

class parseadorJsonSer {
public:
	parseadorJsonSer(Logger *log);
	virtual ~parseadorJsonSer();
	void parsearArchivo(std::string nombreArchivo);
	int CargarPuertoServidor();
	int CargarCantClientes();
	int CargarModoJuego();
	double leeValorEnteroServer(json_t* padre, const char* nombre,const char* nombrep,int valorPorDefecto);
	void setraiz(json_t*);
	json_t* getraiz();
	Logger *getLog() const;
	void setLog(Logger *log);
private:
	Logger *log;
	json_t* raiz;
};

} /* namespace std */

#endif /* PARSEADORJSONSER_H_ */
