/*
 * Bonus.h
 *
 *  Created on: 25 may. 2017
 *      Author: julieta
 */

#ifndef BONUS_H_
#define BONUS_H_

#include "Rectangulo.h"

class Bonus : public Rectangulo {
private:

public:
	Bonus(int ancho, int alto, unsigned int id, std::string color, std::string rutaImagen,
		int x, int y, unsigned int indexZ, Logger *log);

	virtual ~Bonus();
};

#endif /* BONUS_H_ */
