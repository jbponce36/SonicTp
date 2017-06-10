/*
 * jmosca.h
 *
 *  Created on: 8 jun. 2017
 *      Author: patricia
 */

#ifndef JMOSCA_H_
#define JMOSCA_H_

class jmosca {
public:
	jmosca();
	virtual ~jmosca();
	int getMaximoran();

	void setMaximoran(int Maximoran);

	int getMinimoran();

	void setMinimoran(int Minimoran);

private:
	int minimoran;
	int maximoran;

};

#endif /* JMOSCA_H_ */
