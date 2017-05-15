#include "ConexServidor.h"
#include "Hiloenviar.h"

#define DEFAULT_PORT = 8090;

namespace std {

ConexServidor::ConexServidor(Logger *log){
	this->cantMaximaClientes = 0;
	this->cantclientes = 0;
	this->finalizarConexion = false;
	this->partidaComenzada = false;
	pthread_mutex_init(&mutex, NULL);
	this->log = log;
	this->log->setModulo("CONEX SERVIDOR");
}
std::string ConexServidor::cargarNombreArchivo(){
	std::string nombre;
	cout<<"Ingrese el nombre del archivo del servidor"<<endl;
	cin>>nombre;
	return nombre;
}
bool ConexServidor::crear(){
	this->sock_recep = socket(AF_INET,SOCK_STREAM,0);

	if(this->sock_recep < 0){
		return false;
	}
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
  int resBind = bind(this->sock_recep,(struct sockaddr *)&server , sizeof(server));

  if( resBind < 0)
  {
	  std::cout << "open failed, error - " << strerror(errno) << std::endl;
	  this->log->addLogMessage("[ENLAZAR] Error, no se pudo enlazar en el puerto "+intToString(puerto),2);
	  //exit(errno);
	  return false;
  }

  this->puerto = puerto;
  this->log->addLogMessage("[ENLAZAR] Terminado",2);
  return true;
}

int ConexServidor::setsocket(){
  struct timeval tv;
  tv.tv_sec = 5;
  tv.tv_usec = 0;

 setsockopt(this->sock_recep,SOL_SOCKET,SO_RCVTIMEO,(char *)&tv,sizeof(struct timeval));


}

list<int> ConexServidor::getListaClientes(){
	this->listaClientes;
}

void ConexServidor::setListaClientes(list<int> listacliente){
	this->listaClientes = listacliente;
}

bool ConexServidor::finalizar(){

	return this->finalizarConexion;
}

bool ConexServidor::noSeConectaronTodos(){
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
		this->log->addLogMessage("[ESCUCHAR] Error, no se pudo escuchar",1);
		return false;
	}
	this->log->addLogMessage("[ESCUCHAR] Terminado",2);
	return true;
}

