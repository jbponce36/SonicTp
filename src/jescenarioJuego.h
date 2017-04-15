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
#include "jservidor.h"

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

	jservidor* getServidor();
	void setServidor(jservidor* pservidor);

private:
	jventana* ventana;
	jconfiguracion* configuracion;
	jescenario* escenario;
	jservidor* servidor;
};

} /* namespace std */

#endif /* JESCENARIOJUEGO_H_ */
