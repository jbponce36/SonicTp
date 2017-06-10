/*
 * jpinche.h
 *
 *  Created on: 8 jun. 2017
 *      Author: patricia
 */

#ifndef JPINCHE_H_
#define JPINCHE_H_

class jpinche {
public:
	jpinche();
	virtual ~jpinche();

	int getMaximoran();

	void setMaximoran(int Maximoran);

	int getMinimoran();

	void setMinimoran(int Minimoran);

private:
	int minimoran;
	int maximoran;
};

#endif /* JPINCHE_H_ */
