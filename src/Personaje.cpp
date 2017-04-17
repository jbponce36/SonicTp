#include "Personaje.h"

const int POSICION_INICIALX = 0;
const int POSICION_INICIALY = 0;
const int NUMERO_DE_SPRITES = 1;

Personaje::Personaje(int velocidad,SDL_Renderer *render,int altoEscenario, Logger *log){
	this->texturaSonic = new Textura();
	this->texturaSonic->cargarImagen("images/sonicSprite.png",render, log);

	//dimensiones del personaje por defecto
	this->personajeAncho = 50;
	this->personajeAlto= 50;
	//

	this->personajeVelocidad = velocidad;

	//posicion por defecto
    this->posicionX = POSICION_INICIALX;
    this->posicionY = altoEscenario / 2;

    this->velocidadX = 0;
    this->velocidadY = personajeVelocidad;

    this->orientacion = DERECHA;

    this->saltando = false;
    this->corriendo = false;
    cargarSpriteSonic();
}

/*void Personaje::procesarEvento( SDL_Event& e )
{
    //dependiendo de la velocidad y el codigo cambia las variables para luego mover
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //ajusta la velocidad
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            	this->velocidadY -= this->personajeVelocidad;
            	//animacionActual = animacionSaltarDer;
            	saltando = true;
            	break;
            case SDLK_DOWN:
            	//this->velocidadY += this->personajeVelocidad;
            	//animacionActual = animacionSaltarDer;
            	saltando = true;
            	break;
            case SDLK_LEFT:
            	this->velocidadX-= this->personajeVelocidad;
            	animacionActual = animacionCaminarIzq;
            	orientacion = IZQUIERDA;
            	break;
            case SDLK_RIGHT:
            	this->velocidadX += this->personajeVelocidad;
            	animacionActual = animacionCaminarDer;
            	orientacion = DERECHA;
            	break;
            default:
            	return;
        }
        pasos++;
        if (saltando)
		{
			switch (orientacion)
			{
				case IZQUIERDA:
					animacionActual = animacionSaltarIzq;
					break;
				case DERECHA:
					animacionActual = animacionSaltarDer;
					break;
			}
		}
		animacionActual.comenzar();
    }
    //cambia las variables para ajustar al personaje
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //ajusta la velocidad
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            	this->velocidadY += 3*this->personajeVelocidad;
            	//animacionActual = animacionQuietoDer;
            	saltando = false;
            	break;
            case SDLK_DOWN:
            	//this->velocidadY -= this->personajeVelocidad;
            	//animacionActual = animacionQuietoDer;
            	saltando = false;
            	break;
            case SDLK_LEFT:
            	this->velocidadX += this->personajeVelocidad;
            	animacionActual = animacionCaminarDer;
            	orientacion = IZQUIERDA;
            	break;
            case SDLK_RIGHT:
            	this->velocidadX -= this->personajeVelocidad;
            	animacionActual = animacionCaminarIzq;
            	orientacion = DERECHA;
            	break;
            default:
            	return;
        }
        pasos--;
    }
	//No es un evento del teclado
    else
    {
    	return;
    }

	if (pasos == 0)
	{
		switch (orientacion)
		{
			case IZQUIERDA:
				animacionActual = animacionQuietoIzq;
				break;
			case DERECHA:
				animacionActual = animacionQuietoDer;
				break;
		}
		animacionActual.comenzar();
	}

	cout << "Event: " << velocidadX << " " << velocidadY << '\n';
}*/

void Personaje::mover(int maximoAncho,int maximoAlto, float tiempoDeJuego )
{
	/*---Limite en el suelo. Luego borrarlo!---*/
	maximoAlto -= (maximoAlto/5);
	/*-----------------------------------------*/

    //mueve al personaje
    this->posicionX += this->velocidadX * tiempoDeJuego;

    //se fija si se paso los limites de la pantalla
    if( posicionX < 0 )
    {
        posicionX = 0;
    }
    else if (posicionX + this->personajeAncho >  maximoAncho){
		//this->posicionX -= velocidadX;
		this->posicionX = maximoAncho-this->personajeAncho;
	}

    this->posicionY += this->velocidadY * tiempoDeJuego;

	//se fija si se paso los limites de la pantalla
	if( posicionY < 0 )
	{
		posicionY = 0;
	}
	else if (posicionY + this->personajeAlto >  maximoAlto){
		//this->posicionX -= velocidadX;
		this->posicionY = maximoAlto-this->personajeAlto;
		velocidadY = 0;
	}
    /*posicionY += velocidadY;

    //se fija si se paso los limites
    if( ( posicionY < 0 ) || ( posicionY + this->personajeAlto > maximoAlto ) )
    {

        this->posicionY -= velocidadY;
    }*/

	//cout << "Mover: " << velocidadX << " " << velocidadY << '\n';

}

