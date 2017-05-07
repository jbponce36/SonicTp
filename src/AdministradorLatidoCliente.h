/*
 * AdministradorLatidoCliente.h
 *
 *  Created on: 4 may. 2017
 *      Author: pato
 */

#ifndef ADMINISTRADORLATIDOCLIENTE_H_
#define ADMINISTRADORLATIDOCLIENTE_H_

#include <time.h>
#include <stdio.h>
#include "Hilo.h"
#include "Paquete.h"
namespace std {

class AdministradorLatidoCliente {
private:
	time_t end_t;
	ConexCliente *cliente;
	Paquete *colaPaquete;
	Hilo h;
public:


	void actualizarTiempoLatido();
	//bool pasoDemasiadoTiempoDelUltimoLatido();

	AdministradorLatidoCliente(Paquete *colaPaquete);
	~AdministradorLatidoCliente();
	void IniciarHilo();
	static void* iniciarContador(void *ars);
	struct SerParametros{
		ConexCliente *cliente;
	//	time_t *end_t;

	};
	SerParametros parametros;

	ConexCliente* getconexcliente();
	void setconexcliente(ConexCliente *c);
	Hilo gethilo();

	void setH(Hilo);

};

} /* namespace std */

#endif /* ADMINISTRADORLATIDOCLIENTE_H_ */
