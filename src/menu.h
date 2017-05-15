/*
 * menu.h
 *
 *  Created on: 15 may. 2017
 *      Author: patricia
 */

#ifndef MENU_H_
#define MENU_H_

class menu {
public:
	menu();
	virtual ~menu();
	int getSkt();
	  void setSkt(int s);
private:
	  int skt;
};

#endif /* MENU_H_ */
