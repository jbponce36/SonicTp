#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "Mensaje.h"

using namespace std;

class Logger {

private:
	char* archivo; //archivo donde el logger va a escribir todos los mensajes
	enum Nivel {BAJO = 1, MEDIO=2, ALTO=3 };
	Nivel nivel;
	string modulo;

public:
	Logger();
	Logger(char *fileName, int level);
	Logger(char *fileName, int level,  string modulo);
	virtual ~Logger();

	string getLevel();
	void setLevel(int level);

	int validateFileName();
	int validateLevel();
	void iniciarLog();
	int addLogMessage(string logMessage, int nivel);
	void imprimirMensajeNivelAlto(string logMessage,int valor);
    char *getArchivo() const;
    void setArchivo(char *archivo);
    string getModulo() const;
    void setModulo(string modulo);

};

#endif /* LOGGER_H_ */
