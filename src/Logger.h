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

public:
	Logger();
	Logger(char *fileName, int level);
	virtual ~Logger();

	string getLevel();
	void setLevel(int level);

	int validateFileName();
	int validateLevel();
	int addLogMessage(string modulo,string logMessage, int nivel);
    char *getArchivo() const;
    void setArchivo(char *archivo);

};

#endif /* LOGGER_H_ */
