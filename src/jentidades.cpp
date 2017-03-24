/*
 * jentidades.cpp
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#include "jentidades.h"
#include "dimensiones.h"


namespace std {

jentidades::jentidades() {
	// TODO Auto-generated constructor stub
	this->dim = NULL;
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
	color = colorent;
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
	ruta = rutaent;
}

//index
int jentidades::getindex(){
	return index;
}
void jentidades::setindex(int indexent){
	index = indexent;
}

} /* namespace std */
