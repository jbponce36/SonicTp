/*
 * parseadorJsonCli.h
 *
 *  Created on: 18 abr. 2017
 *      Author: pato
 */

#ifndef PARSEADORJSONCLI_H_
#define PARSEADORJSONCLI_H_

#include <iostream>
#include <jansson.h>
#include "Logger.h"
#include <string>
#include <sstream>

namespace std {

class parseadorJsonCli {
public:
	parseadorJsonCli();
	virtual ~parseadorJsonCli();
	void parsearArchivo(std::string  nombreArchivo);
	int CargarPuertoCliente();
	const char* CargarIPCliente();
	const char* leerValorStringip(json_t* padre,const char* nombre,const char* valorPorDefecto);
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

#endif /* PARSEADORJSONCLI_H_ */
