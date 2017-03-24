/*
 * jescenarioJuego.h
 *
 *  Created on: 22 mar. 2017
 *      Author: pato
 */

#ifndef JESCENARIOJUEGO_H_
#define JESCENARIOJUEGO_H_

#include "jventana.h"
#include "jconfiguracion.h"
#include "jescenario.h"
#include "jescenarioJuego.h"


namespace std {

class jescenarioJuego {
public:
	jescenarioJuego();
	virtual ~jescenarioJuego();

	jventana* getVentana();
	void setVentana(jventana* pventana);

	jconfiguracion* getConfiguracion();
	void setConfiguracion(jconfiguracion* pconfiguracion);

	jescenario* getEscenario();
	void setEscenario(jescenario* pescenario);

private:
	jventana* ventana;
	jconfiguracion* configuracion;
	jescenario* escenario;
};

} /* namespace std */

#endif /* JESCENARIOJUEGO_H_ */
