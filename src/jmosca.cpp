/*
 * jmosca.cpp
 *
 *  Created on: 8 jun. 2017
 *      Author: patricia
 */

#include "jmosca.h"

jmosca::jmosca() {
	// TODO Auto-generated constructor stub

}

jmosca::~jmosca() {
	// TODO Auto-generated destructor stub
}

int jmosca::getMaximoran(){
	return maximoran;
}

void jmosca::setMaximoran(int Maximoran) {
	this->maximoran = Maximoran;
}

int jmosca::getMinimoran(){
	return minimoran;
}

void jmosca::setMinimoran(int Minimoran) {
	this->minimoran = Minimoran;
}
