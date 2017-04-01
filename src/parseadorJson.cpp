#include "parseadorJson.h"
#define MODULO 'PARSEADOR JSON'

/* LOGGER_H_ */
//ancho
//alto
//id
//index_z
//rutaimagen
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
/* JESCENARIOJUEGO_H_ */
//radio
//metodos virtuales
//	void settipo(int);
//int gettipo();
//metodos virtuales
//ancho
//alto
// int tipo;
namespace std
{
    parseadorJson::parseadorJson()
    {
    }

    parseadorJson::parseadorJson(Logger *log)
    {
        this->log = log;
        this->log->setModulo("PARSEADOR JSON");
    }

    parseadorJson::~parseadorJson()
    {
    }

    jventana *parseadorJson::cargarVentana(json_t *raiz)
    {
        json_t *jsonventana;
        json_t *jsonventanaalto;
        json_t *jsonventanaancho;
        bool esvalido;
        jventana *ventana = new jventana();
        esvalido = validarVentana(raiz, "ventana", "dimensiones", "alto", "ancho");
        if(esvalido){
            this->log->addLogMessage("[CONFIGURACION DE LA VENTANA] Iniciado.", 2);
            jsonventana = json_object_get(raiz, "ventana");
            jsonventana = json_object_get(jsonventana, "dimensiones");
            jsonventanaalto = json_object_get(jsonventana, "alto");
            this->log->addLogMessage("[CONFIGURACION DE LA VENTANA] Seteando alto.", 3);
            jsonventanaancho = json_object_get(jsonventana, "ancho");
            this->log->addLogMessage("[CONFIGURACION DE LA VENTANA] Seteando ancho.", 3);
            ventana->setalto(json_number_value(jsonventanaalto));
            ventana->setancho(json_number_value(jsonventanaancho));
            this->log->addLogMessage("[CONFIGURACION DE LA VENTANA] Terminado.", 2);
        }else{
            this->log->addLogMessage("[CONFIGURACION DE LA VENTANA] No se han encontrado los atributos correctos, se cargaran valores por defecto", 1);
            ventana->setalto(600);
            ventana->setancho(3600);
        }
        return ventana;
    }

    Logger *parseadorJson::getLog() const
    {
        return log;
    }

    void parseadorJson::setLog(Logger *log)
    {
        this->log = log;
    }

    jescenarioJuego *parseadorJson::getJuego() const
    {
        return juego;
    }

