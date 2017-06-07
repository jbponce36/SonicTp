/*
 * Usuario.h
 *
 *  Created on: 7 jun. 2017
 *      Author: joha
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include <string>

namespace std {

class Usuario {
public:

	enum ModoJuego {INDIVIDUAL = 1, COLABORATIVO=2, GRUPAL=3 };
	Usuario();
	Usuario(string nombre, string contrasenia);
	bool esValido();
	virtual ~Usuario();
	string getContrasenia() ;
	void setContrasenia( string contrasenia);
	int getIdPersonaje() ;
	void setIdPersonaje(int idPersonaje);
	ModoJuego getModoJuego() ;
	void setModoJuego(ModoJuego modoJuego);
	string getNombre() ;
	void setNombre( string nombre);



private:
	string nombre;
	string contrasenia;
	int idPersonaje;
	ModoJuego modoJuego;
};

} /* namespace std */

#endif /* USUARIO_H_ */