int ConexServidor::aceptarcliente()
{
	this->log->addLogMessage("[ACEPTAR CLIENTE] Iniciado",2);
	int longitud_dircliente;
	sockaddr_in direccionclient;

    longitud_dircliente= sizeof(struct sockaddr_in);
    fdCliente = accept(this->sock_recep,(struct sockaddr *)&direccionclient,(socklen_t*)&longitud_dircliente);
    pthread_mutex_lock(&mutex);

    if (fdCliente==-1){
    	printf("Estaba esperando conexiones y se deconecto el servidor  \n");

    	fdCliente = -1;
    }
    else
    {
		if (this->cantclientes == this->cantMaximaClientes)   {

			printf("Se ha superado la cantidad maxima de conexiones  \n");
			const char* mensaje = "Conex rechazada";
			send(fdCliente, mensaje, strlen(mensaje), MSG_DONTWAIT);
			close(fdCliente);
			fdCliente = -1;

		}
		else
		{
			this->cantclientes = this->cantclientes + 1;
			this->finalizarConexion = false;
			//printf("Cliente aceptado \n");
			printf("Cantidad de clientes conectados:%d \n", this->cantclientes);
			this->listaClientes.push_back(fdCliente);
            this->setCantclientes(cantclientes);
			this->setListaClientes(listaClientes);
		}
    }

    pthread_mutex_unlock(&mutex);

	this->log->addLogMessage("[ACEPTAR CLIENTE] Terminado",2);
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

int ConexServidor::getCantMaximaClientes()
{
	return this->cantMaximaClientes;
}

int ConexServidor::recibir(int skt, char *buf, int size)
{
	this->log->addLogMessage("[RECIBIR] Iniciado",2);


	int bytes = recv(skt, buf, size, MSG_NOSIGNAL);


	//recv devuelve 0 si el cliente se desconecto satisfactoriamente
	//devuelve -1 si ubo algun error
	//en ambos casos hay que restar la cantidad de clientes


	pthread_mutex_lock(&mutex);
	if (bytes <= 0){
		this->log->addLogMessage("[RECIBIR] Error",2);
		this->cantclientes = this->cantclientes -1;
		//this->setCantclientes(cantclientes);
		this->listaClientes.remove(fdCliente);
		cout << "Removi el cliente con fd: " << fdCliente << endl;
		cout << "El tamanio de la lista es" << listaClientes.size() << endl;
		//this->setListaClientes(listaClientes);
		printf("Cantidad de clientes conectados %d \n", this->cantclientes);


		//if (this->cantclientes==0){
		if(listaClientes.size() == 0){
			printf("No hay clientes conectados \n");
			if (this->partidaComenzada){

				printf("La partida habia comenzado y se desconectaron todos los clientes \n");
				printf("El servidor se desconectara.   \n");

				//a iria un mutex cada vez que se accede a la variable finalizarConexion
				this->finalizarConexion = true;
				this->cerrar();
			}
		}
	}
	else{
		this->log->addLogMessage("[RECIBIR] Error",2);
	}
	pthread_mutex_unlock(&mutex);

	this->log->addLogMessage("[RECIBIR] Terminado",2);
	return bytes;
}

int ConexServidor::recibirPosicion(int skt, Posicion *posicion, int size)
{
	this->log->addLogMessage("[RECIBIR] Iniciado",2);
	int bytes = recv(skt, posicion, sizeof(posicion), MSG_NOSIGNAL);
	//recv devuelve 0 si el cliente se desconecto satisfactoriamente
	//devuelve -1 si ubo algun error
	//en ambos casos hay que restar la cantidad de clientes


	pthread_mutex_lock(&mutex);
	if (bytes<=0){
		this->log->addLogMessage("[RECIBIR] Error",2);
		this->cantclientes = this->cantclientes -1;
		printf("Cantidad de clientes conectados %d \n", this->cantclientes);

		if (this->cantclientes==0){
			printf("No hay clientes conectados \n");

			if (this->partidaComenzada){

				printf("La partida habia comenzado y se desconectaron todos los clientes \n");
				printf("El servidor se desconectara.   \n");

				//a iria un mutex cada vez que se accede a la variable finalizarConexion
				this->finalizarConexion = true;
				this->cerrar();
			}
		}
	}
	this->log->addLogMessage("[RECIBIR] Terminado",2);
	pthread_mutex_unlock(&mutex);
	return bytes;
}


int ConexServidor::enviarAsincronico(int socket, char *buf, int size){
	this->log->setModulo("[CONEX SERVIDOR]");
	this->log->addLogMessage("[ENVIAR] Iniciado",2);
	int enviado = 0;
	int envioParcial = 0;
	bool socketValido = true;
	while(enviado < size && socketValido)
	{
		pthread_mutex_lock(&mutex);
		envioParcial = send(socket,buf, size, MSG_DONTWAIT);
		pthread_mutex_unlock(&mutex);
		if(envioParcial == 0){
		socketValido = false;
		//this->log->addLogMessage("[ENVIAR] Error, se pudo enviar el mensaje, en el"+toString(),1);
		cout<<"[CONEX SERVIDOR][ENVIAR] No se pudo enviar"<<endl;
		this->log->addLogMessage("[ENVIAR] Error, no se pudo enviar",2);
		//return status;
		}
		else if (envioParcial < 0){

			socketValido = false;
		}

		else{

			enviado += envioParcial;
		}
		//this->log->addLogMessage("[ENVIAR] Terminado",2);
		cout<<"[ENVIAR] Terminado"<<endl;
		//return status;
		}
		if (socketValido == false)
		{
			return envioParcial;
		}
		else {
			return enviado;
	}
}


int ConexServidor::enviar(int socket, char *buf, int size){
	this->log->setModulo("[CONEX SERVIDOR]");
	this->log->addLogMessage("[ENVIAR] Iniciado",2);
	int enviado = 0;
	int envioParcial = 0;
	bool socketValido = true;
	while(enviado < size && socketValido)
	{
		pthread_mutex_lock(&mutex);
		//cout<<":::::::::"<<"tendria que entrar en send"<<endl;
		envioParcial = send(socket,buf, size, MSG_NOSIGNAL);
		//cout<<":::::::::"<<"sali de send"<<endl;
		//cout<<":::::::::"<<envioParcial<<endl;
		pthread_mutex_unlock(&mutex);
		if(envioParcial == 0){
		socketValido = false;
		//this->log->addLogMessage("[ENVIAR] Error, se pudo enviar el mensaje, en el"+toString(),1);
		cout<<"[CONEX SERVIDOR][ENVIAR] No se pudo enviar"<<endl;
		this->log->addLogMessage("[ENVIAR] Error, no se pudo enviar",2);
		//return status;
		}
		else if (envioParcial < 0){

			socketValido = false;
		}

		else{

			enviado += envioParcial;
		}
		//this->log->addLogMessage("[ENVIAR] Terminado",2);
		//cout<<"[ENVIAR] Terminado"<<endl;
		//return status;
		}
		if (socketValido == false)
		{
			return envioParcial;
		}
		else {
			return enviado;
	}
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

string ConexServidor::intToString(int number)
{
  ostringstream oss;
  oss<< number;
  return oss.str();
}

string ConexServidor::toString(){
	return "Socket: "+intToString(this->getFd())+", puerto: "+intToString(this->puerto);
}

bool ConexServidor::getFinalizarConexion(){
	return finalizarConexion;
}
void ConexServidor::setFinalizarConexion(bool FinalizarConexion){
	 this->finalizarConexion = FinalizarConexion;
}
void ConexServidor::comenzarPartida(std::vector<Hiloenviar*> &hrEnviar)
{
	pthread_mutex_lock(&mutex);
	this->partidaComenzada = true;
	printf("Se comienza la partida \n");
    char* mensaje = "[INICIAR JUEGO]";

	std::vector<Hiloenviar*>::iterator pos;
		for(pos = hrEnviar.begin();pos != hrEnviar.end();pos++)
		{
			(*pos)->enviarDato(mensaje);
		}
		/*for(pos = this->listaClientes.begin(); pos!=this->listaClientes.end(); pos++){
			printf("Enviando iniciar juego al cliente %d  \n", (*pos));
			const char* mensaje = "[INICIAR JUEGO]";
			send((*pos), mensaje, strlen(mensaje), MSG_DONTWAIT);

	    }
	    */
	pthread_mutex_unlock(&mutex);
}

}//Namespace