void Personaje::cargarSpriteSonic(){
	if (texturaSonic == NULL){
		return;
	}

	animacionQuietoDer = Animacion(texturaSonic, personajeAncho, 7);
	animacionCaminarDer = Animacion(texturaSonic, personajeAncho, 2);
	animacionCorrerDer = Animacion(texturaSonic, personajeAncho, 2);
	animacionSaltarDer = Animacion(texturaSonic, personajeAncho, 2);
	animacionQuietoIzq = Animacion(texturaSonic, personajeAncho, 7);
	animacionCaminarIzq = Animacion(texturaSonic, personajeAncho, 2);
	animacionCorrerIzq = Animacion(texturaSonic, personajeAncho, 2);
	animacionSaltarIzq = Animacion(texturaSonic, personajeAncho, 2);


	for (int i=0; i<10; i++){
		animacionQuietoDer.cargarSprites(0, 0, 1);
	} //Agrega el primer sprite varias veces para que se quede quieto mas tiempo
	for (int i=0; i<5; i++){
			animacionQuietoDer.cargarSprites(1, 0, 2);
	}  //Agrega los sprites moviendo el pie varias veces

	animacionCaminarDer.cargarSprites(0, 3, 8);
	animacionCorrerDer.cargarSprites(4, 1, 5);
	animacionSaltarDer.cargarSprites(4, 1, 5);

	for (int i=0; i<10; i++){
		animacionQuietoIzq.cargarSprites(9, 0, 1);
	}
	for (int i=0; i<5; i++){
		animacionQuietoIzq.cargarSprites(10, 0, 2);
	}

	animacionCaminarIzq.cargarSprites(9, 3, 8);
	animacionCorrerIzq.cargarSprites(13, 1, 5);
	animacionSaltarIzq.cargarSprites(13, 1, 5);

	animacionActual = &animacionQuietoDer;

}

void Personaje::render( int camX, int camY){

	SDL_Rect cuadroDeVentana;

	cuadroDeVentana.x=(this->posicionX-camX);
	cuadroDeVentana.y=(this->posicionY-camY);
	cuadroDeVentana.w=this->personajeAncho;
	cuadroDeVentana.h=this->personajeAlto;
	animacionActual->dibujar(cuadroDeVentana);
}

int Personaje::getPosicionX()
{
	return this->posicionX;
}

int Personaje::getPosicionY()
{
	return this->posicionY;
}
int Personaje::getAncho(){
	return this->personajeAncho;
}
int Personaje::getAlto(){
	return this->personajeAlto;
}

Personaje::~Personaje(){
	if (texturaSonic != NULL)
	{
		delete texturaSonic;
	}
}

void Personaje::saltar()
{
	if (saltando)
	{
		switch (orientacion)
		{
			case IZQUIERDA:
				animacionActual = &animacionSaltarIzq;
				break;
			case DERECHA:
				animacionActual = &animacionSaltarDer;
				break;
		}
	}
}

void Personaje::correr(bool estaCorriendo)
{
	corriendo = estaCorriendo;
}

void Personaje::irArriba()
{
	this->velocidadY = -this->personajeVelocidad;
	saltando = true;
	saltar();
	animacionActual->comenzar();
}

void Personaje::irAbajo()
{
	this->velocidadY = this->personajeVelocidad;
	saltando = true;
	saltar();
	animacionActual->comenzar();
}

void Personaje::irIzquierda()
{
	if(corriendo){
		this->velocidadX = -2*this->personajeVelocidad;
		animacionActual = &animacionCorrerIzq;
	}
	else{
		this->velocidadX = -this->personajeVelocidad;
		animacionActual = &animacionCaminarIzq;
	}
	orientacion = IZQUIERDA;
	saltar();
	animacionActual->comenzar();
}

void Personaje::irDerecha()
{
	if (corriendo){
		this->velocidadX = 2*this->personajeVelocidad;
		animacionActual = &animacionCorrerDer;
	}
	else{
		this->velocidadX = this->personajeVelocidad;
		animacionActual = &animacionCaminarDer;
	}

	orientacion = DERECHA;
	saltar();
	animacionActual->comenzar();
}

void Personaje::parar()
{
	velocidadX = 0;
	velocidadY = 0;
	saltando = false;
	corriendo = false;
	animacionActual->detener();

	switch (orientacion)
	{
		case IZQUIERDA:
			animacionActual = &animacionQuietoIzq;
			break;
		case DERECHA:
			animacionActual = &animacionQuietoDer;
			break;
	}
	animacionActual->comenzar();

}
