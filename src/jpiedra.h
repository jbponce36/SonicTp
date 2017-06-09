/*
 * jpiedra.h
 *
 *  Created on: 8 jun. 2017
 *      Author: patricia
 */

#ifndef JPIEDRA_H_
#define JPIEDRA_H_

class jpiedra {
public:
	jpiedra();
	virtual ~jpiedra();

	int getMaximoran();

	void setMaximoran(int Maximoran);

	int getMinimoran();

	void setMinimoran(int Minimoran);

private:
	int minimoran;
	int maximoran;
};

#endif /* JPIEDRA_H_ */
