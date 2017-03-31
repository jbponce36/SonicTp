/*
 * jentidades.cpp
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#include "jentidades.h"
#include "dimensiones.h"
#include <stdio.h>
#include <string.h>


namespace std {

jentidades::jentidades() {
	// TODO Auto-generated constructor stub
	this->dim = NULL;
	this->setcoorx(-1);
	this->setcoory(-1);
	this->setcolor("rojo");
	this->setruta("/imagenes/entidad1.png");
}

jentidades::~jentidades() {
	// TODO Auto-generated destructor stub
}

//id
int jentidades::getid(){
	return id;
}
void jentidades::setid(int ident){
	id = ident;
}

//tipo
std::string jentidades:: gettipo(){
	return tipo;
}
void jentidades::settipo(std::string tipoent){
	tipo = tipoent;
}

//color
std::string jentidades::getcolor(){
	return color;
}
void jentidades:: setcolor(std::string colorent){
	if ( (colorent.compare("rojo")==0)
		 || (colorent.compare("verde")==0)
		 || (colorent.compare("amarillo")==0)
		 || (colorent.compare("azul")==0) ) {

		color = colorent;
	}
}

dimensiones* jentidades::getDim(){
	return dim;
}

void jentidades::setDim(dimensiones* dim) {
	this->dim = dim;
}

//dimension ancho
//int jentidades::getancho(){
	//return ancho;
//}
//void jentidades::setancho(int anchoent){
	//ancho = anchoent;
//}

////dimensionalto
//int jentidades::getalto(){
	//return alto;
//}
//void jentidades::setalto(int altoent){
	//alto = altoent;
//}

//coordenada x
int jentidades::getcoorx(){
	return coorx;
}
void jentidades::setcoorx(int coorxent){
	coorx = coorxent;
}

// coordenada y
int jentidades::getcoory(){
	return coory;
}
void jentidades::setcoory(int cooryent){
	coory = cooryent;
}

//rutaimageb
std::string jentidades::getruta(){
	return ruta;
}
void jentidades::setruta(std::string rutaent){
	string extensionpng = "png";
	string extensionbmp = "bmp";
	if (this->hasEnding(rutaent, extensionpng) || this->hasEnding(rutaent, extensionbmp)){
		ruta = rutaent;
	}
	//
	//validacion ruta
	//char cadena[]=rutaent;
	//char *frase = strtok(cadena,".");

	// char *ptr = frase;

	//while(ptr != NULL){
		//cout << ptr << endl;
		//ptr = strtok(NULL, ".");
	//}
	//

}

//index
int jentidades::getindex(){
	return index;
}
void jentidades::setindex(int indexent){
	index = indexent;
}

bool jentidades::esValida() {

	if (this->getcoorx() == -1){
		return false;
	}

	if (this->getcoory() == -1){
		return false;
	}

	//Validamos el tipo
	bool tipoBien = false;
	if (this->gettipo().compare("rectangulo") == 0){
		tipoBien = true;
	}

	if (this->gettipo().compare("circulo") == 0){
		tipoBien = true;
	}

	if (!tipoBien){
		return false;
	}



	return true;
}


bool jentidades::hasEnding(const string& fullString, const string& ending) {

	    if (fullString.length() >= ending.length()) {
	        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
	    } else {
	        return false;
	    }
}

} /* namespace std */
