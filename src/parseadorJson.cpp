/*
 * parseadorJson.cpp
 *
 *  Created on: 20 mar. 2017
 *      Author: pato
 */

#include <iostream>
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
#include <string>



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
            this->log->addLogMessage("[CARGAR VENTANA] Iniciado.", 2);
            jsonventana = json_object_get(raiz, "ventana");
            jsonventana = json_object_get(jsonventana, "dimensiones");
            jsonventanaalto = json_object_get(jsonventana, "alto");
            jsonventanaancho = json_object_get(jsonventana, "ancho");
            ventana->setalto(json_number_value(jsonventanaalto));
            ventana->setancho(json_number_value(jsonventanaancho));
            this->log->addLogMessage("[CARGAR VENTANA] Ventana-> "+ventana->toString(),3);
            this->log->addLogMessage("[CARGAR VENTANA] Terminado.", 2);
        }else{
            ventana->setalto(480);
            ventana->setancho(640);
            this->log->addLogMessage("[CARGAR VENTANA] Alto: 480, Ancho:640.", 3);
        }
        return ventana;
    }

parseadorJson::parseadorJson() {
	// TODO Auto-generated constructor stub
	//jconexion conexion2 = *conexion2.getinstance();
	this->raiz = NULL;
}

parseadorJson::parseadorJson(Logger *log) {
	this->log = log;
	this->log->setModulo("PARSEADOR JSON");
}


Logger* parseadorJson::getLog() const {
	return log;
}

void parseadorJson::setLog(Logger* log) {
	this->log = log;
	this->log->setModulo("PARSEADOR JSON");
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
        	this->log->addLogMessage("[CONFIGURACION DE LA VENTANA] Error obteniendo el valor de las dimensiones de la ventana", 1);
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

    this->log->addLogMessage("[VALIDAR VENTANA] Iniciado.", 2);
	jsonventana = json_object_get(raiz,nomvent);
	jsondimension = json_object_get(jsonventana,nomdim);
	jsonancho = json_object_get(jsondimension,nomancho);
	jsonalto = 	json_object_get(jsondimension,nomalto);

	if((!jsonventana)&&(!jsondimension)){
		this->log->addLogMessage("[VALIDAR VENTANA] ERROR. No se encontro el atributo dimensiones dentro de ventana. Se cargaron dimensiones por defecto.", 1);
		validarvent = false;
	}
	else{
		validarvent = true;
	}

   if(json_number_value(jsonancho) && json_number_value(jsonalto)){
	  validarvent = true;
	  this->log->addLogMessage("[VALIDAR VENTANA]Ventana valida", 3);
    }
   else{
	  validarvent = false;
	  this->log->addLogMessage("[VALIDAR VENTANA] ERROR. Alto y/o ancho no son numeros.Se cargaron dimesiones por default", 1);
   }

   this->log->addLogMessage("[VALIDAR VENTANA] Terminado.", 2);
   return validarvent;
}

