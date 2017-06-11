/*
 * JuegoServidor.cpp
 *
 *  Created on: 23 abr. 2017
 *      Author: julieta
 */

#include "JuegoServidor.h"
#include "debug.h"

JuegoServidor::JuegoServidor(ConexServidor *server,
	std::vector<Hiloenviar*> &hiloEnviar, std::vector<Hilorecibir*> &hiloRecibir, Logger *log,
	bool &juegoTerminado, int modoJuego)
: vista(NULL), control(NULL),server(server), log(log),
  hiloJuego(NULL), hilosEnviar(hiloEnviar), hilosRecibir(hiloRecibir),
  cantJugadores(server->getCantclientes()), sonics(), juegoTerminado(juegoTerminado), velocidad(0),
  altoEscenario(0), modoJuego(modoJuego){
	//Vista, sonic y control se setean desde el thread

}

JuegoServidor::~JuegoServidor()
{
	std::map<int ,Personaje*>::iterator pos;
	for(pos = sonics.begin();pos != sonics.end();pos++){
		delete (*pos).second;
	}
	delete control;
	delete vista;
}

void JuegoServidor::inicializarJuegoServidor(/*std::jescenarioJuego *jparseador*/)
{
	parseadorJson* parseador = new parseadorJson(log);
	char *file=(char*)"configuracion/configuracion.json";
	jescenarioJuego* jparseador = parseador->parsearArchivo(file);
	parser.push_back(jparseador);

	vista = new VistaSDL(jparseador->getVentana(),jparseador->getConfiguracion(),jparseador->getEscenario(), log, true);
	velocidad = jparseador->getConfiguracion()->getvelscroll();
	altoEscenario = jparseador->getEscenario()->getalto();

	for (int id = 1; id <= server->getCantclientes(); id++)
	{
		Personaje *sonic = new Personaje(id, velocidad, vista->obtenerRender(), altoEscenario, log);
		sonics[id] = sonic;
	}


	control = new ControlServidor(0, 0, vista, &sonics, &hilosEnviar, &hilosRecibir, server,log);

	control->setAnill(jparseador->getAnillo());
	control->setJpied(jparseador->getPiedra());
	control->setJpin(jparseador->getPinche());


/*	vector<janillos*> anillos;
	vector<jpiedra*> piedras;
	vector<jpinche*> pinches;

	vector<jcangrejo*> cangrejos;
	vector<jmosca*> moscas;
	vector<jpescado*> pescados;
*/
	//vector<jescenarioJuego*> parser;


	//cargarNiveles(jparseador,anillos,piedras,pinches,cangrejos,moscas,pescados);


	std::string ruta = "configuracion/configuracion";
	for(int i=1; i < CANTIDAD_NIVELES;i++){
		cout<<"cout1loop archivos"<<endl;
		std::string rutaCompleta = ruta + Util::intToString(i) + ".json";
		char *rutaChar = (char*)rutaCompleta.c_str();
		cout<<"antes ruta"<<endl;
		//strcpy(rutaChar,rutaCompleta.c_str());
			//	char buffer[LARGO_MENSAJE_POSICION_CLIENTE] = "";
			//		strcpy(buffer, mensaje.c_str());
		cout<<"ruta: "<<rutaChar<<endl;
		jparseador = parseador->parsearArchivo(rutaChar);

		parser.push_back(jparseador);

	}

	cout<<"cout1"<<endl;
    vista->setJjuego(parser);


	/*control->setAnill(jparseador->getAnillo());
	control->setJpied(jparseador->getPiedra());
    control->setJpin(jparseador->getPinche());*/


    if(modoJuego == 3)
    {
    	cout << "Modo juego es 3\n";
    	//Aca recibe los numeros de grupo de los clientes
    	std::vector<Hilorecibir*>::iterator pos;
    	std::string mensaje;
    	for(pos = hilosRecibir.begin();pos != hilosRecibir.end();pos++)
		{
    		int grupo = 1;
    		mensaje = (*pos)->obtenerElementoDeLaCola();
			while (mensaje.substr(0, 3).compare(MENSAJE_EQUIPO) != 0)
			{
				if (mensaje.substr(0,3).compare(MENSAJE_DESCONEXION_CLIENTE) == 0)
				{
					//Recibe "DES1"
					this->log->addLogMessage("[RECIBIR GRUPO] Error. Cliente desconectado. Se asignara al grupo 1." ,1);
					mensaje = MENSAJE_EQUIPO + mensaje.substr(3,1) + "1";
					break;
				}
				mensaje = (*pos)->obtenerElementoDeLaCola();
			}
			int idSonic = atoi(mensaje.substr(3,1).c_str());
			grupo = atoi(mensaje.substr(4,1).c_str());



		}
    }


}


void JuegoServidor::iniciarJuegoControlServidor()
{
	control->ControlarJuegoServidor(vista, juegoTerminado);

}

