
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
    jventana *parseadorJson::cargarVentana(json_t *raiz)
    {
        json_t *jsonventana;
        json_t *jsonventanaalto;
        json_t *jsonventanaancho;
        bool esvalido;
        jventana *ventana = new jventana();
        esvalido = validarVentana(raiz, "ventana", "dimensiones", "alto", "ancho");

        if(esvalido){
        	this->log->addLogMessage("PARSEADOR JSON","[CONFIGURACION DE LA VENTANA] Iniciado.", 2);
            jsonventana = json_object_get(raiz, "ventana");
            jsonventana = json_object_get(jsonventana, "dimensiones");
            jsonventanaalto = json_object_get(jsonventana, "alto");
        	this->log->addLogMessage("PARSEADOR JSON","[CONFIGURACION DE LA VENTANA] Seteando alto.", 3);
            jsonventanaancho = json_object_get(jsonventana, "ancho");
        	this->log->addLogMessage("PARSEADOR JSON","[CONFIGURACION DE LA VENTANA] Seteando ancho.", 3);
            ventana->setalto(json_number_value(jsonventanaalto));
            ventana->setancho(json_number_value(jsonventanaancho));

            this->log->addLogMessage("PARSEADOR JSON","[CONFIGURACION DE LA VENTANA] Terminado.", 2);
        }else{
        	this->log->addLogMessage("PARSEADOR JSON","[CONFIGURACION DE LA VENTANA] No se han encontrado los atributos correctos, se cargaran valores por defecto", 1);
            ventana->setalto(480);
            ventana->setancho(640);


        }
        return ventana;
    }

parseadorJson::parseadorJson() {
	// TODO Auto-generated constructor stub
	//jconexion conexion2 = *conexion2.getinstance();
}

parseadorJson::parseadorJson(Logger *log) {
	this->log = log;

}


Logger* parseadorJson::getLog() const {
	return log;
}

void parseadorJson::setLog(Logger* log) {
	this->log = log;
}

parseadorJson::~parseadorJson() {
	// TODO Auto-generated destructor stub
}


bool parseadorJson::leerValorVentana(json_t *dimension, const char *ancho, const char *alto)
    {
        json_t *jsonancho;
        json_t *jsonalto;
        bool validarvent = true;
        jsonancho = json_object_get(dimension, ancho);
        jsonalto = json_object_get(dimension, alto);
        if((!jsonancho) && (!jsonalto)){
            validarvent = false;
        }
        if((!json_is_number(jsonancho)) && (!(json_is_number(jsonalto)))){
        	validarvent = false;
        	this->log->addLogMessage("PARSEADOR JSON","[CONFIGURACION DE LA VENTANA] Error obteniendo el valor de las dimensiones de la ventana", 1);
        }
        return validarvent;
    }


double parseadorJson::leerValorEntero(json_t* padre, const char* nombre,int valorPorDefecto){
	json_t *elemento;

	elemento = json_object_get(padre,nombre);

	if (!elemento){
		return valorPorDefecto;
	}

	if (!json_is_number(elemento)){
		return valorPorDefecto;
	}

	return json_number_value(elemento);

}

bool parseadorJson::tryLeerValorEntero(json_t* padre,
		const char* nombre,
		double* valorLeido
		){
	json_t *elemento;

	elemento = json_object_get(padre,nombre);

	if (!elemento){
		return false;
	}

	if (!json_is_number(elemento)){
		return false;
	}

	*valorLeido = json_number_value(elemento);
    return true;
}


bool parseadorJson::validarVentana(json_t* raiz,const char* nomvent,const char* nomdim,const char* nomancho,const char* nomalto){


	json_t *jsonventana;
    json_t *jsondimension;
    json_t *jsonancho;
    json_t *jsonalto;
    bool validarvent = true;

	jsonventana = json_object_get(raiz,nomvent);
	jsondimension = json_object_get(jsonventana,nomdim);
	jsonancho = json_object_get(jsondimension,nomancho);
	jsonalto = 	json_object_get(jsondimension,nomalto);


	if((!jsonventana)&&(!jsondimension)){

		validarvent = false;
	}
	else{
		validarvent = true;

	}

   if(json_number_value(jsonancho) && json_number_value(jsonalto)){
	  validarvent = true;
    }
   else{
	  validarvent = false;
   }

    return validarvent;
}

jconfiguracion* parseadorJson::cargarConfiguracion(json_t* raiz){

	 json_t *jsonconfiguracion;
	// json_t *jsonvelscrol;

	 jconfiguracion *configuracion = new jconfiguracion();


     jsonconfiguracion = json_object_get(raiz, "configuracion");
  //   jsonvelscrol = json_object_get(jsonconfiguracion, "vel_scroll");


      if((jsonconfiguracion)){


      configuracion->setvelscroll(this->leerValorEntero(jsonconfiguracion,"vel_scroll",15));


     }
      else{

    	  configuracion->setvelscroll(15);


       }
	 return configuracion;
}



