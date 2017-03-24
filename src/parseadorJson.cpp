/*
 * parseadorJson.cpp
 *
 *  Created on: 20 mar. 2017
 *      Author: pato
 */

#include <iostream>
#include </usr/include/SDL2/SDL.h>
#include <jansson.h>
#include "jventana.h"
#include "jconfiguracion.h"
#include "jescenario.h"
#include "capas.h"
#include "jentidades.h"
#include <list>
#include "parseadorJson.h"
#include "dimensiones.h"
#include "jrectangulo.h"
#include "jcirculo.h"



namespace std {



parseadorJson::parseadorJson() {
	// TODO Auto-generated constructor stub
	//jconexion conexion2 = *conexion2.getinstance();
}

parseadorJson::~parseadorJson() {
	// TODO Auto-generated destructor stub
}



jventana* parseadorJson::cargarVentana(json_t* raiz){

    json_t *jsonventana;
    json_t *jsonventanaalto;
    json_t *jsonventanaancho;

    jsonventana = json_object_get(raiz, "ventana");
    jsonventana = json_object_get(jsonventana,"dimensiones");

    jsonventanaalto = json_object_get(jsonventana,"alto");
    jsonventanaancho = json_object_get(jsonventana,"ancho");


    jventana *ventana = new jventana();

    ventana->setalto(json_number_value(jsonventanaalto));
    ventana->setancho(json_number_value(jsonventanaancho));

    return ventana;

}

jconfiguracion* parseadorJson::cargarConfiguracion(json_t* raiz){

	 json_t *jsonconfiguracion;

	 jsonconfiguracion = json_object_get(raiz, "configuracion");
	 jsonconfiguracion = json_object_get(jsonconfiguracion, "vel_scroll");

	 jconfiguracion *configuracion = new jconfiguracion();

	 configuracion->setvelscroll(json_number_value( jsonconfiguracion));

	 return configuracion;
}

jescenario* parseadorJson::cargarEscenario(json_t* raiz){

	json_t *jsonescenario;

	json_t *jdimensiones;
	json_t *jd_alto;
	json_t *jd_ancho;

	json_t *jcapas;

	jescenario *escenario = new jescenario();

	jsonescenario = json_object_get(raiz, "escenario");
	jdimensiones = json_object_get(jsonescenario,"dimensiones");
	jd_alto = json_object_get(jdimensiones,"alto");
	jd_ancho = json_object_get(jdimensiones,"ancho");

	escenario->setalto(json_number_value(jd_alto));
	escenario->setancho(json_number_value(jd_ancho));

	//cout<<escenario->getalto()<<endl;
	//cout<<escenario->getancho()<<endl;

	jcapas = json_object_get(jsonescenario, "capas");

	//lista de capas
	list<capas> capalista;
	//iterador de capas
	list<capas>::iterator pos;


	for( int i = 0; i < json_array_size(jcapas); i++ ){

	   json_t *capai;
	   json_t *id;
	   json_t *index_z;
	   json_t *ruta_imagen;

	   capai = json_array_get(jcapas, i);

	   capas *jcapas = new capas();

	   id = json_object_get(capai,"id");
	   index_z = json_object_get(capai,"index_z");
	   ruta_imagen = json_object_get(capai,"ruta_imagen");

	   jcapas->setid(json_number_value(id));
	   jcapas->setindex(json_number_value(index_z));
	   jcapas->setrutaimagen(json_string_value(ruta_imagen));


	   capalista.push_back(*jcapas);



	}


	 // agrego la lista total al escenario

	 escenario->setcapas(capalista);




	  //ENTIDADES (viene de escenario)

	  json_t *jsonentidades;

	  jsonentidades = json_object_get(jsonescenario, "entidades");

	  list<jentidades> listaentidades;
	   for( int i = 0; i < json_array_size(jsonentidades); i++ ){

		   json_t *entidadi;

		   json_t *id;
		   json_t *tipo;
		   json_t *color;
		   json_t *ruta_imagen;
		   json_t *index_z;
		   json_t *dimensiones;
		   json_t *ancho;
		   json_t *alto;
		   json_t *radio;
		   json_t *coordenada;
		   json_t *coorx;
		   json_t *coory;

	              //voy creando nuevos objetos entidades
	       jentidades *entidades = new jentidades();

	       entidadi = json_array_get(jsonentidades, i);

	       id = json_object_get(entidadi,"id");
	       entidades->setid(json_number_value(id));

	       tipo = json_object_get(entidadi,"tipo");
	       entidades->settipo(json_string_value(tipo));

	       color = json_object_get(entidadi,"color");
	       entidades->setcolor(json_string_value(color));

	       dimensiones= json_object_get(entidadi,"dimensiones");
	              // devuelve 0...si eel elemento no tiene algun atributo
	       ancho = json_object_get(dimensiones,"ancho");
	       alto = json_object_get(dimensiones,"alto");
	       radio = json_object_get(dimensiones,"radio");

	       if (strcmp(json_string_value(tipo), "rectangulo") == 0){
            const char* rect = "rectangulo";


	           jrectangulo* rectangulo = new jrectangulo();
	           rectangulo->setalto(json_number_value(alto));
	           rectangulo->setancho(json_number_value(ancho));
	           rectangulo->settipo2(rect);
               entidades->setDim(rectangulo);


	        }

	       if(strcmp(json_string_value(tipo),"circulo") == 0){
	    	   const char* circ = "circulo";
	    	   jcirculo*  circulo = new jcirculo();
	    	   circulo->setradio(json_number_value(radio));
	    	   circulo->settipo2(circ);
               entidades->setDim(circulo);

	        }

	        coordenada = json_object_get(entidadi,"coordenada");
	        coorx = json_object_get(coordenada,"x");
	        entidades->setcoorx(json_number_value(coorx));

	        coory = json_object_get(coordenada,"y");
	        entidades->setcoory((json_number_value(coory)));

	        ruta_imagen = json_object_get(entidadi,"ruta_imagen");
	        entidades->setruta(json_string_value(ruta_imagen));

	        index_z= json_object_get(entidadi,"index_z");
	        entidades->setindex(json_number_value(index_z));

	        listaentidades.push_back(*entidades);



	          }


	           escenario->setentidades(listaentidades);

	           return escenario;

}

jescenarioJuego* parseadorJson::parsearArchivo(char* nombreArchivo){

	 json_t *json;
	 json_error_t error;

	 json = json_load_file(nombreArchivo,0,&error);



	  if(!json) {

	       cout << "!!! hay  probremas!!!" << endl;
	       cout << error.text << endl;
	       return NULL;
	  }

	   jventana* ventana = cargarVentana(json);
	   jconfiguracion* config = cargarConfiguracion(json);
	   jescenario* escenario = cargarEscenario(json);

	   jescenarioJuego* result = new jescenarioJuego();

	   result->setVentana(ventana);
	   result->setEscenario(escenario);
	   result->setConfiguracion(config);

	   return result;

 }


} /* namespace std */
