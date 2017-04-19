/*
 * Hilo.cpp
 *
 *  Created on: 16 abr. 2017
 *      Author: pato
 */

#include "Hilo.h"


namespace std {

Hilo::Hilo(Logger *logs) {
	this->log = logs;
	this->log->setModulo("Hilo");
}

Hilo::~Hilo() {
	// TODO Auto-generated destructor stub
}

int Hilo::Join(){
	 pthread_join(this->tid,NULL);
	 return 0;
}

int Hilo::Create(void *Callback,void *args){
 //this->log->addLogMessage("[VALIDAR CREACION MUTEX] Iniciado.", 2);
 cout<<"1"<<endl;
  //int tret = pthread_create(&this->tid[2], NULL, (void *(*)(void *))Callback, NULL);
  int tret = pthread_create(&this->tid, NULL, (void *(*)(void *))Callback, args);

  cout<<"2"<<endl;
  if(tret == 0) {
	  cout<<"3"<<endl;
	 // this->log->addLogMessage("[VALIDAR CREACION MUTEX] Creacion correcta del mutex.", 3);
	  cout<<tret<<endl;
      return tret;
    }
    else {
    	cout<<"5"<<endl;
     // this->log->addLogMessage("[VALIDAR CREACION MUTEX] Creacion incorrecta del mutex." ,1);
    	cout<<tret<<endl;
      return tret;
  }

   // this->log->addLogMessage("[VALIDAR CREACION MUTEX] Terminada.", 2);
}

int Hilo::InitMutex(){

 this->log->addLogMessage("[VALIDAR INICIO MUTEX] Iniciado.", 2);

 if(pthread_mutex_init(&mutex, NULL) < 0) {
   this->log->addLogMessage("[VALIDAR INICIO MUTEX] Error al iniciar el mutex",1);
	   //cerr << "Error while initializing mutex" << endl;
	    return -1;
  }
  else {
	    //cout << "Mutex initialized." << endl;
	this->log->addLogMessage("[VALIDAR INICIO MUTEX] Mutex iniciado correctamente",3);
	    return 0;
   }
 this->log->addLogMessage("[VALIDAR INICIO MUTEX] Terminado.",2);
}

int Hilo::LockMutex(const char *identificacion){// me imagino sera la ip...

 this->log->addLogMessage("[VALIDAR LOCKS MUTEX] Iniciado.", 2);

 if(pthread_mutex_lock(&mutex) == 0) {
	 //esta todo bien y se puedo adquirir el locks
	this->log->addLogMessage("[VALIDAR LOCKS MUTEX] se adquirio el locks para el cliente",3);
    return 0;
  }
 else {

	 this->log->addLogMessage("[VALIDAR LOCKS MUTEX] Error al adquirir el locks al cliente",1);
     return -1;
  }
    this->log->addLogMessage("[VALIDAR LOCKS MUTEX] Terminado.",2);

}

int Hilo::UnlockMutex(const char *identificacion){

 this->log->addLogMessage("[VALIDAR UNLOCKS] Iniciando.",2);

 if(pthread_mutex_unlock(&mutex) == 0) {
  // se pudo liberar el blqueo del cliente
	 this->log->addLogMessage("[VALIDAR UNLOCKS] Se pudo liberar el locks del cliente",3);
     return 0;
   }
   else {
     this->log->addLogMessage("[VALIDAR UNLOCKS] No se pudo liberar el locks del cliente",1);
    return -1;
 }

 this->log->addLogMessage("[VALIDAR UNLOCKS] Terminado.",2);
 }
} /* namespace std */
