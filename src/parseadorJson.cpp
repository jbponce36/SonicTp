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

parseadorJson::parseadorJson(Logger *log) {
	this->log = log;
	this->banderacapas = 0;

}

parseadorJson::~parseadorJson() {
	// TODO Auto-generated destructor stub
}



jventana* parseadorJson::cargarVentana(json_t* raiz){

	   json_t *jsonventana;
	    json_t *jsonventanaalto;
	    json_t *jsonventanaancho;
	    bool esvalido;

	    jventana *ventana = new jventana();

	    esvalido = validarVentana(raiz,"ventana","dimensiones","alto","ancho");

	    if(esvalido){

	    jsonventana = json_object_get(raiz, "ventana");
	    jsonventana = json_object_get(jsonventana,"dimensiones");

	    jsonventanaalto = json_object_get(jsonventana,"alto");
	    jsonventanaancho = json_object_get(jsonventana,"ancho");


	    ventana->setalto(json_number_value(jsonventanaalto));
	    ventana->setancho(json_number_value(jsonventanaancho));

	    //cout<<"ventana archivo"<<endl;
	    //cout<<ventana->getalto()<<endl;
	    //cout<<ventana->getancho()<<endl;

	    }
	    else
	    {

	      ventana->setalto(600);
	      ventana->setancho(3600);
	      //cout<<"ventana defecto"<<endl;
	      //cout<<ventana->getalto()<<endl;
	      //cout<<ventana->getancho()<<endl;
	    }

	    return ventana;

}