jconfiguracion* parseadorJson::cargarConfiguracion(json_t* raiz){

	 json_t *jsonconfiguracion;
	// json_t *jsonvelscrol;

	 jconfiguracion *configuracion = new jconfiguracion();

     jsonconfiguracion = json_object_get(raiz, "configuracion");
     this->log->addLogMessage("[CARGAR VELOCIDAD DE SCROLL] Iniciado.", 2);

  //   jsonvelscrol = json_object_get(jsonconfiguracion, "vel_scroll");

     if((jsonconfiguracion)){
    	 configuracion->setvelscroll(this->leerValorEntero(jsonconfiguracion,"vel_scroll",500));
     }
     else{
    	 this->log->addLogMessage("[CARGAR VELOCIDAD DE SCROLL] Error, no se encontro el atributo configuracion. Se carga un valor de velocidad de scroll por defecto.", 1);
    	 configuracion->setvelscroll(15);
     }

     this->log->imprimirMensajeNivelAlto("[CARGAR VELOCIDAD DE SCROLL] Velocidad de scroll: ", configuracion->getvelscroll());
     this->log->addLogMessage("[CARGAR VELOCIDAD DE SCROLL] Terminado.", 2);
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
	this->log->addLogMessage("[CARGAR ESCENARIO] Iniciado.",2);
	jescenario *escenario = new jescenario();
	//VALIDO QUE ESTE BIEN EL ESCENARIO,DIMENSION,ANCHO Y ALTO

	if (jsonescenario){
		jdimensiones = json_object_get(jsonescenario,"dimensiones");
		if (jdimensiones){
			//Validacion:Si uno de los dos esta mal tiene que dejar los dos por defecto
			double alto, ancho;

			if (this->tryLeerValorEntero(jdimensiones,"alto",&alto)
				&& this->tryLeerValorEntero(jdimensiones,"ancho", &ancho) ){
				escenario->setalto(alto);
				escenario->setancho(ancho);
			}
		}
	}
	else{
		this->log->addLogMessage("[CARGAR ESCENARIO] Error, no se encontro el atributo dimensiones dentro de escenario. Se cargaran sus dimensiones por defecto.",1);
	}

	this->log->addLogMessage("[CARGAR ESCENARIO] Escenario ->"+ escenario->toString() ,3);

	//Verificr lo que falta
	jcapas = json_object_get(jsonescenario, "capas");
	this->log->addLogMessage("[CARGAR CAPAS] Iniciado.",2);
	list<capas> capalista;

	if (jcapas){
		for( int i = 0; i < json_array_size(jcapas); i++ ){
		   json_t *capai;
		   capai = json_array_get(jcapas, i);

		   if (capai){
			   capas *jcapas = new capas();
			   int id = 0, index_z = 0; string ruta = "";

			   if (i == 0){
				   ruta = "images/capa0.png";
				   index_z = 99;
			   }
			   if (i == 1){
				   ruta = "images/capa1r.png";
				   index_z = 98;
			   }

			   jcapas->setid(this->leerValorEntero(capai,"id", id));
			   jcapas->setindex(this->leerValorEntero(capai,"index_z",index_z));
			   jcapas->setrutaimagen(this->leerValorStringCapas(capai,"ruta_imagen",ruta));
			   capalista.push_back(*jcapas);
			   this->log->addLogMessage("[CARGAR CAPAS] Capa-> " + jcapas->toString(),3);
		   }
		}
		escenario->setcapas(capalista);
	}

	if (escenario->getcapas().size() == 0){
		this->log->addLogMessage("[CARGAR CAPAS] Error, no se encontro el atributo capas dentro de escenario. Se cargaran capas por defecto.", 1);
		//si no encuentra la capa carga las dos capas por defecto
		capalista = this->DevolverCapasPorDefecto();
		escenario->setcapas(capalista);
	}
	this->log->setModulo("PARSEADOR JSON");
	this->log->addLogMessage("[CARGAR CAPAS] Terminado.\n",2);
	// agrego la lista total al escenario

	//ENTIDADES (viene de escenario)
	json_t *jsonentidades;
	jsonentidades = json_object_get(jsonescenario, "entidades");
	this->log->addLogMessage("[CARGAR ENTIDADES] Iniciado.",2);
	list<jentidades> listaentidades;
	if ((jsonentidades)){
		for( int i = 0; i < json_array_size(jsonentidades); i++ ){
			json_t *entidadi;
			json_t *dimensiones;
			json_t *coordenada;

			//voy creando nuevos objetos entidades
			jentidades *entidades = new jentidades();

			entidadi = json_array_get(jsonentidades, i);
			if (entidadi){
				entidades->setid(this->leerValorEntero(entidadi, "id", 1));
				entidades->settipo(this->leerValorStringCapas(entidadi, "tipo", ""));
				entidades->setcolor(this->leerValorStringCapas(entidadi, "color", "rojo"));
				coordenada = json_object_get(entidadi,"coordenada");

				if (coordenada){
					double cordx,cordy;

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
					if ((entidades->gettipo().compare("rectangulo") == 0)|| (entidades->gettipo().compare("cuadrado") == 0)  ){
						double ancho;
						double alto;

						jrectangulo* rectangulo = new jrectangulo();
						if (this->tryLeerValorEntero(dimensiones, "ancho", &ancho)
						  && this->tryLeerValorEntero(dimensiones, "alto", &alto)){
						  rectangulo->setalto(alto);
						  rectangulo->setancho(ancho);
						}

						rectangulo->settipo2("rectangulo");
						entidades->setDim(rectangulo);
					}
						 //aca va el cuadrado
						  if (entidades->gettipo().compare("cuadrado") == 0){
							  double ancho;
							  double alto;

							  jcuadrado* cuadrado = new jcuadrado();

							  if (this->tryLeerValorEntero(dimensiones, "ancho", &ancho)
							  	  && this->tryLeerValorEntero(dimensiones, "alto", &alto)){
							  	  cuadrado->setalto(alto);
							  	  cuadrado->setancho(ancho);
							  }
							  cuadrado->settipo2("cuadrado");
							  entidades->setDim(cuadrado);
						  }
						 //fin cuadrado
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
						 //cuadrado
						 if(entidades->gettipo().compare("cuadrado") == 0){
							 jcuadrado* cuadrado = new jcuadrado();

                             cuadrado->settipo2("cuadrado");
                             entidades->setDim(cuadrado);

						 }//fin cuadrado
					 }

				entidades->setruta(this->leerValorStringCapas(entidadi,"ruta_imagen", "/images/entidaddefault.png"));
				entidades->setindex(this->leerValorEntero(entidadi, "index_z", 99));

				if (entidades->esValida()){
					listaentidades.push_back(*entidades);
					this->log->addLogMessage("[CARGAR ENTIDADES] Entidad-> "+entidades->toString(),3);
				}
			}//if etidadi
		}//for

		escenario->setentidades(listaentidades);

	}//if ((jsonentidades))

	if (escenario->getentidades().size() == 0){
		this->log->addLogMessage("[CARGAR ENTIDADES] Error, no se encontro el atributo entidades dentro de escenario. Se cargaran entidades por defecto.",1);
		listaentidades = this->DevolverEntidadesPorDefecto();
		escenario->setentidades(listaentidades);
	}

	this->log->addLogMessage("[CARGAR ENTIDADES] Terminado.",2);
	this->log->addLogMessage("[CARGAR ESCENARIO] Terminado.",2);
	return escenario;
}

