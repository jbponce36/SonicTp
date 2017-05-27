/*
 * Util.h
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <iostream>
#include <sstream>
#include "Definiciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

class Util {
public:
	static std::string intToString(int numero);
	static std::string intToStringConPadding(int numero);
	static int stringConPaddingToInt(std::string mensaje);
};

#endif /* UTIL_H_ */
