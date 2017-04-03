#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "Mensaje.h"
#include <string>

using namespace std;

class Logger {

private:
	char* archivo; //archivo donde el logger va a escribir todos los mensajes
	enum Nivel {BAJO = 1, MEDIO=2, ALTO=3 };
	Nivel nivel;
	std::string modulo;

public:
	Logger();
	Logger(char *fileName, int level);
	Logger(char *fileName, int level,  std::string modulo);
	virtual ~Logger();
	std::string getLevel();
	void setLevel(int level);
	int validateFileName();
	int validateLevel();
	void iniciarLog(std::string mensaje);
	int addLogMessage(std::string logMessage, int nivel);
	void imprimirMensajeNivelAlto(std::string logMessage,int valor);
    char *getArchivo() const;
    void setArchivo(char *archivo);
    std::string getModulo() const;
    void setModulo(std::string modulo);

};

#endif /* LOGGER_H_ */
