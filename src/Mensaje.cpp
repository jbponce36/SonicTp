#include "Mensaje.h"

Mensaje::Mensaje() {
	// TODO Auto-generated constructor stub

}

string Mensaje::getDescripcion() const
{
    return descripcion;
}

int Mensaje::getNivel() const
{
    return nivel;
}

void Mensaje::setDescripcion(string descripcion)
{
    this->descripcion = descripcion;
}


void Mensaje::setNivel(int nivel)
{
    this->nivel = nivel;
}

time_t Mensaje::getFecha() const
{
	time_t t = time(0);   // get time now
	return t;

}

string Mensaje::getModulo() const
{
    return modulo;
}

void Mensaje::setModulo(string modulo)
{
    this->modulo = modulo;
}

void Mensaje::setFecha(time_t fecha)
{
    this->fecha = fecha;
}

void Mensaje::imprimirMensaje(){
	struct tm * now = localtime(&this->fecha);

}

Mensaje::~Mensaje() {
	// TODO Auto-generated destructor stub
}
