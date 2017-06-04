/*
 * debug.cpp
 *
 *  Created on: 24 may. 2017
 *      Author: patricia
 */

#include "debug.h"
#include <stdio.h>

void debug(int nivel, char* funcion, char* mensaje, int valor)
{
	if (nivel<3){
		printf(funcion);
		printf(" --- ");
		printf(mensaje, valor);
		printf("\n");
	}
}