void JuegoServidor::iniciarJuego()
{
	//Se leen los datos del json

	log->setModulo("JUEGO_SERVIDOR");
	log->addLogMessage("Se inicia el juego.",1);

	//Inicia el juego
	inicializarJuegoServidor(); //Inicializa vista y control.

	iniciarJuegoControlServidor();

	log->setModulo("JUEGO_SERVIDOR");
	log->addLogMessage("Se termina el juego.",1);


}

void* JuegoServidor::iniciarJuegoServidor(void *datos)
{
	JuegoServidor *juego = (JuegoServidor*)datos;
	juego->iniciarJuego();
	return NULL;
}

void JuegoServidor::iniciarHiloJuego()
{
	hiloJuego = new Hilo();

	hiloJuego->Create((void *)iniciarJuegoServidor, (void *)this);
}

void JuegoServidor::terminarHiloJuego()
{
	juegoTerminado = true;
	hiloJuego->Join();
}

void JuegoServidor::enviarATodosLosClientes(std::string mensaje)
{
	control->enviarATodos(mensaje);
}

int JuegoServidor::obtenerIdLibre()
{
	std::map<int ,Personaje*>::iterator pos;
	for(pos = sonics.begin();pos != sonics.end();pos++){
		if((*pos).second->estaCongelado() && (*pos).second->sigueVivo())
		{
			return (*pos).first; //Devuelve el id de algun sonic congelado y que no este muerto
		}
	}
	return 0;
}

void JuegoServidor::obtenerPosicionValida(int &x, int &y)
{
	std::map<int ,Personaje*>::iterator pos;
	for(pos = sonics.begin();pos != sonics.end();pos++){
		if(!(*pos).second->estaCongelado() && (*pos).second->sigueVivo())
		{
			x = (*pos).second->getPosicionX();
			y = (*pos).second->getPosicionY();
			return;
		}
	}

}

void JuegoServidor::reconectar(int sock, ConexServidor *servidor)
{
	int idLibre = obtenerIdLibre();
	if(idLibre == 0)
	{
		cout << "No hay ningun sonic desconectado." << endl;
		servidor->quitarCliente(sock);
		return;
	}

	Hilorecibir *hrecibir = hilosRecibir.at(idLibre-1);
	Hiloenviar *henviar = hilosEnviar.at(idLibre-1);

	if((hrecibir->continua()) || (henviar->continua()))
	{
		cout << "Los hilos enviar/recibir aun no terminaron." << endl;
		servidor->quitarCliente(sock);
		return;
	}

	hrecibir->parametros.skt = sock;
	hrecibir->parametros.continuar = true;
	hrecibir->IniciarHilo();

	henviar->parametros.skt = sock;
	henviar->parametros.continuar = true;

	//Le mando un ID y la cantidad maxima de jugadores
	ostringstream oss;
	oss<< MENSAJE_ID << idLibre << server->getCantMaximaClientes();
	char buffer[6] = "";
	string temp = oss.str();
	temp = temp + SEPARADOR_DE_MENSAJE;
	strcpy(buffer, temp.c_str());
	cout << "Server envio ID+maxConexiones: " << buffer << endl;

	henviar->enviarDato(buffer);
	henviar->iniciarHiloQueue();

	char buffer2[6] = "";
	ostringstream ossModoDeJuego;
	ossModoDeJuego << 1;
	string stringModo = MENSAJE_MODO + ossModoDeJuego.str();
	stringModo = stringModo + PADDING + SEPARADOR_DE_MENSAJE;
	strcpy(buffer2, stringModo.c_str());
	cout << "Server envio modo de juego: " << buffer2 << endl;
	henviar->enviarDato(buffer2);

	sleep(1);

	char *inicio = "[INICIAR JUEGO]$";
	henviar->enviarDato(inicio);

	sleep(1);
	//hlatidos->IniciarHilo();

	int x = 0, y = 0;
	obtenerPosicionValida(x, y);
	sonics.at(idLibre)->posicionarseEn(x, y);
	sonics.at(idLibre)->descongelar();

	control->enviarDatosEscenario(henviar);
	control->enviarDatosEnemigosInicialesAUno(henviar);
	control->enviarAUno(FIN_MENSAJES_ENEMIGOS, henviar);
	control->enviarAnillasPiedrasYPinches(henviar);
}
void JuegoServidor::cargarNiveles(jescenarioJuego *jparseador,vector<jescenarioJuego*> parser){

	/*anillos.push_back(jparseador->getAnillo());
	piedras.push_back(jparseador->getPiedra());
	pinches.push_back(jparseador->getPinche());


	cangrejos.push_back(jparseador->getCangrejo());
	moscas.push_back(jparseador->getMosca());
	pescados.push_back(jparseador->getPescado());
	*/




	/*control->setAnill(jparseador->getAnillo());
	control->setJpied(jparseador->getPiedra());
	control->setJpin(jparseador->getPinche());*/
}
