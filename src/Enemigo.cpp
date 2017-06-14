/*
 * Enemigo.cpp
 *
 *  Created on: 21 may. 2017
 *      Author: julian
 */

#include "Enemigo.h"
//lado servidor
Enemigo::Enemigo(int x, int y,std::string tipo) {
	this->vivo = true;
	this->tipoEnemigo = tipo;
	this->posicioneX = x;
	this->posicioneY = y;
	//this->SpriteActual = {0,0,20,20};
	//this->velocidad = 20;
	//this->tiempo = SDL_GetTicks();
	this->numeroSprite = 0;
	//this->contadorSprite = 0;
	//this->numeroMaximoSprites = 4;
	this->seguirEnviandoMensajes = true;
}
void Enemigo::setVivo(bool cambiarVivo){
	this->vivo = cambiarVivo;
}
std::string Enemigo::obteneMensajeEstadoInicial(){

	//Tamano es 9. Ej: c-100-200
	std::string mensaje= "";
	mensaje = mensaje + this->tipoEnemigo;
	mensaje = mensaje + this->intToStringConPadding4((int)this->posicioneX);
	mensaje = mensaje + this->intToStringConPadding4((int)this->posicioneY);
	//mensaje = mensaje + this->intToStringConPadding(this->numeroSprite);
	/*if(this->vivo == true){
		mensaje = mensaje + "v";
	}else{
		mensaje = mensaje + "m";
	}*/
	return mensaje;
}
std::string Enemigo::obteneMensajeEstado(){
	//Tamano es 11. Ej: -100-200-1v
	std::string mensaje= "";
	mensaje = mensaje + this->intToStringConPadding4((int)this->posicioneX);
	mensaje = mensaje + this->intToStringConPadding4((int)this->posicioneY);
	mensaje = mensaje + this->intToStringConPadding2(this->numeroSprite);
	if(this->vivo == true){
		mensaje = mensaje + "v";
	}else{
		mensaje = mensaje + "m";
	}
	return mensaje;
}
std::string Enemigo::intToStringConPadding4(int number)
{
	// -100
  ostringstream oss;
  oss<< number;
  std::string numero = oss.str();
  while(numero.length() < 4){
	  numero = "-" + numero;
  }
  return numero;
}
std::string Enemigo::intToStringConPadding2(int number){
	//-1
	ostringstream oss;
	oss<< number;
	std::string numero = oss.str();
	while(numero.length() < 2){
	  numero = "-" + numero;
	}
	return numero;
}
void Enemigo::actualizarPosicion(){
	cout<<"entro al acutlizar de enemigo"<<endl;
	/*if(this->vivo==true){
		Uint32 timeActual= SDL_GetTicks();
		this->calcularNumeroDeSprite();
		float timeStep = (timeActual - this->tiempo) / 1000.f;
		//cout<<"timeStep: "<<timeStep<<endl;
		float auxPosicion = this->posicionesX + ((this->velocidad)*timeStep);
		//cout<<"auxPosicion: "<<auxPosicion<<endl;
		if(this->velocidad > 0){
			if(auxPosicion > this->maximoX){
				this->velocidad = this->velocidad*(-1);
			}else{
				this->posicionesX = auxPosicion;
			}
		}else{
			if(auxPosicion < this->minimoX){
				this->velocidad = this->velocidad*(-1);
			}else{
				this->posicionesX = auxPosicion;
			}
		}
		this->tiempo = SDL_GetTicks();
	}*/
}
int Enemigo::getPosicionDeEnemigo(){
	return 0;
}
/*void Enemigo::calcularNumeroDeSprite(){
	int numSprite = 0;
	numSprite = this->contadorSprite/4;
	if(numSprite == 1 or numSprite == 2){
		if(this->velocidad > 0){
			numSprite = 1;
		}else{
			numSprite = 2;
		}
	}
	this->numeroSprite = numSprite;
	(this->contadorSprite)++;


	if( this->contadorSprite / 4 >= this->numeroMaximoSprites)
	{
		this->contadorSprite = 0;
	}

}*/
SDL_Rect Enemigo::obtenerDimensiones(){
	SDL_Rect recta = {0,0,0,0};
	return recta;
}
bool Enemigo::getSeguirEnviandoMensajes(){
	return this->seguirEnviandoMensajes;
}
void Enemigo::setSeguirEnviandoMensajes(bool seguir){
	this->seguirEnviandoMensajes = seguir;
}
void Enemigo::setNumeroSprite(int numero){
	this->numeroSprite = numero;
}
int Enemigo::getNumeroSprite(){
	return this->numeroSprite;
}
std::string Enemigo::getTipoEnemigo(){
	return this->tipoEnemigo;
}
void Enemigo::setTipoEnemigo(std::string tipo){
	this->tipoEnemigo = tipo;
}



