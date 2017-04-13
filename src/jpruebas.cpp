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
#include "ConexCliente.h"
#include "ConexServidor.h"


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

	cout << "CONFIGURACION" << endl;
	cout << "vel_scroll:" << parser->getConfiguracion()->getvelscroll() << endl;

	cout << "ESCENARIO" << endl;
	cout << "dimension-ancho:" << parser->getEscenario()->getancho() << endl;
	cout << "dimension-ancho:" << parser->getEscenario()->getalto() << endl;

	cout << "CAPAS" << endl;
	for(pos = capal.begin(); pos!=capal.end(); pos++){

        cout<< "capa-id:" << (*pos).getid()<<endl;
        cout<< "capa-index:" << (*pos).getindex()<<endl;
        cout<< "capa-ruta: " << (*pos).getrutaimagen()<<endl;


    }

	cout << "ESCENARIO" << endl;

	list<jentidades>::iterator iterEntidades;
	list<jentidades> lentidades = parser->getEscenario()->getentidades();
	for(iterEntidades = lentidades.begin(); iterEntidades!=lentidades.end(); iterEntidades++){
		cout<< "-----------------------------------" <<endl;
        cout<< "id:" << (*iterEntidades).getid()<<endl;
        cout<< "tipo:" << (*iterEntidades).gettipo() <<endl;
        cout<< "nombre valor1: " << (*iterEntidades).getDim()->getnombrevalor1()<<endl;
        cout<< "valor1: " << (*iterEntidades).getDim()->getvalor1()<<endl;
        cout<< "nombre valor1: " << (*iterEntidades).getDim()->getnombrevalor2()<<endl;
        cout<< "valor1: " << (*iterEntidades).getDim()->getvalor2()<<endl;
        cout<< "color: " << (*iterEntidades).getcolor()<<endl;
        cout<< "coordenada x: " << (*iterEntidades).getcoorx()<<endl;
        cout<< "coordenada y: " << (*iterEntidades).getcoory()<<endl;
        cout<< "ruta imagen: " << (*iterEntidades).getruta()<<endl;
        cout<< "index z: " << (*iterEntidades).getindex()<<endl;
    }


	}

void jpruebas::pruebasocket(){

  ConexServidor*  conexser = new ConexServidor();
  ConexCliente * conexcliente = new ConexCliente();

  char* message;
  int puerto = 3316;


  if (!conexcliente->crear()){
  	  cout<<"socket() error\n"<<endl;
   }

  int fdcliente = conexcliente->conectar(puerto);
  printf("ponga un mensaje : ");
  message = "Hola Patricia";

  if(!conexcliente->recibircliente(fdcliente,message)){
	  cout<<"Error en recv()"<<endl;
  }
  if(!conexcliente->enviarcliente(fdcliente,message)){
	  cout<<"error en env"<<endl;
  }



}



} /* namespace std */