std::string parseadorJson::leerValorStringCapas(json_t* padre,const char* nombre,std::string valorPorDefecto){

    json_t *elemento;

	elemento = json_object_get(padre,nombre);

	if (!elemento){
		return valorPorDefecto;

	}

	if (!json_is_string(elemento)){
		return valorPorDefecto;

	}

	return json_string_value(elemento);

}

jescenario* parseadorJson::cargarEscenario(json_t* raiz){

	    json_t *jsonescenario;

		json_t *jdimensiones;


		json_t *jcapas;


		jsonescenario = json_object_get(raiz, "escenario");

		jescenario *escenario = new jescenario();
		//VALIDO QUE ESTE BIEN EL ESCENARIO,DIMENSION,ANCHO Y ALTO


		jsonescenario = json_object_get(raiz, "escenario");

		if (jsonescenario){

			jdimensiones = json_object_get(jsonescenario,"dimensiones");
			if (jdimensiones){
				//Validacion:
				//Si uno de los dos esta mal tiene que dejar los dos por defecto
				double alto;
				double ancho;

				if (this->tryLeerValorEntero(jdimensiones,"alto",&alto)
				    && this->tryLeerValorEntero(jdimensiones,"ancho", &ancho) )
				{
					escenario->setalto(alto);
					escenario->setancho(ancho);
				}
			}
		}
		//Verificr lo que falta


		jcapas = json_object_get(jsonescenario, "capas");

		//lista de capas

		list<capas> capalista;

		if (jcapas){
			for( int i = 0; i < json_array_size(jcapas); i++ ){


			   json_t *capai;

			   capai = json_array_get(jcapas, i);

			   if (capai){
				   capas *jcapas = new capas();

				   jcapas->setid(this->leerValorEntero(capai,"id", 1));
				   jcapas->setindex(this->leerValorEntero(capai,"index_z",99));
				   jcapas->setrutaimagen(this->leerValorStringCapas(capai,"ruta_imagen","/images/capa1r.png"));

				   capalista.push_back(*jcapas);
			   }

		 	}
			escenario->setcapas(capalista);
	    }


		if (escenario->getcapas().size() == 0){
		      //si no encuentra la capa carga las dos capas por defecto
		      capalista = this->DevolverCapasPorDefecto();
		      escenario->setcapas(capalista);
		}


		// agrego la lista total al escenario



		 //ENTIDADES (viene de escenario)

		  json_t *jsonentidades;

		  jsonentidades = json_object_get(jsonescenario, "entidades");


		  list<jentidades> listaentidades;
		  if ((jsonentidades)){

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

				 if (entidadi){

					 entidades->setid(this->leerValorEntero(entidadi, "id", 1));
					 entidades->settipo(this->leerValorStringCapas(entidadi, "tipo", ""));
					 entidades->setcolor(this->leerValorStringCapas(entidadi, "color", "rojo"));

					 coordenada = json_object_get(entidadi,"coordenada");
					 if (coordenada){
						 double cordx;
						 double cordy;

						 if (this->tryLeerValorEntero(coordenada, "x", &cordx)
						     && this->tryLeerValorEntero(coordenada, "y", &cordy)){

							 entidades->setcoorx(cordx);
  						     entidades->setcoory(cordy);
						 }
					 }




					 dimensiones= json_object_get(entidadi,"dimensiones");
					 if (dimensiones){
								  // devuelve 0...si eel elemento no tiene algun atributo
						 //if (strcmp(entidades->gettipo()., "rectangulo") == 0){
						 if (entidades->gettipo().compare("rectangulo") == 0){

							 double ancho;
							 double alto;

							 jrectangulo* rectangulo = new jrectangulo();


							  if (this->tryLeerValorEntero(dimensiones, "ancho", &ancho)
								  && this->tryLeerValorEntero(dimensiones, "alto", &alto)){
								  rectangulo->setalto(ancho);
								  rectangulo->setancho(alto);
							  }

							  rectangulo->settipo2("rectangulo");
							  entidades->setDim(rectangulo);
						  }

						  //if(strcmp(json_string_value(tipo),"circulo") == 0){
						 if (entidades->gettipo().compare("circulo") == 0){

							 double radio;
							 jcirculo*  circulo = new jcirculo();
							 if (this->tryLeerValorEntero(dimensiones,"radio", &radio)){
								 circulo->setradio(radio);
							 }

							 circulo->settipo2("circulo");
							 entidades->setDim(circulo);
						  }
					 }else{ //if (dimensiones)

						 if (entidades->gettipo().compare("rectangulo") == 0){
 							  jrectangulo* rectangulo = new jrectangulo();
							  rectangulo->settipo2("rectangulo");
							  entidades->setDim(rectangulo);
						  }

						  //if(strcmp(json_string_value(tipo),"circulo") == 0){
						 if (entidades->gettipo().compare("circulo") == 0){
							 jcirculo*  circulo = new jcirculo();
							 circulo->settipo2("circulo");
							 entidades->setDim(circulo);
						  }

					 }



					 entidades->setruta(this->leerValorStringCapas(entidadi,"ruta_imagen", "/imagenes/entidad1.png"));
  				     entidades->setindex(this->leerValorEntero(entidadi, "index_z", 99));

					 if (entidades->esValida()){
					   listaentidades.push_back(*entidades);
					}
				 }//if etidadi
			  }//for

			  escenario->setentidades(listaentidades);

		  }//if ((jsonentidades))

		  if (escenario->getentidades().size() == 0){
			  listaentidades = this->DevolverEntidadesPorDefecto();
			  escenario->setentidades(listaentidades);
		  }

		  return escenario;
}

