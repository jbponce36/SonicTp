/*
 * parseadorJsonCli.cpp
 *
 *  Created on: 18 abr. 2017
 *      Author: pato
 */

#include "parseadorJsonCli.h"

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
            ( std::ostringstream() << std::dec << x ) ).str()

namespace std {

parseadorJsonCli::parseadorJsonCli(Logger *log ) {
	// TODO Auto-generated constructor stub
	this->raiz = NULL;
	this->log = log;
	this->log->setModulo("PARSEADOR CLI");

}

parseadorJsonCli::~parseadorJsonCli() {
	// TODO Auto-generated destructor stub
}

Logger* parseadorJsonCli::getLog() const {
	return log;
}

void parseadorJsonCli::setLog(Logger* log) {
	this->log = log;
	this->log->setModulo("PARSEADOR JSON CLIENTE");
}

json_t* parseadorJsonCli::getraiz(){
	return raiz;
}

void parseadorJsonCli::setraiz(json_t* Raiz){
	raiz = Raiz;
}

void parseadorJsonCli::parsearArchivo(std::string  nombreArchivo){
 json_t *json;
 json_error_t error;
 cout<<"entro"<<endl;
 this->log->addLogMessage("[PARSEADOR JSON CLIENTE] Iniciado.", 2);

 json = json_load_file(nombreArchivo.c_str(),0,&error);
 this->setraiz(json);

  if(!json) {
	 cout << error.text << endl;
	 this->log->addLogMessage("[PARSEADOR JSON CLIENTE] [ERROR] No se encontro el archivo o directorio.", 1);
	 cout << "Cargando archivo por defecto" << endl;
	 json = json_load_file("configuracion/clientedefault.json",0,&error);
	 this->setraiz(json);
	 this->log->addLogMessage("[PARSEADOR JSON CLIENTE] Se carga un archivo por defecto: configuracion/default.json .", 1);
	 if (!json){
		 cout << "!!! no existe el archivo por defecto!!!" << endl;
		 cout << error.text << endl;
		 this->log->addLogMessage("[PARSEADOR JSON CLIENTE] No existe el archivo o directorio por defecto.", 1);

	 }
 }
	  this->log->addLogMessage("[PARSEADOR JSON CLIENTE] Terminado.", 2);

}

double parseadorJsonCli::leeValorEnteroServer(json_t* padre, const char* nombre,const char* nombrep,int valorPorDefecto){
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

const char* parseadorJsonCli::leerValorStringip(json_t* padre,const char* nombre,const char* valorPorDefecto){
 json_t *elemento;

 std::string msjobj = std::string("[PARSEADOR JSON SERVER] ERROR. el atributo")+ " " + nombre + " " + std::string("no se encuentra o esta mal escrito,se carga el valor por defecto") + " " + SSTR( valorPorDefecto );
 std:: string msjatributo = std::string("[PARSEADOR JSON SERVER] ERROR. el atributo") + " " + nombre + " " + std::string("no es un char,se carga el valor por defecto")+ " " + SSTR( valorPorDefecto );

 elemento = json_object_get(padre,nombre);

 if (!elemento){
	 this->log->addLogMessage(msjobj,1);
	 cout<<msjobj<<endl;
	 return valorPorDefecto;

 }

 if (!json_is_string(elemento)){
	 this->log->addLogMessage(msjatributo,1);
	 cout<<msjatributo<<endl;
	 return valorPorDefecto;

 }

  return json_string_value(elemento);
}

int parseadorJsonCli::CargarPuertoCliente(){
  json_t* raiz;

  this->log->addLogMessage("[PARSEADOR JSON CLIENTE] Iniciado.", 2);
  int puerto;
  raiz = this->getraiz();

  puerto = this->leeValorEnteroServer(raiz,"puerto","CLIENTE",8080);

  this->log->addLogMessage("[PARSEADOR JSON CLIENTE] Terminado.", 2);
  return puerto;
}

const char* parseadorJsonCli::CargarIPCliente(){
	this->log->addLogMessage("[PARSEADOR JSON CLIENTE] Iniciado.", 2);
	const char* ip;
	raiz = this->getraiz();

	ip = this->leerValorStringip(raiz,"ip","127.0.0.1");
	this->log->addLogMessage("[PARSEADOR JSON CLIENTE] Terminado.", 2);

	return ip;
}
} /* namespace std */