    void parseadorJson::setJuego(jescenarioJuego *juego)
    {
        this->juego = juego;
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

    double parseadorJson::leerValorEntero(json_t *padre, const char *nombre, int valorPorDefecto)
    {
        json_t *elemento;
        elemento = json_object_get(padre, nombre);
        if(!elemento){
            return valorPorDefecto;
        }
        if (!json_is_number(elemento)){
		return valorPorDefecto;
	}
        return json_number_value(elemento);
    }

    bool parseadorJson::validarVentana(json_t *raiz, const char *nomvent, const char *nomdim, const char *nomancho, const char *nomalto)
    {
        json_t *jsonventana;
        json_t *jsondimension;
        json_t *jsonancho;
        json_t *jsonalto;
        bool validarvent = true;
        jsonventana = json_object_get(raiz, nomvent);
        jsondimension = json_object_get(jsonventana, nomdim);
        jsonancho = json_object_get(jsondimension, nomancho);
        jsonalto = json_object_get(jsondimension, nomalto);
        if((!jsonventana) && (!jsondimension)){
            validarvent = false;
        }else{
            validarvent = true;
        }
        if(json_number_value(jsonancho) && json_number_value(jsonalto)){
            validarvent = true;
        }else{
            validarvent = false;
        }
        return validarvent;
    }

    void parseadorJson::validarEntidadesEscenario(json_t *raizentidad, const char *id, const char *tipo, const char *color, const char *dim, const char *coor, const char *ruta, const char *index)
    {
        json_t *jsonentidades;
        json_t *jsonid;
        json_t *jsontipo;
        json_t *jsoncolor;
        json_t *jsondimensiones;
        json_t *jsoncoordenadas;
        json_t *jsonrutaimagen;
        json_t *jsonindex;
        bool validarentesc = true;
        jsonentidades = json_object_get(raizentidad, "entidades");
        jsonid = json_object_get(jsonentidades, id);
        jsontipo = json_object_get(jsonentidades, tipo);
        jsoncolor = json_object_get(jsonentidades, color);
        jsondimensiones = json_object_get(jsonentidades, dim);
        jsoncoordenadas = json_object_get(jsoncoordenadas, coor);
        jsonrutaimagen = json_object_get(jsoncoordenadas, ruta);
        jsonindex = json_object_get(jsoncoordenadas, index);
        if((!jsonid) && (!jsontipo) && (jsoncolor) && (jsondimensiones) && (jsoncoordenadas) && (jsonrutaimagen) && (jsonindex)){
            validarentesc = false;
        }else{
            validarentesc = true;
        }
    }

    bool parseadorJson::validarEscenario(json_t *raiz, const char *nomesce, const char *nomdim, const char *ancho, const char *alto)
    {
        json_t *jsonescenario;
        json_t *jsondimensiones;
        json_t *jsonalto;
        json_t *jsonancho;
        bool valesce = true;
        jsonescenario = json_object_get(raiz, nomesce);
        jsondimensiones = json_object_get(jsonescenario, nomdim);
        jsonalto = json_object_get(jsondimensiones, alto);
        jsonancho = json_object_get(jsondimensiones, ancho);
        if((!jsonescenario) && (!jsondimensiones)){
            valesce = false;
        }else{
            valesce = true;
        }
        if(json_number_value(jsonancho) && (json_number_value(jsonalto))){
            valesce = true;
        }else{
            valesce = false;
        }
        return valesce;
    }

    bool parseadorJson::validarConfiguracion(json_t *raiz, const char *config, const char *velscroll)
    {
        json_t *jsonconfiguracion;
        json_t *jsonvelscroll;
        bool valconfig = true;
        jsonconfiguracion = json_object_get(raiz, config);
        jsonvelscroll = json_object_get(jsonconfiguracion, velscroll);
        if((!jsonconfiguracion) && (!jsonvelscroll)){
            valconfig = false;
        }else{
            valconfig = true;
        }
        if(json_number_value(jsonvelscroll)){
            valconfig = true;
        }else{
            valconfig = false;
        }
        return valconfig;
    }

    jconfiguracion *parseadorJson::cargarConfiguracion(json_t *raiz)
    {
        json_t *jsonconfiguracion;
        json_t *jsonvelscrol;
        jconfiguracion *configuracion = new jconfiguracion();
        jsonconfiguracion = json_object_get(raiz, "configuracion");
        jsonvelscrol = json_object_get(jsonconfiguracion, "vel_scroll");
        if((jsonconfiguracion) && (jsonvelscrol)){
        	this->log->addLogMessage("[CONFIGURACION DE LA VELOCIDAD DE SCROLL] Iniciado.", 2);
            configuracion->setvelscroll(this->leerValorEntero(jsonconfiguracion, "vel_scroll", 20));
            this->log->addLogMessage("[CONFIGURACION DE LA VELOCIDAD DE SCROLL] Velocidad de scroll ", 3);
            this->log->addLogMessage("[CONFIGURACION DE LA VELOCIDAD DE SCROLL] Terminado.", 2);
        }else{
            configuracion->setvelscroll(20);
            this->log->addLogMessage("[CONFIGURACION DE LA VELOCIDAD DE SCROLL] No se ha encontrado el atributo correctamente, se cargo un valor por defecto ", 3);
        }
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
        jdimensiones = json_object_get(jsonescenario, "dimensiones");
        jd_alto = json_object_get(jdimensiones, "alto");
        jd_ancho = json_object_get(jdimensiones, "ancho");
        escenario->setalto(json_number_value(jd_alto));
        escenario->setancho(json_number_value(jd_ancho));
        jcapas = json_object_get(jsonescenario, "capas");
        list<capas> capalista;
        list<capas>::iterator pos;

        this->log->addLogMessage("[CONFIGURACION DE LAS CAPAS] Iniciado. ", 2);

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
        this->log->addLogMessage("[CONFIGURACION DE LAS CAPAS] Terminado. ", 2);

        json_t *jsonentidades;
        jsonentidades = json_object_get(jsonescenario, "entidades");
        list<jentidades> listaentidades;

        this->log->addLogMessage("[CONFIGURACION DE LAS ENTIDADES] Iniciado. ", 2);

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
        this->log->addLogMessage("[CONFIGURACION DE LAS ENTIDADES] Terminado, ", 2);

        return escenario;
    }

    jescenarioJuego *parseadorJson::parsearArchivo(char *nombreArchivo)
    {
        json_t *json;
        json_error_t error;
        json = json_load_file(nombreArchivo, 0, &error);
        if(!json) {
        	this->log->addLogMessage("Error al intentar leer el archivo Json, no existe el archivo o directorio.",1);
        	cout << "!!! hay  probremas!!!" << endl;
        	cout << error.text << endl;
	       return NULL;
	  }
        jventana *ventana = cargarVentana(json);
        jconfiguracion *config = cargarConfiguracion(json);
        jescenario *escenario = cargarEscenario(json);
        jescenarioJuego *result = new jescenarioJuego();
        result->setVentana(ventana);
        result->setEscenario(escenario);
        result->setConfiguracion(config);
        this->log->addLogMessage("Se termino de leer el archivo de configuracion.", 2);
        return result;
    }

    // TODO Auto-generated constructor stub
    //jconexion conexion2 = *conexion2.getinstance();
    // TODO Auto-generated destructor stub
    //cout<<"ventana archivo"<<endl;
    //cout<<ventana->getalto()<<endl;
    //cout<<ventana->getancho()<<endl;
    //cout<<"ventana defecto"<<endl;
    //cout<<ventana->getalto()<<endl;
    //cout<<ventana->getancho()<<endl;
    //VER QUE PASA CON ENTIDADES SI ESTA MAL!!!
    //if(json_number_value(jsonancho) && (json_number_value(jsonalto))){
    //cout<< "valor configuracion archivo"<<endl;
    //cout<<configuracion->getvelscroll()<<endl;
    //cout<< "valor configuracion def"<<endl;
    // cout<<configuracion->getvelscroll()<<endl;
    //cout<<escenario->getalto()<<endl;
    //cout<<escenario->getancho()<<endl;
    //lista de capas
    //iterador de capas
    // agrego la lista total al escenario
    //ENTIDADES (viene de escenario)
    //voy creando nuevos objetos entidades
    // devuelve 0...si eel elemento no tiene algun atributo
} /* namespace std */
