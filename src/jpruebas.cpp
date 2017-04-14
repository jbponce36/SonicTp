/*
 * jpruebas.cpp
 *
 *  Created on: 21 mar. 2017
 *      Author: pato
 */

#include "jpruebas.h"

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

  Sockets *conexser = new Sockets();
  Sockets *conexcliente = new Sockets();

  char* message;
  int puerto = 8080;
  int status = conexser->crear();

  if (status<0){
  	  cout<<"socket() error\n"<<endl;
  }

  status = conexser->enlazar(puerto);

  if (status<0){
  	  cout<<"socket() error\n"<<endl;
  }

  status = conexser->escuchar();

  if (status<0){
  	  cout<<"socket() error\n"<<endl;
  }

  status = conexser->aceptarcliente(conexcliente);

  if (status<0){
  	  cout<<"error \n"<<endl;
  }

  //int fdcliente = conexcliente->conectar(hostname,puerto);




  conexcliente->cerrar();
  conexser->cerrar();
}



} /* namespace std */
