/*
 * parseadorJsonSer.cpp
 *
 *  Created on: 17 abr. 2017
 *      Author: pato
 */

#include "parseadorJsonSer.h"
#include "Logger.h"
#include <string>
#include <sstream>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
            ( std::ostringstream() << std::dec << x ) ).str()

namespace std {

parseadorJsonSer::parseadorJsonSer(Logger *log) {
	// TODO Auto-generated constructor stub
	this->raiz = NULL;
	this->log = log;
	this->log->setModulo("PARSEADOR JSON SERVER");
}

Logger* parseadorJsonSer::getLog() const {
	return log;
}

void parseadorJsonSer::setLog(Logger* log) {
	this->log = log;
	this->log->setModulo("PARSEADOR JSON SERVER");
}

parseadorJsonSer::~parseadorJsonSer() {
	// TODO Auto-generated destructor stub
}

json_t* parseadorJsonSer::getraiz(){
	return raiz;
}

void parseadorJsonSer::setraiz(json_t* Raiz){
	raiz = Raiz;
}

void parseadorJsonSer::parsearArchivo(std::string nombreArchivo){
  json_t *json;
  json_error_t error;

  this->log->addLogMessage("[PARSEADOR JSON SERVIDOR] Iniciado.", 2);

  json = json_load_file(nombreArchivo.c_str(),0,&error);
  this->setraiz(json);

  if(!json) {
	  cout << error.text << endl;
	  this->log->addLogMessage("[PARSEADOR JSON SERVIDOR] [ERROR] No se encontro el archivo o directorio.", 1);
	  cout << "Cargando archivo por defecto" << endl;
	  json = json_load_file("configuracion/servidordefault.json",0,&error);
	  this->setraiz(json);
	  this->log->addLogMessage("[PARSEADOR JSON SERVIDOR] Se carga un archivo por defecto: configuracion/default.json .", 1);
	  if (!json){
	    cout << "!!! no existe el archivo por defecto!!!" << endl;
	    cout << error.text << endl;
	    this->log->addLogMessage("[PARSEADOR JSON SERVIDOR] No existe el archivo o directorio por defecto.", 1);

	}
 }
  //this->log->addLogMessage("[PARSEADOR JSON SERVIDOR] Terminado. \n", 2);

}

double parseadorJsonSer::leeValorEnteroServer(json_t* padre, const char* nombre,const char* nombrep,int valorPorDefecto){
	json_t *elemento;

	std::string msjobj = std::string("[PARSEADOR JSON SERVER] ERROR. el atributo")+ " " + nombre + " " + std::string("no se encuentra o esta mal escrito,se carga el valor por defecto") + " " + SSTR( valorPorDefecto );
	std:: string msjatributo = std::string("[PARSEADOR JSON SERVER] ERROR. el atributo") + " " + nombre + " " + std::string("no es un numero,se carga el valor por defecto")+ " " + SSTR( valorPorDefecto );
	elemento = json_object_get(padre,nombre);

	if (!elemento){
		this->log->addLogMessage(msjobj,1);
		cout<<msjobj<<endl;
		return valorPorDefecto;

	}

	if (!json_is_number(elemento)){
		this->log->addLogMessage(msjatributo,1);
		cout<<msjatributo<<endl;
		return valorPorDefecto;
	}

	return json_number_value(elemento);
}


int parseadorJsonSer::CargarPuertoServidor(){

  json_t* raiz;

  int puerto;
  raiz = this->getraiz();

  this->log->addLogMessage("[PARSEADOR JSON SERVER] Iniciado.", 2);

  puerto = this->leeValorEnteroServer(raiz,"puerto","SERVIDOR",8080);

  this->log->addLogMessage("[PARSEADOR JSON SERVER] Terminado.", 2);
  return puerto;

}

int parseadorJsonSer::CargarCantClientes(){

 json_t* raiz;
 int cantclientes;

 raiz = this->getraiz();

 this->log->addLogMessage("[PARSEADOR JSON SERVER] Iniciado.", 2);

 cantclientes = this->leeValorEnteroServer(raiz,"cantclientes","SERVIDOR",2);

 this->log->addLogMessage("[PARSEADOR JSON SERVER] Terminado.", 2);

  return cantclientes;

 }
} /* namespace std */
