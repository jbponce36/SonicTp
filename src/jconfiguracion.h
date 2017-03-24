/*
 * jconfiguracion.h
 *
 *  Created on: 18 mar. 2017
 *      Author: pato
 */

#ifndef JCONFIGURACION_H_
#define JCONFIGURACION_H_

namespace std {

class jconfiguracion {
public:
	jconfiguracion();
	virtual ~jconfiguracion();

	int getvelscroll();
	void setvelscroll(int);

private:
	int velscroll;
};

} /* namespace std */

#endif /* JCONFIGURACION_H_ */
