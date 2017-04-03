/*
 * capas.cpp
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#include "capas.h"
#include "jescenario.h"

namespace std {

capas::capas() {
	// TODO Auto-generated constructor stub

}

capas::~capas() {
	// TODO Auto-generated destructor stub
}

//id
int capas::getid(){
	return id;
}
void capas::setid(int idcapas){
	id = idcapas;
}

//index_z
int capas::getindex(){
	return index_z;
}
void capas::setindex(int indexcapas){
	index_z =indexcapas;
}
//rutaimagen

std::string capas::getrutaimagen(){
	return ruta_imagen;
}
void capas::setrutaimagen(std::string rutimagen){
	ruta_imagen = rutimagen;
}

string capas::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

string capas::toString(){
	return "id: " + intToString(id) +", " + "index_z: "+ intToString(index_z)+", " + "ruta_imagen: "+ ruta_imagen;
}
} /* namespace std */
