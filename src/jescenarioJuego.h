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
#include "janillos.h"
#include "jpiedra.h"
#include "jpinche.h"
#include "jcangrejo.h"
#include "jmosca.h"
#include "jpescado.h"

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

    janillos* getAnillo();
    void setAnillo(janillos* panillos);

    jpiedra* getPiedra();
    void setPiedra(jpiedra* ppiedra);

    jpinche* getPinche();
    void setPinche(jpinche* ppinche);

    jcangrejo* getCangrejo();
    void setCangrejo(jcangrejo* pcangrejo);

    jmosca* getMosca();
    void setMosca(jmosca* pmosca);

    jpescado* getPescado();
    void setPescado(jpescado* ppescado);
    jescenario* escenario;

private:
	jventana* ventana;
	jconfiguracion* configuracion;
	//jescenario* escenario;
	jservidor* servidor;
	janillos* anillo;
	jpiedra* piedra;
	jpinche* pinche;
	jcangrejo* cangrejo;
	jmosca* mosca;
	jpescado* pescado;

};

} /* namespace std */

#endif /* JESCENARIOJUEGO_H_ */
