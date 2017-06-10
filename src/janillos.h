/*
 * janillos.h
 *
 *  Created on: 8 jun. 2017
 *      Author: patricia
 */

#ifndef JANILLOS_H_
#define JANILLOS_H_

class janillos {
public:
	janillos();
	virtual ~janillos();

	int getMaximoran();

	void setMaximoran(int Maximoran);

	int getMinimoran();

	void setMinimoran(int Minimoran);


private:
	int minimoran;
	int maximoran;

};

#endif /* JANILLOS_H_ */
