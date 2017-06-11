/*
 * AdminsitradorDeNiveles.cpp
 *
 *  Created on: 22 may. 2017
 *      Author: cristian
 */

#include "AdministradorDeNiveles.h"
#include "ControlServidor.h"


AdministradorDeNiveles::AdministradorDeNiveles(){

	this->nivelActual = 0;
	this->nivelServidor = 0;
}

void AdministradorDeNiveles::pasarDeNivel(){

	if( this->nivelActual <= 5 )
	{
		//cout<<"paso de nivel"<<nivelActual<<endl;
		this->nivelActual += 2;
	}
}

void AdministradorDeNiveles::cargarNivel(VistaSDL* vista,Personaje* sonic){
	if( this->nivelActual <= 5 )
	{

		this->capa0 = vista->obtenerTextura(this->nivelActual);
		this->capa1 = vista->obtenerTextura(this->nivelActual + 1);
		//sonic->posicionarseEn(200,500);
	}
}

void AdministradorDeNiveles::mostrarNivel(Camara *camara, VistaSDL *vista, SDL_Rect *imagenMostrar){

	capa0->renderizar(camara->devolverCamara(),imagenMostrar);
	capa1->renderizar(camara->devolverCamara(),imagenMostrar);
}

void AdministradorDeNiveles::setNivel(int nivel){

	this->nivelActual = nivel;
}

int AdministradorDeNiveles::getNivel(){

	return this->nivelActual;
}

bool AdministradorDeNiveles::EsUltimoNivel(){

	return (this->nivelActual == 5);
}

AdministradorDeNiveles::~AdministradorDeNiveles(){

}

void AdministradorDeNiveles::mostrarPunConPan(VistaSDL* vista,vector<Personaje*>*personajes){

	// ACA CARGAMOS LA PANTALLA DE PUNTOS
		this->pantallaPuntos = new Textura();
		this->pantallaPuntos->cargarImagen("images/entidad1.png","images/entidad1.png",vista->getRenderizador(),vista->getLog());
		SDL_Rect cuadventana;
		cuadventana.x = 0;
		cuadventana.y = 0;
		cuadventana.h = vista->getAltoVentana();
		cuadventana.w = vista->getAnchoVentana();
		pantallaPuntos->renderizar(&cuadventana,&cuadventana);

		SDL_Rect camara;
		SDL_Rect imagenMostrar;

		SDL_SetRenderDrawColor(vista->getRenderizador(),0xff,0xff,0xff,0xff);
		SDL_RenderClear(vista->getRenderizador());

		camara.x = 0;
		camara.y = 0;
		camara.w = pantallaPuntos->obtenerAnchoTextura();
		camara.h = pantallaPuntos->obtenerAltoTextura();

		imagenMostrar.x = 0;
		imagenMostrar.y = 0;
		//imagenMostrar.w = menuInicial->obtenerAnchoTextura();
		//imagenMostrar.h = menuInicial->obtenerAltoTextura();
		imagenMostrar.w = vista->getAnchoVentana();
		imagenMostrar.h = vista->getAltoVentana();
		pantallaPuntos->renderizar(&camara,&imagenMostrar);
		/*camara.w = texturaConectar->obtenerAnchoTextura();
		camara.h = texturaConectar->obtenerAltoTextura();
		switch (seleccion){
			case 0:
			texturaConectar.renderizar(&imagenMostrar,&camara);
			break;

			case 1:
			texturaDesconectar.renderizar(&imagenMostrar,&camara);
			break;

			case 2:
			texturaSalir.renderizar(&imagenMostrar,&camara);
			break;
		}
		*/
		vista->mostrarScoJueIndTodosFinNiv(personajes);

		SDL_RenderPresent(vista->getRenderizador());

		sleep(3);
}
void AdministradorDeNiveles::pasarNivelServidor(VistaSDL* vista,ControlServidor* controlSevidor){


	nivelServidor++;
	jescenarioJuego* jjuego = vista->obtenerNivel(nivelServidor);
	controlSevidor->CreoAnillas(jjuego->getAnillo()->getMinimoran(),jjuego->getAnillo()->getMaximoran());
	controlSevidor->CreoPiedras(jjuego->getPiedra()->getMinimoran(),jjuego->getPiedra()->getMaximoran());
	controlSevidor->CreoPinche(jjuego->getPinche()->getMinimoran(),jjuego->getPinche()->getMaximoran());
	jjuego->getEscenario()->getentidades()


}

void AdministradorDeNiveles::pasarNivelReset(VistaSDL*vista){

	for(int i = 0 ; i < 3; i++)
	{
		vista->getJjuego();

       // control->CreoAnillas();
	}
}
