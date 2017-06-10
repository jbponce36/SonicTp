/*
 * jpescado.h
 *
 *  Created on: 9 jun. 2017
 *      Author: patricia
 */

#ifndef JPESCADO_H_
#define JPESCADO_H_

class jpescado {
public:
	jpescado();
	virtual ~jpescado();
	int getMaximoran();

	void setMaximoran(int Maximoran);

	int getMinimoran();

	void setMinimoran(int Minimoran);

private:
	int minimoran;
	int maximoran;
};

#endif /* JPESCADO_H_ */
