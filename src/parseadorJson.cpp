/*
 * parseadorJson.cpp
 *
 *  Created on: 20 mar. 2017
 *      Author: pato
 */

#include <iostream>
#include "parseadorJson.h"
#include </usr/include/SDL2/SDL.h>

/* CAPAS_H_ */
//	virtual void settipo(int) = 0;
//virtual int gettipo() = 0;
//int tipo;
// id
//tipo
// color
// dimension ancho
//int getancho();
//void setancho(int);
// dimension alto
//int getalto();
//void setalto(int);
// coordenada x
// coordenada y
//rutaimagen
//index
//ancho
//alto
//capas
//entidades
/* CAPAS_H_ */
//archivo donde el logger va a escribir todos los mensajes
/* JESCENARIOJUEGO_H_ */
//char* getFiguraparser() const;
//void setFiguraparse(int level);
//	void settipo(int);
//int gettipo();
//metodos virtuales
//ancho
//alto
// int tipo;
//radio
//metodos virtuales
namespace std
{
    parseadorJson::parseadorJson()
    {
    }
    parseadorJson::parseadorJson(Logger *log)
    {
    	this->log = log;
    }

    parseadorJson::~parseadorJson()
    {
    }

    jventana *parseadorJson::cargarVentana(json_t *raiz)
    {
        json_t *jsonventana;
        json_t *jsonventanaalto;
        json_t *jsonventanaancho;
        jsonventana = json_object_get(raiz, "ventana");
        log->addLogMessage("PARSEADOR JSON", "Se empieza a cargar la configuracion de la ventana.",2);
        jsonventana = json_object_get(jsonventana, "dimensiones");
        jsonventanaalto = json_object_get(jsonventana, "alto");
        jsonventanaancho = json_object_get(jsonventana, "ancho");
        jventana *ventana = new jventana();
        ventana->setalto(json_number_value(jsonventanaalto));
        ventana->setancho(json_number_value(jsonventanaancho));
        log->addLogMessage("PARSEADOR JSON", "Se termina de cargar la configuracion de la ventana.",2);
        return ventana;
    }

    jconfiguracion *parseadorJson::cargarConfiguracion(json_t *raiz)
    {
        json_t *jsonconfiguracion;
        jsonconfiguracion = json_object_get(raiz, "configuracion");
        log->addLogMessage("PARSEADOR JSON", "Se empieza a cargar la configuracion de la velocidad de scroll.", 2);
        jsonconfiguracion = json_object_get(jsonconfiguracion, "vel_scroll");
        jconfiguracion *configuracion = new jconfiguracion();
        configuracion->setvelscroll(json_number_value(jsonconfiguracion));
        log->addLogMessage("PARSEADOR JSON", "Se termina de cargar la configuracion de la velocidad de scroll.",2);
        return configuracion;
    }

