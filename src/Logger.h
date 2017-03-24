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
	enum Nivel {INFO = 1, DEBBUG=2, ERROR=3 };
	Nivel nivel;
	vector<string> logMessages;

public:
	Logger();
	Logger(char *fileName, int level);
	virtual ~Logger();

	char* getLevel() const;
	void setLevel(int level);

	int validateFileName();
	int validateLevel();
	int addLogMessage(string modulo,string logMessage);
    char *getArchivo() const;
    void setArchivo(char *archivo);

};

#endif /* LOGGER_H_ */
