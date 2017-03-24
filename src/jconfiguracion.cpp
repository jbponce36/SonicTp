/*
 * jconfiguracion.cpp
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#include "jconfiguracion.h"

namespace std {

jconfiguracion::jconfiguracion() {
	// TODO Auto-generated constructor stub

}

jconfiguracion::~jconfiguracion() {
	// TODO Auto-generated destructor stub
}

int jconfiguracion::getvelscroll(){
	return velscroll;
}

void jconfiguracion::setvelscroll(int velscrollconf){
	velscroll = velscrollconf;
}
} /* namespace std */