double parseadorJson::leerValorEnteroaux(json_t* padre, const char* nombre,int valorPorDefecto){


	    json_t *elemento;

		elemento = json_object_get(padre,nombre);

		if (!elemento){
			banderacapas = 1;
			return valorPorDefecto;
		}

		if (!json_is_number(elemento)){
			banderacapas = 1;
			return valorPorDefecto;
		}

		if (banderacapas == 1){
			return valorPorDefecto;
		}
		return json_number_value(elemento);
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

void parseadorJson::validarEntidadesEscenario(json_t* raizentidad,const char* id,const char* tipo,const char* color,const char* dim,const char* coor,const char* ruta,const char* index){

	json_t *jsonentidades;
    json_t *jsonid;
    json_t *jsontipo;
    json_t *jsoncolor;
    json_t *jsondimensiones;
    json_t *jsoncoordenadas;
    json_t *jsonrutaimagen;
    json_t *jsonindex;


    bool validarentesc = true;

	//VER QUE PASA CON ENTIDADES SI ESTA MAL!!!
	jsonentidades = json_object_get(raizentidad, "entidades");
	jsonid = json_object_get(jsonentidades,id);
	jsontipo = json_object_get(jsonentidades,tipo);
	jsoncolor = json_object_get(jsonentidades,color);
	jsondimensiones = json_object_get(jsonentidades,dim);
	jsoncoordenadas = json_object_get(jsoncoordenadas,coor);
	jsonrutaimagen = json_object_get(jsoncoordenadas,ruta);
	jsonindex = json_object_get(jsoncoordenadas,index);

	if((!jsonid)&&(!jsontipo)&&(jsoncolor)&&(jsondimensiones)&&(jsoncoordenadas)&&(jsonrutaimagen)&&(jsonindex)){
		validarentesc = false;

	}
	else{
		validarentesc = true;
	}

	 //if(json_number_value(jsonancho) && (json_number_value(jsonalto))){
}

bool parseadorJson::validarEscenario(json_t*raiz,const char* nomesce,const char* nomdim,const char* ancho,const char* alto){

	json_t *jsonescenario;
    json_t *jsondimensiones;
    json_t *jsonalto;
    json_t *jsonancho;


    bool valesce = true;

	jsonescenario = json_object_get(raiz,nomesce);
	jsondimensiones = json_object_get(jsonescenario,nomdim);

    jsonalto = json_object_get(jsondimensiones,alto);
	jsonancho = json_object_get(jsondimensiones,ancho);

	if((!jsonescenario)&&(!jsondimensiones)){
		valesce =false;


	}
	else{
		valesce = true;

	}

	 if(json_number_value(jsonancho) && (json_number_value(jsonalto))){
		 valesce = true;


	 }
	 else{
		 valesce =false;

	 }

    return valesce;

}


jconfiguracion* parseadorJson::cargarConfiguracion(json_t* raiz){


	 json_t *jsonconfiguracion;
	 json_t *jsonvelscrol;

	 jconfiguracion *configuracion = new jconfiguracion();


     jsonconfiguracion = json_object_get(raiz, "configuracion");
     jsonvelscrol = json_object_get(jsonconfiguracion, "vel_scroll");

      if((jsonconfiguracion)&&(jsonvelscrol)){


      configuracion->setvelscroll(this->leerValorEntero(jsonconfiguracion,"vel_scroll",20));


       //cout<< "valor configuracion archivo"<<endl;
       //cout<<configuracion->getvelscroll()<<endl;
     }
      else{

    	  configuracion->setvelscroll(20);
    	  //cout<< "valor configuracion def"<<endl;
    	 // cout<<configuracion->getvelscroll()<<endl;
       }
	 return configuracion;
}

void parseadorJson::ValidarCapas(json_t*raiz,list<capas>ca){





}

std::string parseadorJson::leerValorStringCapas(json_t* padre,const char* nombre,std::string valorPorDefecto){

    json_t *elemento;

	elemento = json_object_get(padre,nombre);

	if (!elemento){
		return valorPorDefecto;
		banderacapas = 1;
	}

	if (!json_is_string(elemento)){
		return valorPorDefecto;
		banderacapas = 1;
	}

	if (banderacapas == 1){
		return valorPorDefecto;
	}
	return json_string_value(elemento);

}
int parseadorJson::leerEntidadid(json_t* entidad,const char* nombre){

  json_t *id;
  int esvalido = 1;

  id = json_object_get(entidad,nombre);

  if((!id)){
   esvalido = 0;
  }

  if(!json_number_value(id)){
   esvalido = 0;
  }

  return esvalido;
}

int parseadorJson::leerEntidadtipo(json_t* entidad,const char* nombre){
  json_t *tipo;
  int esvalido = 1;

  tipo = json_object_get(entidad,nombre);

  if((!tipo)){
	esvalido = 0;
  }

  if (!json_is_string(tipo))  {
	  esvalido = 0;
  }

  if((!json_string_value(tipo)) && (json_string_value(tipo) != "rectangulo") && (json_string_value(tipo) != "circulo")){
	 esvalido = 0;
  }

	return esvalido;
}

int parseadorJson::leerEntidadcolor(json_t* entidad,const char* nombre){

	json_t *color;
	int esvalido = 1;

	color = json_object_get(entidad,nombre);

	if(!color){
		esvalido = 0;
	}

	if((!json_string_value(color)) && (json_string_value(color) != "amarillo") && (json_string_value(color) != "rojo")){
		   esvalido = 0;
	}

	 return esvalido;
}

int parseadorJson::leerEntidaddimensionr(json_t* entidad,const char* nombred,const char* nombrean,const char* nombreal){

	json_t *dimension;
	json_t *alto;
	json_t *ancho;

	int esvalido = 1;

    dimension = json_object_get(entidad,nombred);
    ancho = json_object_get(dimension,nombrean);
    alto = json_object_get(dimension,nombreal);

    if((!dimension) && (!alto) && (!ancho)){
    	esvalido = 0;
    }

    if(!json_is_number(ancho)){
       	esvalido = 0;
    }

    if(!json_is_number(alto)){
       	esvalido = 0;
    }


  return esvalido;
}

int parseadorJson::leerEntidaddimensionc(json_t* entidad,const char* nombred,const char* nombrer){
	json_t *dimension;
    json_t *radio;

    int esvalido = 1;

    dimension = json_object_get(entidad,nombred);
    radio = json_object_get(dimension,nombrer);

    if((!dimension) && (radio)){
       	esvalido = 0;
    }

    if((!json_number_value(radio))){
       	esvalido = 0;
       }
     return esvalido;

}

int parseadorJson::leerEntidadrutaimagen(json_t* entidad,const char* nombre){

	json_t *rutaimagen;
	bool esvalido = 1;

	rutaimagen = json_object_get(entidad,nombre);

	if((!rutaimagen)){
	   esvalido = 0;
	}

	if((!json_string_value(rutaimagen))){
	   esvalido = 0;
	}

	return esvalido;
}


jescenario* parseadorJson::cargarEscenario(json_t* raiz){

	json_t *jsonescenario;
	json_t *jdimensiones;
	json_t *jd_alto;
	json_t *jd_ancho;
	json_t *jcapas;
	bool esvalido;

	//VECTOR POR DEFECTO DE CAPAS LO QUIERO DESTRUIR AL FINAL , VER MEMORIA
     	capas* objs= new capas[2];
		//inicializa los elementos del array
		objs[0].setid(1);
		objs[0].setindex(99);
		objs[0].setrutaimagen("/images/capa1.png");

		objs[1].setid(2);
		objs[1].setindex(98);
		objs[1].setrutaimagen("/images/capa2.png");

	//


	//VECTOR POR DEFECTO DE ENTIDADES

	//

	jescenario *escenario = new jescenario();

	//VALIDO DIMENSIONES,ANCHO Y ALTO

	esvalido=validarEscenario(raiz,"escenario","dimensiones","ancho","alto");

	if(esvalido ==true){

		jsonescenario = json_object_get(raiz, "escenario");
		jdimensiones = json_object_get(jsonescenario,"dimensiones");
		jd_alto = json_object_get(jdimensiones,"alto");
		jd_ancho = json_object_get(jdimensiones,"ancho");

		escenario->setalto(json_number_value(jd_alto));
		escenario->setancho(json_number_value(jd_ancho));

		//cout<<escenario->getalto()<<endl;
		//cout<<escenario->getancho()<<endl;
	}
	else{
		 escenario->setancho(3600);
		 escenario->setalto(600);
		 //cout<<escenario->getalto()<<endl;
		 //cout<<escenario->getancho()<<endl;

	}


	jcapas = json_object_get(jsonescenario, "capas");

	//lista de capas
	list<capas> capalista;


	if(jcapas){
	//	cout<<"CAPAS"<<endl;
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


		   //  jcapas->setid(json_number_value(id));
			 //jcapas->setindex(json_number_value(index_z));
			// jcapas->setrutaimagen(json_string_value(ruta_imagen));
			// jcapas->setid(this->leerValorEnteroaux(id,"id",1));

		   //VALIDO LAS CAPAS Y LE CARGO EL VECTOR POR DEFECTO, SALE MALLLL
		   jcapas->setid(this->leerValorEnteroaux(capai,"id",objs[i].getid()));
		   jcapas->setindex(this->leerValorEnteroaux(capai,"index_z",objs[i].getindex()));
		   jcapas->setrutaimagen(this->leerValorStringCapas(capai,"ruta_imagen",objs[i].getrutaimagen()));

     	   capalista.push_back(*jcapas);

		}

	}
	else
	{
		banderacapas=1;
	}


	if (banderacapas==1)
	{ // SI "CAPA" ESTA MAL ESCRITO ENTONCES CARGO VECTOR POR DEFECTO
		//no existia la capa
		capalista.clear();

		for(int i=0;i<2;i++){
			capalista.push_back(objs[i]);
		}

	}


	 escenario->setcapas(capalista);

/*	list<capas>::iterator pos;
	 for(pos = capalista.begin(); pos!=capalista.end(); pos++){

	         cout<< "escenario-id:" << (*pos).getid()<<endl;
	         cout<< "escenario -index:" << (*pos).getindex()<<endl;
	         cout<< "escenario -ruta: " << (*pos).getrutaimagen()<<endl;
     }
*/
     //ENTIDADES (viene de escenario)

	 json_t *jsonentidades;

     jsonentidades = json_object_get(jsonescenario, "entidades");

     list<jentidades> listaentidades;

     bool cargarEntidadesPorDefecto = false;
     if(jsonentidades){
		//	 cout<<"ENTIDADES"<<endl;
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

			int validarid;
			int validartipo;
			int validarcolor;
			int validardim;
			int valcoor;
			int valruta;
			int valindex;

			list<int> validarent;
			list<int>::iterator pos;


			//voy creando nuevos objetos entidades
			jentidades *entidades = new jentidades();


			//VALIDO ID
			entidadi = json_array_get(jsonentidades, i);

			id = json_object_get(entidadi,"id");
			entidades->setid(json_number_value(id));

			validarid = leerEntidadid(entidadi,"id");
			validarent.push_back(validarid);

			//cout<<entidades->getid()<<endl;

			//VALIDO TIPO
			validartipo = leerEntidadtipo(entidadi,"tipo");
			validarent.push_back(validartipo);

			if (validartipo){
				tipo = json_object_get(entidadi,"tipo");
				entidades->settipo(json_string_value(tipo));

				if (strcmp(json_string_value(tipo), "rectangulo") == 0){
				  const char* rect = "rectangulo";

				  //VALIDAR DIMENSION RECTANGULO ,ANCHO Y ALTO


				  jrectangulo* rectangulo = new jrectangulo();
				  rectangulo->setalto(json_number_value(alto));
				  rectangulo->setancho(json_number_value(ancho));
				  rectangulo->settipo2(rect);
				  entidades->setDim(rectangulo);

				  validardim = leerEntidaddimensionr(entidadi,"dimensiones","ancho","alto");
				  validarent.push_back(validardim);
				  //cout<<rectangulo->getvalor1()<<endl;
				  //cout<<rectangulo->getvalor2()<<endl;
				}
				if(strcmp(json_string_value(tipo),"circulo") == 0){

					//VALIDAR DIMENSION CIRCULO

				  const char* circ = "circulo";
				  jcirculo*  circulo = new jcirculo();
				  circulo->setradio(json_number_value(radio));
				  circulo->settipo2(circ);
				  entidades->setDim(circulo);

				  validardim = leerEntidaddimensionc(entidadi,"dimensiones","radio");
				  validarent.push_back(validardim);

				  //cout<<circulo->getvalor1()<<endl;

				}

			}

			//cout<<entidades->gettipo()<<endl;

			//VALIDAR COLOR
			color = json_object_get(entidadi,"color");
			entidades->setcolor(json_string_value(color));

			validarcolor = leerEntidadcolor(entidadi,"color");
			validarent.push_back(validarcolor);
			//cout<<entidades->getcolor()<<endl;

			dimensiones= json_object_get(entidadi,"dimensiones");
			  // devuelve 0...si eel elemento no tiene algun atributo
			ancho = json_object_get(dimensiones,"ancho");
			alto = json_object_get(dimensiones,"alto");
			radio = json_object_get(dimensiones,"radio");


			  // VALIDAR COORDENADA USO EL VALIDAR DIMENSION RECTANGULO

			   coordenada = json_object_get(entidadi,"coordenada");
			   coorx = json_object_get(coordenada,"x");
			   entidades->setcoorx(json_number_value(coorx));

			   valcoor = leerEntidaddimensionr(entidadi,"coordenada","x","y");
			   validarent.push_back(valcoor);

			   //cout<<entidades->getcoorx()<<endl;

			   coory = json_object_get(coordenada,"y");
			   entidades->setcoory((json_number_value(coory)));
			   //cout<<entidades->getcoory()<<endl;

			   //VALIDAR RUTA IMAGEN

			   ruta_imagen = json_object_get(entidadi,"ruta_imagen");
			   entidades->setruta(json_string_value(ruta_imagen));

			   valruta = leerEntidadtipo(entidadi,"ruta_imagen");
			   validarent.push_back(valruta);

			   //cout<<entidades->getruta()<<endl;

			   //VALIDAD INDEX, USO EL VALIDAR ID
			   index_z= json_object_get(entidadi,"index_z");
			   entidades->setindex(json_number_value(index_z));

			   valindex = leerEntidadid(entidadi,"index_z");
			   validarent.push_back(valindex);

			   //cout<<entidades->getindex()<<endl;

			   //RECORRO LA LISTA BOOLEANA PARA VER SI LA AGREGO O NO A CAPAS

			   bool estaBien = true;
			   for(pos = validarent.begin(); pos!=validarent.end(); pos++){

					if( (*pos) == 0){
						estaBien = false;
					}

				}

			   if (estaBien){
				   listaentidades.push_back(*entidades);
			   }

			 //  listaentidades.push_back(*entidades);

		}

		if (listaentidades.size()==0){
			cargarEntidadesPorDefecto = true;
		}
	}
	else{
		// SI NO ENCONTRO ENTIDADES TENGO QUE HACER UNA LISTA DE 3 ELEMENTOS POR DEFECTO
		// y agregarla a escenario
		cargarEntidadesPorDefecto = true;
	}

     if (cargarEntidadesPorDefecto){
    	 	 //CARGAR VECTOR POR DEFECTO
     }


		   escenario->setentidades(listaentidades);

		/*	list<jentidades>::iterator iterEntidades;
			list<jentidades> lentidades = escenario->getentidades();
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

			delete [] objs;
          */
		   return escenario;
  // QUIERO BORRAR TODAS LAS LISTAS Y VECTORES!!!
		   // como carajo borro el objs!!!

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
