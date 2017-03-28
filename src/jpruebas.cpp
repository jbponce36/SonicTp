/*
 * jpruebas.cpp
 *
 *  Created on: 21 mar. 2017
 *      Author: pato
 */

#include "jpruebas.h"
#include <iostream>
#include </usr/include/SDL2/SDL.h>
#include <jansson.h>
#include "jventana.h"
#include "jconfiguracion.h"
#include "jescenario.h"
#include "capas.h"
#include "jentidades.h"
#include <list>
#include "dimensiones.h"
#include "parseadorJson.h"


namespace std {

jpruebas::jpruebas() {
	// TODO Auto-generated constructor stub

}

jpruebas::~jpruebas() {
	// TODO Auto-generated destructor stub
}

void jpruebas::prueba(jescenarioJuego* parser){

	list<capas>::iterator pos;
	list<capas> capal;
    capal =  parser->getEscenario()->getcapas();

    pos = capal.begin();


	cout << "VENTANA" << endl;
	cout << "ancho:" << parser->getVentana()->getancho() << endl;
	cout << "alto:" << parser->getVentana()->getalto() << endl;

	/*cout << "CONFIGURACION" << endl;
	cout << "vel_scroll:" << parser->getConfiguracion()->getvelscroll() << endl;

	cout << "ESCENARIO" << endl;
	cout << "dimension-ancho:" << parser->getEscenario()->getancho() << endl;
	cout << "dimension-ancho:" << parser->getEscenario()->getalto() << endl;
*/
	for(pos = capal.begin(); pos!=capal.end(); pos++){

        cout<< "escenario-id:" << (*pos).getid()<<endl;
        cout<< "escenario -index:" << (*pos).getindex()<<endl;
        cout<< "escenario -ruta: " << (*pos).getrutaimagen()<<endl;

       int h =  (*pos).getid();
    }

	/*cout << "ESCENARIO" << endl;
	cout << parser->getEscenario()->getentidades().size() << endl;
	list<jentidades>::iterator iterEntidades;
	list<jentidades> lentidades = parser->getEscenario()->getentidades();
	for(iterEntidades = lentidades.begin(); iterEntidades!=lentidades.end(); iterEntidades++){

        cout<< "entidad-id:" << (*iterEntidades).getid()<<endl;
        cout<< "entidad -tipo:" << (*iterEntidades).gettipo() <<endl;
        cout<< "entidad -nombre valor1: " << (*iterEntidades).getDim()->getnombrevalor1()<<endl;
        cout<< "entidad -valor1: " << (*iterEntidades).getDim()->getvalor1()<<endl;
        cout<< "entidad -nombre valor2: " << (*iterEntidades).getDim()->getnombrevalor2()<<endl;
        cout<< "entidad -valor2: " << (*iterEntidades).getDim()->getvalor2()<<endl;
        cout<< "entidad -color: " << (*iterEntidades).getcolor()<<endl;
        cout<< "entidad -coordenada x: " << (*iterEntidades).getcoorx()<<endl;
        cout<< "entidad -coordenada y: " << (*iterEntidades).getcoory()<<endl;
        cout<< "entidad -ruta imagen: " << (*iterEntidades).getruta()<<endl;
        cout<< "entidad -index z: " << (*iterEntidades).getindex()<<endl;
    }


*/

}

} /* namespace std */