    jescenario *parseadorJson::cargarEscenario(json_t *raiz)
    {
        json_t *jsonescenario;
        json_t *jdimensiones;
        json_t *jd_alto;
        json_t *jd_ancho;
        json_t *jcapas;
        jescenario *escenario = new jescenario();
        jsonescenario = json_object_get(raiz, "escenario");
        log->addLogMessage("PARSEADOR JSON", "Se empezo a cargar la configuracion del escenario.", 2);
        jdimensiones = json_object_get(jsonescenario, "dimensiones");
        jd_alto = json_object_get(jdimensiones, "alto");
        jd_ancho = json_object_get(jdimensiones, "ancho");
        escenario->setalto(json_number_value(jd_alto));
        escenario->setancho(json_number_value(jd_ancho));
        jcapas = json_object_get(jsonescenario, "capas");
        list<capas> capalista;
        list<capas>::iterator pos;
        for(int i = 0;i < json_array_size(jcapas);i++){
            json_t *capai;
            json_t *id;
            json_t *index_z;
            json_t *ruta_imagen;
            capai = json_array_get(jcapas, i);
            capas *jcapas = new capas();
            id = json_object_get(capai, "id");
            index_z = json_object_get(capai, "index_z");
            ruta_imagen = json_object_get(capai, "ruta_imagen");
            jcapas->setid(json_number_value(id));
            jcapas->setindex(json_number_value(index_z));
            jcapas->setrutaimagen(json_string_value(ruta_imagen));
            capalista.push_back(*jcapas);
        }
        escenario->setcapas(capalista);
        json_t *jsonentidades;
        jsonentidades = json_object_get(jsonescenario, "entidades");
        list<jentidades> listaentidades;
        for(int i = 0;i < json_array_size(jsonentidades);i++){
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
            jentidades *entidades = new jentidades();
            entidadi = json_array_get(jsonentidades, i);
            id = json_object_get(entidadi, "id");
            entidades->setid(json_number_value(id));
            tipo = json_object_get(entidadi, "tipo");
            entidades->settipo(json_string_value(tipo));
            color = json_object_get(entidadi, "color");
            entidades->setcolor(json_string_value(color));
            dimensiones = json_object_get(entidadi, "dimensiones");
            ancho = json_object_get(dimensiones, "ancho");
            alto = json_object_get(dimensiones, "alto");
            radio = json_object_get(dimensiones, "radio");
            if(strcmp(json_string_value(tipo), "rectangulo") == 0){
                const char *rect = "rectangulo";
                jrectangulo *rectangulo = new jrectangulo();
                rectangulo->setalto(json_number_value(alto));
                rectangulo->setancho(json_number_value(ancho));
                rectangulo->settipo2(rect);
                entidades->setDim(rectangulo);
            }
            if(strcmp(json_string_value(tipo), "circulo") == 0){
                const char *circ = "circulo";
                jcirculo *circulo = new jcirculo();
                circulo->setradio(json_number_value(radio));
                circulo->settipo2(circ);
                entidades->setDim(circulo);
            }
            coordenada = json_object_get(entidadi, "coordenada");
            coorx = json_object_get(coordenada, "x");
            entidades->setcoorx(json_number_value(coorx));
            coory = json_object_get(coordenada, "y");
            entidades->setcoory((json_number_value(coory)));
            ruta_imagen = json_object_get(entidadi, "ruta_imagen");
            entidades->setruta(json_string_value(ruta_imagen));
            index_z = json_object_get(entidadi, "index_z");
            entidades->setindex(json_number_value(index_z));
            listaentidades.push_back(*entidades);
        }

        escenario->setentidades(listaentidades);
        log->addLogMessage("PARSEADOR JSON", "Se termino de cargar la configuracion del escenario.",2);
        return escenario;
    }

    jescenarioJuego *parseadorJson::parsearArchivo(char *nombreArchivo)
    {
        json_t *json;
        json_error_t error;
        json = json_load_file(nombreArchivo, 0, &error);
        if(!json) {
           this->log->addLogMessage("PARSEADOR JSON","Error al intentar leer el archivo Json, no existe el archivo o directorio.",1);
	       cout << "!!! hay  probremas!!!" << endl;
	       cout << error.text << endl;
	       return NULL;
	  }
        this->log->addLogMessage("PARSEADOR JSON","Se empieza a leer el archivo de configuracion.", 2);
        jventana *ventana = cargarVentana(json);
        jconfiguracion *config = cargarConfiguracion(json);
        jescenario *escenario = cargarEscenario(json);
        jescenarioJuego *result = new jescenarioJuego();
        result->setVentana(ventana);
        result->setEscenario(escenario);
        result->setConfiguracion(config);
        this->log->addLogMessage("PARSEADOR JSON","Se termina de leer el archivo de configuracion.",2);
        return result;
    }

    Logger *parseadorJson::getLog() const
    {
        return log;
    }

    void parseadorJson::setLog(Logger *log)
    {
        this->log = log;
    }

    // TODO Auto-generated constructor stub
    //jconexion conexion2 = *conexion2.getinstance();
    // TODO Auto-generated destructor stub
    //cout<<escenario->getalto()<<endl;
    //cout<<escenario->getancho()<<endl;
    //lista de capas
    //iterador de capas
    // agrego la lista total al escenario
    //ENTIDADES (viene de escenario)
    //voy creando nuevos objetos entidades
    // devuelve 0...si eel elemento no tiene algun atributo
} /* namespace std */
