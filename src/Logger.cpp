#include "Logger.h"

Logger::Logger() {
	this->nivel = MEDIO;
}

Logger::Logger(char *fileName, int level){
	this->archivo = fileName;
	this->setLevel(level);
}

Logger::Logger(char *fileName,int level, string modulo){
	this->archivo = fileName;
	this->setLevel(level);
	this->modulo = modulo;
}

void Logger::setLevel(int level)
{
	switch(level)
		{
		    case 1: this->nivel = BAJO;  break;
		    case 2: this->nivel = MEDIO; break;
		    case 3: this->nivel = ALTO;  break;
		}
}

string Logger::getLevel()
{
	switch(this->nivel)
	{
		case 1: return "BAJO";
		case 2: return "MEDIO";
		case 3: return "ALTO";
	}
	return "MEDIO";
}

int Logger::validateFileName(){

	return 0;
}
int Logger::validateLevel(){
	return 0;

}

char *Logger::getArchivo() const
{
    return archivo;
}

string Logger::getModulo() const
{
    return modulo;
}

void Logger::setModulo(string modulo)
{
    this->modulo = modulo;
}

void Logger::setArchivo(char *archivo)
{
    this->archivo = archivo;
}

void Logger::iniciarLog(){
	ofstream myfile;
	myfile.open(this->archivo, ios_base::app);

	//imprime la fecha actual
	time_t t = time(0);   // get time now
	struct tm *now = localtime( & t );
	myfile<<"["
		 <<(now->tm_year + 1900) << '-'
		 << (now->tm_mon + 1) << '-'
		 <<  now->tm_mday
		 <<  " "
		 <<  now->tm_hour
		 <<  ":"
		 <<  now->tm_min
		 <<  ":"
		 <<  now->tm_sec
		 <<"] ";

	myfile<<"INICIANDO LOGGER EN NIVEL:"<< this->getLevel()<<endl;
	myfile<<"-------------------------------------------------------------------------------------------"<<endl;
	myfile.close();

}

int Logger::addLogMessage(string logMessage, int nivel){
	if (this->nivel >= nivel){
		ofstream myfile;
		myfile.open(this->archivo, ios_base::app);

		//imprime la fecha actual
		time_t t = time(0);   // get time now
	    struct tm *now = localtime( & t );
	    myfile <<"["
	    	 <<	(now->tm_year + 1900) << '-'
	         << (now->tm_mon + 1) << '-'
	         <<  now->tm_mday
	         <<  " "
	         <<  now->tm_hour
	         <<  ":"
	         <<  now->tm_min
	         <<  ":"
	         <<  now->tm_sec
	         <<  "] ";

	    // imprime el nivel+ mensaje
		myfile <<"["<<this->modulo<<"] "<<logMessage<< endl;
		myfile.close();
		return 0;
	}
	return -1;
}

void Logger::imprimirMensajeNivelAlto(string logMessage, int valor){
	if(this->nivel == 3){
		ofstream myfile;
		myfile.open(this->archivo, ios_base::app);

		//imprime la fecha actual
		time_t t = time(0);   // get time now
		struct tm *now = localtime( & t );
		myfile <<"["
			 <<	(now->tm_year + 1900) << '-'
			 << (now->tm_mon + 1) << '-'
			 <<  now->tm_mday
			 <<  " "
			 <<  now->tm_hour
			 <<  ":"
			 <<  now->tm_min
			 <<  ":"
			 <<  now->tm_sec
			 <<  "] ";

		// imprime el nivel+ mensaje
		myfile<<"["<<this->modulo<<"] "<<logMessage<< valor<<"."<<endl;
		myfile.close();
	}
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}
