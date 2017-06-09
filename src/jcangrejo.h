/*
 * jcangrejo.h
 *
 *  Created on: 8 jun. 2017
 *      Author: patricia
 */

#ifndef JCANGREJO_H_
#define JCANGREJO_H_

class jcangrejo {
public:
	jcangrejo();
	virtual ~jcangrejo();

	int getMaximoran();

	void setMaximoran(int Maximoran);

	int getMinimoran();

	void setMinimoran(int Minimoran);

private:
	int minimoran;
	int maximoran;
};

#endif /* JCANGREJO_H_ */
