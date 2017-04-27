/*
 * ConexServidor.cpp
 *
 *  Created on: 11 abr. 2017
 *      Author: pato
 */

#include "ConexServidor.h"

#include <pthread.h>


#define DEFAULT_PORT = 8090;

namespace std {

ConexServidor::ConexServidor(Logger *log){
	this->cantMaximaClientes = 0;
	this->cantclientes = 0;
	this->finalizarConexion = false;
	this->partidaComenzada = false;
	pthread_mutex_init(&mutex, NULL);
	log->setModulo("CONEX SERVIDOR");
	this->log = log;
}
std::string ConexServidor::cargarNombreArchivo(){
	std::string nombre;
	cout<<"Ingrese el nombre del archivo del servidor"<<endl;
	cin>>nombre;
	return nombre;
}
bool ConexServidor::crear(){
	this->log->addLogMessage("[CREAR] Iniciado",2);
	this->sock_recep = socket(AF_INET,SOCK_STREAM,0);

	if(this->sock_recep < 0){
		return false;
	}

	this->log->addLogMessage("[CREAR] Finalizado",2);
	return true;
}
ConexServidor::~ConexServidor() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&mutex);
}

bool ConexServidor::enlazar(int puerto){

	//struct sockaddr_in server;
	sockaddr_in	server;
	//this->AgregarDireccionSocket(&server,puerto);
	this->log->addLogMessage("[ENLAZAR] Iniciado",2);
	server.sin_family = AF_INET;
	server.sin_port = htons(puerto);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server.sin_zero),8);
	cout<<puerto<<endl;
	int resBind = bind(this->sock_recep,(struct sockaddr *)(&server), sizeof (server));
		if(resBind < 0){
			std::cout << "open failed, error - " << strerror(errno) << std::endl;
			this->log->addLogMessage("[ENLAZAR] Error, no se pudo enlazar en el puerto "+intToString(puerto),2);
			//exit(errno);
			return false;
		}
		this->log->addLogMessage("[ENLAZAR] Finalizado",2);
		return true;
  }

    bool ConexServidor::finalizar()
    {
        return this->finalizarConexion;
    }

    bool ConexServidor::noSeConectaronTodos()
    {
        printf("Conectados %d Maximo %d \n", this->cantclientes, this->cantMaximaClientes);
        return this->cantclientes < this->cantMaximaClientes;
    }

    bool ConexServidor::escuchar(int cantidadMaxima)
    {
    	this->log->addLogMessage("[ESCUCHAR] Iniciado",2);
        int escuchar = listen(this->sock_recep, cantidadMaxima);
        cout << cantidadMaxima << endl;
        this->cantMaximaClientes = cantidadMaxima;
        if(escuchar < 0){
        	this->log->addLogMessage("[ESCUCHAR] Error",1);
            return false;
        }

        this->log->addLogMessage("[ESCUCHAR] Terminado",2);
        return true;
    }

    int ConexServidor::aceptarcliente()
    {
    	this->log->addLogMessage("[ACEPTAR] Iniciado",2);
        int longitud_dircliente;
        sockaddr_in direccionclient;
        longitud_dircliente = sizeof (struct sockaddr_in);
        int fdCliente = accept(this->sock_recep, (struct sockaddr*)(&direccionclient), (socklen_t*)(&longitud_dircliente));
        pthread_mutex_lock(&mutex);
        if(fdCliente == -1){
            printf("Estaba esperando conexiones y se deconecto el servidor  \n");
            fdCliente = -1;
        }else{
            if(this->cantclientes == this->cantMaximaClientes){
                printf("Se ha superado la cantidad maxima de conexiones  \n");
                const char *mensaje = "Conexion rechazada. Numero maximo de conexiones establecidas";
                send(fdCliente, mensaje, strlen(mensaje), MSG_DONTWAIT);
                close(fdCliente);
                fdCliente - 1;
                this->log->addLogMessage("[ACEPTAR] Error, el max de clientes es: "+intToString(cantMaximaClientes),2);
            }else{
                this->cantclientes = this->cantclientes + 1;
                this->finalizarConexion = false;
                //printf("Cliente aceptado \n");
                printf("Cantidad de clientes conectados:%d \n", this->cantclientes);
            }
        }

        pthread_mutex_unlock(&mutex);
        this->log->addLogMessage("[ACEPTAR] Terminado",2);
        return fdCliente;
    }

    int ConexServidor::getCantclientes()
    {
        return this->cantclientes;
    }

    void ConexServidor::setCantclientes(int CantClientes)
    {
        this->cantclientes = CantClientes;
    }

    int ConexServidor::recibir(int skt, char *buf, int size)
    {
        this->log->addLogMessage("[RECIBIR] Iniciado",2);
        int bytes = recv(skt, buf, size, MSG_NOSIGNAL);
        //recv devuelve 0 si el cliente se desconecto satisfactoriamente
        //devuelve -1 si ubo algun error
        //en ambos casos hay que restar la cantidad de clientes
        pthread_mutex_lock(&mutex);
        if(bytes <= 0){
            this->cantclientes = this->cantclientes - 1;
            printf("Cantidad de clientes conectados %d \n", this->cantclientes);
            if(this->cantclientes == 0){
                printf("No hay clientes conectados \n");
                if(this->partidaComenzada){
                    printf("La partida habia comenzado y se desconectaron todos los clientes \n");
                    printf("El servidor se desconectara.   \n");
                    //a iria un mutex cada vez que se accede a la variable finalizarConexion
                    this->finalizarConexion = true;
                    this->cerrar();
                }
                this->log->addLogMessage("[RECIBIR] Todos los clientes se desconectaron",2);
            }

        }

        pthread_mutex_unlock(&mutex);
        this->log->addLogMessage("[RECIBIR] Terminado",2);
        return bytes;
    }

    int ConexServidor::enviar(int socket, char *buf, int size)
    {
        this->log->addLogMessage("[ENVIAR] Iniciado",2);
        //	int sent = 0;
        //	int status = 0;
        //	bool is_the_socket_valid = true;
        //this->log->addLogMessage("[ENVIAR] Iniciado",2);
        //	while (sent < size && is_the_socket_valid) {
        int status = send(socket, buf, size, MSG_NOSIGNAL);
        //	if (status <= 0) {
        //		is_the_socket_valid = false;
        //	}
        //	else {
        //		sent += status;
        //	}
        //}
        if(status < 0){
            //this->log->addLogMessage("[ENVIAR] Error, se pudo enviar el mensaje, en el"+toString(),1);
            cout << "[CONEX SERVIDOR][ENVIAR] No se pudo enviar" << endl;
            this->log->addLogMessage("[ENVIAR] Error",2);
            return status;
        }
        //this->log->addLogMessage("[ENVIAR] Terminado",2);
        cout << "[CONEX SERVIDOR][ENVIAR] Se envio correctamente" << endl;
        this->log->addLogMessage("[ENVIAR] Terminado",2);
        return status;
    }

    int ConexServidor::cerrar()
    {
        this->log->addLogMessage("[CERRAR] Iniciado",2);
        int status = shutdown(this->sock_recep, SHUT_RDWR);
        status = close(this->sock_recep);
        this->log->addLogMessage("[CERRAR] Terminado",2);
        return status;
    }

    int ConexServidor::getFd() const
    {
        return fd;
    }

    string ConexServidor::getHostname() const
    {
        return hostname;
    }

    void ConexServidor::setFd(int fd)
    {
        this->fd = fd;
    }

    void ConexServidor::setHostname(string hostname)
    {
        this->hostname = hostname;
    }

    Logger *ConexServidor::getLog() const
    {
        return log;
    }

    void ConexServidor::setLog(Logger *log)
    {
        this->log = log;
}


}
/*void ConexServidor::aceptarClientes()
{


	char *archivoLog=(char*)"configuracion/log.txt";
	Logger *log = new Logger(archivoLog, getNivelLogger(argc,argv ), "PRINCIPAL");
	log->iniciarLog("INICAR LOGGER");

	//Se lee del json el nombre de la ventana
	parseadorJson* parseador = new parseadorJson(log);

	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);


	log->setModulo("PRINCIPAL");
	log->addLogMessage("Se empieza a cargar la vista.",1);
	log->setLevel(getNivelLogger(argc, argv));



	Hilo *hilo = new hilo();


	while(1)
	{
		Sockets skt = new Sockets();
		skt = acep();
		if (skt == true){
			hilo->Create((void*)control->ControlarJuego(skt));//hilo
		}else{
			close(skt);
		}
	}
}*/

string ConexServidor::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

string ConexServidor::toString(){
	return "Socket: "+intToString(this->getFd())+", puerto: "+intToString(this->puerto);
}
 /* namespace std */




bool ConexServidor::getFinalizarConexion(){
	return finalizarConexion;
}
void ConexServidor::setFinalizarConexion(bool FinalizarConexion){
	 this->finalizarConexion = FinalizarConexion;
}
void ConexServidor::comenzarPartida(){
	pthread_mutex_lock(&mutex);
	this->partidaComenzada = true;
	printf("Se comienza la partida \n");
	pthread_mutex_unlock(&mutex);
}