jescenarioJuego* parseadorJson::parsearArchivo(char* nombreArchivo){

	 json_t *json;
	 json_error_t error;

	 this->log->addLogMessage("[PARSEAR ARCHIVO] Iniciado.", 2);
	 json = json_load_file(nombreArchivo,0,&error);
       //nuevo
	   this->setraiz(json);
	   //
	  if(!json) {
	       cout << "!!! hay  probremas!!!" << endl;
	       cout << error.text << endl;
	       this->log->addLogMessage("[PARSEAR ARCHIVO] [ERROR] No se encontro el archivo o directorio.", 1);
	       cout << "Cargando archivo por defecto" << endl;
	       json = json_load_file("configuracion/default.json",0,&error);
	       //nuevo
	       this->setraiz(json);
	       //nuevo
	       this->log->addLogMessage("[PARSEAR ARCHIVO] Se carga un archivo por defecto: configuracion/default.json .", 1);
	       if (!json){
		       cout << "!!! no existe el archivo por defecto!!!" << endl;
		       cout << error.text << endl;
		       this->log->addLogMessage("[PARSEAR ARCHIVO] No existe el archivo o directorio por defecto.", 1);
		       return NULL;
	       }
	  }

        jventana *ventana = cargarVentana(json);
        jconfiguracion *config = cargarConfiguracion(json);
        jescenario *escenario = cargarEscenario(json);
        jservidor* servidor = this->cargarServidor(json);
        jescenarioJuego *result = new jescenarioJuego();

        result->setVentana(ventana);
        result->setEscenario(escenario);
        result->setConfiguracion(config);
        result->setServidor(servidor);

        validarDimensionesVentana(result);
        this->log->addLogMessage("[PARSEAR ARCHIVO] Terminado. \n", 2);
        return result;
    }

