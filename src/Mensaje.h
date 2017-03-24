#ifndef MENSAJE_H_
#define MENSAJE_H_

#include <stdio.h>
#include <time.h>
#include <iostream>

using namespace std;

class Mensaje {

private:
	time_t fecha;
	string modulo;
	string descripcion;
	int nivel;

public:
	Mensaje();
	virtual ~Mensaje();
    string getDescripcion() const;

    int getNivel() const;
    void setDescripcion(string descripcion);

    void setNivel(int nivel);
    void imprimirMensaje();
    time_t getFecha() const;
    void setFecha(time_t fecha);
    string getModulo() const;
    void setModulo(string modulo);
};

#endif /* MENSAJE_H_ */
