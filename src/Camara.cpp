#include "Camara.h"

Camara::Camara(int posicionx, int posiciony, int alto, int ancho, std::map<int, Personaje*> *sonics)
: sonics(sonics){
	camaraImagen = new SDL_Rect();
	this->camaraImagen->x = posicionx;
	this->camaraImagen->y = posiciony;
	this->camaraImagen->h = alto;
	this->camaraImagen->w = ancho;
	this->margen = ancho/4;
	this->bloqueada = false;
}

void Camara::actualizar(Personaje *sonic, int maximoAncho, int maximoAlto){
//NO SE USA!

//Fija en el sonic
//this->camaraImagen->x = ( sonic->getPosicionX() + sonic->getAncho() / 2 ) - camaraImagen->w / 2;

	int posicionXSonic = sonic->getPosicionX();
	if(posicionXSonic > (camaraImagen->x + camaraImagen->w - margen))
	{
		this->camaraImagen->x += posicionXSonic - (camaraImagen->x + camaraImagen->w) + margen;
	}
	else if(posicionXSonic < (camaraImagen->x + margen))
	{
		this->camaraImagen->x -= (camaraImagen->x + margen) - posicionXSonic;
	}

	if( this->camaraImagen->x < 0 )
	{
		this->camaraImagen->x = 0;
	}
	/*if( this->camaraImagen->y < 0 )
	{
		this->camaraImagen->y = 0;
	}*/
	if( this->camaraImagen->x > maximoAncho - this->camaraImagen->w )
	{
		this->camaraImagen->x = maximoAncho - this->camaraImagen->w;
	}
	/*if( this->camaraImagen->y > maximoAlto - this->camaraImagen->h )
	{
		this->camaraImagen->y = maximoAlto - this->camaraImagen->h;
	}*/

}

void Camara::actualizar(int maximoAncho, int maximoAlto){

	/*A la camara la arrastra el sonic de mayor posicion. El que llegue al margen la arrastra.
	 Si hay un Sonic atras, se queda quieta e impide avanzar al otro Sonic.*/

	int posicionMax = 0, velocidadDelMax = 0, posicionMin = maximoAncho, velocidadDelMin = 0;
	//bloqueada = false;
	bool bloqueadaADerecha = false, bloqueadaAIzquierda = false;
	int anchoSonic;
	std::map<int, Personaje*>::iterator sonic;
	for(sonic = sonics->begin();sonic != sonics->end();sonic++){
		if (!(*sonic).second->estaCongelado()){
			if (posicionMax < (*sonic).second->getPosicionX()){
				posicionMax = (*sonic).second->getPosicionX();
				velocidadDelMax = (*sonic).second->getVelocidadX();
			}
			if (posicionMin > (*sonic).second->getPosicionX()){
				posicionMin = (*sonic).second->getPosicionX();
				velocidadDelMin = (*sonic).second->getVelocidadX();
			}
		}
		/*if ((*sonic).second->bloqueaCamara(camaraImagen)){
			bloqueada = true;
		}*/
		if ((*sonic).second->bloqueaCamaraADerecha(camaraImagen)){
			bloqueadaADerecha = true;
		}
		if ((*sonic).second->bloqueaCamaraAIzquierda(camaraImagen)){
			bloqueadaAIzquierda = true;
		}
		anchoSonic = (*sonic).second->getAncho();
	}

	if(velocidadDelMax < 0)
		velocidadDelMax = -velocidadDelMax;


	//Si el sonic de mayor posicion llega al margen y no hay nadie bloqueando, arrastra la camara
	if(posicionMax + anchoSonic > (camaraImagen->x + camaraImagen->w - margen))
	{
		if(posicionMin > (camaraImagen->x + margen))
		{
			this->camaraImagen->x += posicionMax - (camaraImagen->x + camaraImagen->w) + margen;
		}
		else //El minimo esta en el costado izquierdo
		{
			if(velocidadDelMin == 0)
			{
				if (!bloqueadaAIzquierda)
					this->camaraImagen->x += velocidadDelMax*0.04;
			}
			else if (velocidadDelMin > 0)
			{
				this->camaraImagen->x += velocidadDelMin*0.04;
			}
		}


		//if(!bloqueada)
			//this->camaraImagen->x += posicionMax - (camaraImagen->x + camaraImagen->w) + margen;
	}
	else if(posicionMin < (camaraImagen->x + margen))
	{
		if(velocidadDelMax == 0)
		{
			if (velocidadDelMin < 0) //Quiere ir a la izquierda
				if(!bloqueadaADerecha){
					this->camaraImagen->x += velocidadDelMin*0.04;
					cout << "No esta bloqueada a derecha. Todo ok.\n";
				}
		}
		else
		{
			this->camaraImagen->x -= velocidadDelMax*0.04;
		}

		//this->camaraImagen->x -= (camaraImagen->x + margen) - posicionMax;
	}



	//Si llega a los limites del escenario la detiene
	if( this->camaraImagen->x > maximoAncho - this->camaraImagen->w )
	{
		this->camaraImagen->x = maximoAncho - this->camaraImagen->w;
	}
	else if( this->camaraImagen->x < 0 )
	{
		this->camaraImagen->x = 0;
	}

}

void Camara::actualizarXY(int x, int y)
{
	//Lo usa la camara del cliente
	camaraImagen->x = x;
	camaraImagen->y = y;
}

std::string Camara::intToStringConPadding(int number)
{
  ostringstream oss;
  oss<< number;
  std::string numero = oss.str();
  while(numero.length() < MAX_CANT_DIGITOS_POS){
	  numero = PADDING + numero;
  }
  return numero;
}

std::string Camara::obtenerMensajeEstado()
{
	return ("x" + intToStringConPadding(camaraImagen->x) + "y" + intToStringConPadding(camaraImagen->y));
}

SDL_Rect *Camara::devolverCamara(){
	return this->camaraImagen;
}
int Camara::getPosicionX(){
	return this->camaraImagen->x;
}
int Camara::getPosicionY(){
	return this->camaraImagen->y;
}

Camara::~Camara() {
	// TODO Auto-generated destructor stub
	delete camaraImagen;
}