//lado cliente
//540 en y en el primer mapa
/*Enemigo::Enemigo(int x, int y) {
	//this->Rectangulo(20,20,1,"color","images/DonCangrejo.png",0,20,98,Logger *log);
	this->tipoEnemigo ='0';
	//this->posicionesYdimensones.w = 40;
	//this->posicionesYdimensones.h= 40;
	this->posicioneX = x;
	this->posicioneY = y;
	//this->velocidad = 0;
	//this->maximoX = 0;
	//this->minimoX = 0;
	//Textura *enemigoTextura = new Textura();
	//enemigoTextura->cargarImagen("images/enemigos/DonCangrejo.png", "no hay", vista->obtenerRender(),log);
	//this->animacionEnemigo = Animacion(enemigoTextura, dimension, 0, "cangrejo");
	this->vivo = true;
	//this->animacionEnemigo.cargarSprites(0,0,4);
	//this->tiempo = 0;
	this->numeroSprite = 0;
	//this->numeroMaximoSprites = 0;
	//this->contadorSprite = 0;
	this->seguirEnviandoMensajes = true;
}*/
void Enemigo::renderizar(int camaraX, int camaraY){
	/*SDL_Rect cuadroDeVentana;
	this->animacionEnemigo.cambiarSprite(this->numeroSprite);
	//cout<<"numero animacion: "<<this->numeroSprite<<endl;;
	cuadroDeVentana.x=(this->posicionesX-camaraX);
	cuadroDeVentana.y=(this->posicionesY-camaraY);
	cuadroDeVentana.w= 90;
	cuadroDeVentana.h= 90;
	//cout<<"posicion x: "<<this->posicionesX<<endl;
	//cout<<"posicion y: "<<this->posicionesX<<endl;
	//cout<<"ancho: "<<this->posicionesYdimensones.w<<endl;
	//cout<<"largo: "<<this->posicionesYdimensones.h<<endl;
	this->animacionEnemigo.renderizar(cuadroDeVentana);*/
}
void Enemigo::cargarCaracteristicas(int x,int y, int h, int w, char tipo){
	this->tipoEnemigo = tipo;
	this->posicioneX=x;
	this->posicioneY=y;
}

bool Enemigo::getVivo(){
	return this->vivo;
}
void Enemigo::parsearMensajeInicial(std::string mensaje){
	//Mensaje es del tipo: /c-100-200
	cout<<"mensaje: "<<mensaje<<endl;
	std::string posX = mensaje.substr(2, 4);
	std::string posY = mensaje.substr(6, 4);
	posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());
	posY.erase(std::remove(posY.begin(), posY.end(), PADDING), posY.end());
	this->posicioneX = atoi(posX.c_str());
	this->posicioneY = atoi(posY.c_str());
}
void Enemigo::parsearMensaje(std::string mensaje){
	//Mensaje es del tipo: -100-200-2v
	//cout<<"mensaje: "<<mensaje<<endl;


	std::string posX = mensaje.substr(0, 4);
	std::string posY = mensaje.substr(4, 4);
	std::string numSprite = mensaje.substr(8,2);
	posX.erase(std::remove(posX.begin(), posX.end(), PADDING), posX.end());
	posY.erase(std::remove(posY.begin(), posY.end(), PADDING), posY.end());
	numSprite.erase(std::remove(numSprite.begin(), numSprite.end(), PADDING), numSprite.end());
	this->posicioneX = atoi(posX.c_str());
	this->posicioneY = atoi(posY.c_str());
	this->numeroSprite = atoi(numSprite.c_str());
	if(mensaje[10] == 'v'){
		//cout<<"esta vivo"<<endl;
	}else{
		//cout<<"muerto"<<endl;
		this->vivo=false;
	}
}

float Enemigo::getPosicionesX(){
	return this->posicioneX;
}
float Enemigo::getPosicionesY(){
	return this->posicioneY;
}
void Enemigo::setPosicionesX(float posicion){
	this->posicioneX = posicion;
}
void Enemigo::setPosicionesY(float posicion){
	this->posicioneY = posicion;
}
Enemigo::~Enemigo() {
	// TODO Auto-generated destructor stub
}

