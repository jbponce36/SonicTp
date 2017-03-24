#include "Logger.h"

Logger::Logger() {
	this->nivel = DEBBUG;
}

Logger::Logger(char *fileName, int level){
	this->archivo = fileName;
	this->setLevel(level);
}


void Logger::setLevel(int level)
{
	switch(level)
		{
		    case 1: this->nivel = INFO;   break;
		    case 2: this->nivel = DEBBUG; break;
		    case 3: this->nivel = ERROR;  break;
		}
}

char* Logger::getLevel() const
{
	switch(this->nivel)
	{
		case 1: return "INFO";
		case 2: return "DEBBUG";
		case 3: return "ERROR";
	}
	return "SS";
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

void Logger::setArchivo(char *archivo)
{
    this->archivo = archivo;
}

int Logger::addLogMessage(string modulo,string logMessage){
	if (validateFileName() == 0){
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
		myfile <<"["<< this->getLevel()<<"] "<<"["<<modulo<<"] "<<logMessage<< endl;
		myfile.close();
		return 0;
	}

	return -1;
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}