jescenarioJuego* parseadorJson::parsearArchivo(char* nombreArchivo){

	 json_t *json;
	 json_error_t error;

	 json = json_load_file(nombreArchivo,0,&error);

	  if(!json) {
	       cout << "!!! hay  probremas!!!" << endl;
	       cout << error.text << endl;
	       cout << "Cargando archivo por defecto" << endl;
	       json = json_load_file("configuracion/default.json",0,&error);
	       if (!json){
		       cout << "!!! no existe el archivo por defecto!!!" << endl;
		       cout << error.text << endl;
		       cout << "Cargando archivo por defecto" << endl;

		       return NULL;
	       }
	  }

        jventana *ventana = cargarVentana(json);
        jconfiguracion *config = cargarConfiguracion(json);
        jescenario *escenario = cargarEscenario(json);
        jescenarioJuego *result = new jescenarioJuego();
        result->setVentana(ventana);
        result->setEscenario(escenario);
        result->setConfiguracion(config);
        this->log->addLogMessage("PARSEADOR JSON","Se termino de leer el archivo de configuracion.", 2);
        return result;
    }

list<capas> parseadorJson::DevolverCapasPorDefecto(){

	list<capas>capasdefault;

	capas *jcapas1 = new capas();
	capas *jcapas2 = new capas();

	jcapas1->setid(1);
	jcapas1->setindex(99);
	jcapas1->setrutaimagen("images/capa0.png");

	jcapas2->setid(2);
	jcapas2->setindex(98);
	jcapas2->setrutaimagen("images/capa1r.png");

	capasdefault.push_back(*jcapas1);
	capasdefault.push_back(*jcapas2);

	return capasdefault;

}

list<jentidades> parseadorJson::DevolverEntidadesPorDefecto(){

	list<jentidades>entidadesdefault;

	jentidades *entidades1 = new jentidades();
	jentidades *entidades2 = new jentidades();
	jentidades *entidades3 = new jentidades();

	entidades1->setid(1);
	entidades1->settipo("rectangulo");
	entidades1->setcolor("rojo");

	jrectangulo *rectangulo1 = new jrectangulo();
    rectangulo1->setalto(20);
    rectangulo1->setancho(40);
	rectangulo1->settipo2("rectangulo");
	entidades1->setDim(rectangulo1);

    entidades1->setcoorx(100);
    entidades1->setcoory(100);
    entidades1->setruta("/images/entidad1.png");
    entidades1->setindex(99);

    entidadesdefault.push_back(*entidades1);

    entidades2->setid(2);
    entidades2->settipo("rectangulo");
    entidades2->setcolor("verde");

    jrectangulo *rectangulo2 = new jrectangulo();
    rectangulo2->setalto(35);
    rectangulo2->setancho(80);
    rectangulo2->settipo2("rectangulo");
    entidades2->setDim(rectangulo2);

    entidades2->setcoorx(200);
    entidades2->setcoory(200);
    entidades2->setruta("/images/entidad2.png");
    entidades2->setindex(99);

    entidadesdefault.push_back(*entidades2);

    entidades3->setid(3);
    entidades3->settipo("circulo");
    entidades3->setcolor("amarillo");

    jcirculo* circulo = new jcirculo();
    circulo->setradio(15);
    circulo->settipo2("circulo");
    entidades3->setDim(circulo);

    entidades3->setcoorx(300);
    entidades3->setcoory(300);
    entidades3->setruta("/images/entidad3.png");
    entidades3->setindex(99);

    entidadesdefault.push_back(*entidades3);

    return entidadesdefault;
}
jescenarioJuego* parseadorJson::getescenario(){
	return juego;
}
} /* namespace std */