list<capas> parseadorJson::DevolverCapasPorDefecto(){

	list<capas>capasdefault;

	capas *jcapas1 = new capas();
	capas *jcapas2 = new capas();

	jcapas1->setid(1);
	jcapas1->setindex(99);
	jcapas1->setrutaimagen("images/capa0.png");
	this->log->addLogMessage("[CARGAS CAPAS] Capa 1-> id:1, index_z: 99, ruta_imagen: images/capa0.png  ", 3);

	jcapas2->setid(2);
	jcapas2->setindex(98);
	jcapas2->setrutaimagen("images/capa1r.png");
	this->log->addLogMessage("[CARGAS CAPAS] Capa 2-> id:2, index_z: 98, ruta_imagen: images/capa1r.png  ", 3);

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
    this->log->addLogMessage("[CARGAR ENTIDADES] Entidad 1-> id: 1, tipo: rectangulo, color: rojo, dimesiones->( alto: 20, ancho: 40), (coordenadas-> x:100, y:100)",3);

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
    this->log->addLogMessage("[CARGAR ENTIDADES] Entidad 2-> id: 2, tipo: rectangulo, color: verde, dimesiones->( alto: 35, ancho: 80), (coordenadas-> x:200, y:200)",3);

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
    this->log->addLogMessage("[CARGAR ENTIDADES] Entidad 1-> id: 3, tipo: circulo, color: amarillo, dimesiones-> radio: 15, (coordenadas-> x:300, y:300)",3);

    return entidadesdefault;
}
jescenarioJuego* parseadorJson::getescenario(){
	return juego;
}

void parseadorJson::validarDimensionesVentana(jescenarioJuego *escenarioJuego){
	this->log->addLogMessage("[VALIDAR DIMENSIONES DE LA VENTANA] Iniciado.", 2 );
    if(escenarioJuego->getEscenario()->getancho() < escenarioJuego->getVentana()->getancho()){

    	//escenarioJuego->getEscenario()->setancho(escenarioJuego->getVentana()->getancho());
   }

	this->log->addLogMessage("[VALIDAR DIMENSIONES DE LA VENTANA] Terminado.", 2 );

}

int parseadorJson::CargarPuertoServidor(){

	json_t* raiz;
	json_t *jsonservidor;
	json_t *jsonpuerto;


    raiz = this->getraiz();
	jsonservidor = json_object_get(raiz, "servidor");
	jsonpuerto = json_object_get(jsonservidor, "puerto");

	int puerto = json_number_value(jsonpuerto);

	return puerto;

}

int parseadorJson::CargarCantClientes(){

	json_t* raiz;
	json_t *jsonservidor;
    json_t *jsoncantclientes;

    int cantclientes;

    raiz = this->getraiz();
	jsonservidor = json_object_get(raiz, "servidor");
	jsoncantclientes = json_object_get(jsonservidor, "clientes");

	cantclientes = json_number_value(jsoncantclientes);

	return cantclientes;
}

jservidor* parseadorJson::cargarServidor(json_t* raiz){

	json_t *jsonservidor;
	json_t *jsonpuerto;
    json_t *jsonclientes;

	jservidor* server = new jservidor();

	jsonservidor = json_object_get(raiz, "servidor");
	jsonpuerto = json_object_get(jsonservidor, "puerto");
	jsonclientes = json_object_get(jsonservidor,"clientes");

	server->setPuerto(json_number_value(jsonpuerto));
    server->setCantclientes(json_number_value(jsonclientes));

    return server;

}

json_t* parseadorJson::getraiz(){
	return raiz;
}

void parseadorJson::setraiz(json_t* Raiz){
	raiz = Raiz;
}

} /* namespace std */
