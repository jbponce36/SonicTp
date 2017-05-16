/*
 * menu.h
 *
 *  Created on: 15 may. 2017
 *      Author: patricia
 */

#ifndef MENU_H_
#define MENU_H_
//#include "ConexCliente.h"
//#include "JuegoCliente.h"

class menu {
public:
	menu(/*ConexCliente *cliente,JuegoCliente *c*/);
	virtual ~menu();
	int getSkt();
	  void setSkt(int s);
private:
	  int skt;

};

#endif /* MENU_H_ */
