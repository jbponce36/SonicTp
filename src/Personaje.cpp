#include "Personaje.h"
#include "debug.h"
#include "Puntaje.h"
#include "ControlServidor.h"


const int POSICION_INICIALX = 0;
const int POSICION_INICIALY = 0;

Personaje::Personaje(int id, int velocidad,SDL_Renderer *render,int altoEscenario, Logger *log)
{
	this->id = id;

	this->texturaSonic = new Textura();
	this->texturaCongelado = new Textura();
	this->texturaEscudo = new Textura();
	this->texturaInvencible = new Textura();
	//this->texturaAtaque = new Textura();

	std::string rutaImagen = "images/sonicSprite" + intToString(id) +".png";
	this->texturaSonic->cargarImagen(rutaImagen, IMAGEN_POR_DEFECTO, render, log);
	this->texturaCongelado->cargarImagen("images/sonicgris.png", IMAGEN_POR_DEFECTO, render, log);
	this->texturaEscudo->cargarImagen("images/BonusEscudo.png", "images/BonusEscudo.png", render, log);
	this->texturaInvencible->cargarImagen("images/BonusInvencibilidad.png", "images/BonusInvencibilidad.png", render, log);

	//this->texturaAtaque->cargarImagen("images/ataque.png", "images/ataque.png", render, log);
	//dimensiones del personaje por defecto
	this->personajeAncho = 150;
	this->personajeAlto= 150;

	this->personajeVelocidad = velocidad;
	this->personajeAceleracion = velocidad/20;
	//posicion por defecto
    this->posicionX = POSICION_INICIALX + id*20 - 20; //Para que no esten en el mismo lugar al empezar
    if(posicionX < 0)
    	posicionX = POSICION_INICIALX;
    this->posicionY = 4*altoEscenario/5 - personajeAlto;

    this->velocidadX = 0;
    this->velocidadY = 0;
    this->grupo = 1;

    this->orientacion = DERECHA;

    this->saltando = false;
    this->corriendo = false;
    this->estaQuieto = true;
    this->congelado = false;
    this->tieneEscudo = false;
    this->esInmortal = false;
    this->esInvencible = false;
    this->herido = false;
    this->estaVivo = true;
    this->duracionInvencibilidad = 20.0;

    this->puntaje = new Puntaje(id, render,log);

    cargarSpriteSonic();
    this->log = log;
    this->puntos = new Puntos(this->id);
    this->puedeIrDerecha = true;
    this->puedeIrIzquierda = true;
    this->colisionando = false;
    this->resbalando = false;

    this->ataque = false;
}

void Personaje::mover(SDL_Rect *limites, float tiempoDeJuego)
{
	int maximoAlto = limites->h;
	int maximoAncho = limites->w;

	/*Limite en el suelo.*/
	maximoAlto -= (maximoAlto/5);

    //mueve al personaje
    this->posicionX += this->velocidadX * REGULADOR_ALTURA_SALTO;

    //se fija si se paso los limites de la pantalla
    if( posicionX < limites->x )
    {
    	//velocidadX = 0;
        posicionX = limites->x;
    }
    else if (posicionX + this->personajeAncho - limites->x >  maximoAncho){
    	//velocidadX = 0;
		this->posicionX = maximoAncho-this->personajeAncho+limites->x;
	}

    //Si esta saltando lo afecta la gravedad
    if (saltando){
    	this->velocidadY += GRAVEDAD;
    }

    this->posicionY += this->velocidadY * REGULADOR_ALTURA_SALTO;

	//se fija si se paso los limites de la pantalla
	if( posicionY < 0 )
	{
		posicionY = 0;
	}
	else if (posicionY + this->personajeAlto >  maximoAlto){
		this->posicionY = maximoAlto-this->personajeAlto;
		saltando = false; //Al tocar el piso deja de saltar
		resbalando = false;
		parar();
	}

	if(posicionY + personajeAlto < maximoAlto){
		saltando = true; //Esta en el aire.
	}
	//cout << "Mover: " << velocidadX << " " << velocidadY << '\n';

}

void Personaje::cargarSpriteSonic(){
	if (texturaSonic == NULL){
		return;
	}

	if(puntaje->getTexturaPuntaje() == NULL){
		cout<<"textura puntaje no cargada"<<endl;
	}

	animacionQuietoDer = Animacion(texturaSonic, personajeAncho, 7, ANIMACION_QUIETO_DERECHA);
	animacionCaminarDer = Animacion(texturaSonic, personajeAncho, 2, ANIMACION_CAMINAR_DERECHA);
	animacionCorrerDer = Animacion(texturaSonic, personajeAncho, 2, ANIMACION_CORRER_DERECHA);
	animacionSaltarDer = Animacion(texturaSonic, personajeAncho, 2, ANIMACION_SALTAR_DERECHA);
	animacionQuietoIzq = Animacion(texturaSonic, personajeAncho, 7, ANIMACION_QUIETO_IZQUIERDA);
	animacionCaminarIzq = Animacion(texturaSonic, personajeAncho, 2, ANIMACION_CAMINAR_IZQUIERDA);
	animacionCorrerIzq = Animacion(texturaSonic, personajeAncho, 2, ANIMACION_CORRER_IZQUIERDA);
	animacionSaltarIzq = Animacion(texturaSonic, personajeAncho, 2, ANIMACION_SALTAR_IZQUIERDA);
	animacionCongelado = Animacion(texturaCongelado, personajeAncho, 1, ANIMACION_CONGELADO);
	animacionEscudo = Animacion(texturaEscudo, personajeAncho + 50, 2, ANIMACION_ESCUDO);
	animacionInvencible = Animacion(texturaInvencible, personajeAncho + 50, 2, ANIMACION_INVENCIBLE);
	puntaje->setAnimacionPuntaje(Animacion(puntaje->getTexturaPuntaje(), puntaje->getAlto(), 1, ANIMACION_PUNTAJE));

	animacionAtaqueDer = Animacion(texturaSonic, personajeAncho, 1, ANIMACION_ATAQUE_DERECHA);
	animacionAtaqueIzq = Animacion(texturaSonic, personajeAncho, 1, ANIMACION_ATAQUE_IZQUIERDA);

	//for (int i=0; i<10; i++){
	//	animacionQuietoDer.cargarSprites(0, 0, 1);
	//} //Agrega el primer sprite varias veces para que se quede quieto mas tiempo
	//for (int i=0; i<5; i++){
	//		animacionQuietoDer.cargarSprites(1, 0, 2);
	//}  //Agrega los sprites moviendo el pie varias veces

	//animacionCaminarDer.cargarSprites(0, 3, 8);
	//animacionCorrerDer.cargarSprites(4, 1, 5);
	//animacionSaltarDer.cargarSprites(4, 1, 5);

	//for (int i=0; i<10; i++){
	//	animacionQuietoIzq.cargarSprites(9, 0, 1);
	//}
	//for (int i=0; i<5; i++){
	//	animacionQuietoIzq.cargarSprites(10, 0, 2);
	//}

	//animacionCaminarIzq.cargarSprites(9, 3, 8);
	//animacionCorrerIzq.cargarSprites(13, 1, 5);
	//animacionSaltarIzq.cargarSprites(13, 1, 5);

	//desde aca es el codigo del nuevo set de sprites
	animacionQuietoDer.cargarSprites(0, 0, 1);
	animacionCaminarDer.cargarSprites(1, 0, 9);
	animacionCorrerDer.cargarSprites(0, 1, 4);
	animacionSaltarDer.cargarSprites(0, 2, 9);
	animacionAtaqueDer.cargarSprites(0, 2, 9);

	animacionQuietoIzq.cargarSpritesAlReves(9, 3, 1);
	animacionCaminarIzq.cargarSpritesAlReves(0, 3, 9);
	animacionCorrerIzq.cargarSpritesAlReves(6, 4, 4);
	animacionSaltarIzq.cargarSpritesAlReves(1, 5, 9);
	animacionAtaqueIzq.cargarSpritesAlReves(1, 5, 9);

	animacionCongelado.cargarSprites(0, 0, 1);

	animacionEscudo.cargarSprites(0, 0, 4);

	animacionInvencible.cargarSprites(0, 0, 4);
	animacionInvencible.cargarSprites(0, 1, 4);

	puntaje->getAnimacionPuntaje().cargarSprites(0,0,1);

	animacionActual = &animacionQuietoDer;
	animacionBonus = NULL;


}

void Personaje::render( int camX, int camY){

	if(herido){
		if(animacionActual->esFotogramaPar()){
			return;
		}
	}

	SDL_Rect cuadroDeVentana;

	cuadroDeVentana.x=(this->posicionX-camX);
	cuadroDeVentana.y=(this->posicionY-camY);
	cuadroDeVentana.w=this->personajeAncho;
	cuadroDeVentana.h=this->personajeAlto;
	animacionActual->dibujar(cuadroDeVentana);

	if (animacionBonus != NULL)
	{
		cuadroDeVentana.x=(this->posicionX-camX-25);
		cuadroDeVentana.y=(this->posicionY-camY-25);
		cuadroDeVentana.w=this->personajeAncho+50;
		cuadroDeVentana.h=this->personajeAlto+50;
		animacionBonus->dibujar(cuadroDeVentana);
	}
}

void Personaje::posicionarseEn(int x, int y)
{
	this->posicionX = x;
	this->posicionY = y;
}

void Personaje::posicionarseConAnimacion(int x, int y, std::string animacion, int indiceAnimacion)
{
	//Esto lo usa el cliente!
	posicionarseEn(x, y);

	std::string animacionAnterior = animacionActual->obtenerNombre();
	if(animacionAnterior.compare(animacion) == 0)
	{
		return;
	}

	animacionActual->detener();

	if(animacion.compare(ANIMACION_QUIETO_DERECHA) == 0){
		animacionActual = &animacionQuietoDer;
	}
	else if(animacion.compare(ANIMACION_CAMINAR_DERECHA) == 0){
		animacionActual = &animacionCaminarDer;
	}
	else if(animacion.compare(ANIMACION_CORRER_DERECHA) == 0){
		animacionActual = &animacionCorrerDer;
	}
	else if(animacion.compare(ANIMACION_SALTAR_DERECHA) == 0){
		animacionActual = &animacionSaltarDer;
	}
	else if(animacion.compare(ANIMACION_QUIETO_IZQUIERDA) == 0){
		animacionActual = &animacionQuietoIzq;
	}
	else if(animacion.compare(ANIMACION_CAMINAR_IZQUIERDA) == 0){
		animacionActual = &animacionCaminarIzq;
	}
	else if(animacion.compare(ANIMACION_CORRER_IZQUIERDA) == 0){
		animacionActual = &animacionCorrerIzq;
	}
	else if(animacion.compare(ANIMACION_SALTAR_IZQUIERDA) == 0){
		animacionActual = &animacionSaltarIzq;
	}
	else if(animacion.compare(ANIMACION_CONGELADO) == 0){
		animacionActual = &animacionCongelado;
	}
	else if(animacion.compare(ANIMACION_TITILAR) == 0){
		herido = true;
	}
	else if(animacion.compare(ANIMACION_NO_TITILAR) == 0){
		herido = false;
	}
	else if(animacion.compare(ANIMACION_ATAQUE_DERECHA) == 0){
		animacionActual = &animacionAtaqueDer;
	}
	else if(animacion.compare(ANIMACION_ATAQUE_IZQUIERDA) == 0){
		animacionActual = &animacionAtaqueIzq;
	}
	else
	{
		//Es una animacion de bonus
		if(animacionBonus != NULL)
			animacionBonus->detener();

		if(animacion.compare(ANIMACION_ESCUDO) == 0){
			ponerseEscudo();
			animacionBonus->comenzar();
		}
		else if(animacion.compare(ANIMACION_INVENCIBLE) == 0){
			serInvencible();
			animacionBonus->comenzar();
		}
		else if(animacion.compare(ANIMACION_SIN_BONUS) == 0){
			quitarseEscudo();
			dejarDeSerInvencible();
		}
	}

	animacionActual->comenzar();
}

int Personaje::getPosicionX()
{
	return this->posicionX;
}
int Personaje::getPosicionY()
{
	return this->posicionY;
}
int Personaje::getVelocidadX()
{
	return this->velocidadX;
}
int Personaje::getAncho(){
	return this->personajeAncho;
}
int Personaje::getAlto(){
	return this->personajeAlto;
}
int Personaje::getId(){
	return this->id;
}
std::string Personaje::getNombreAnimacion()
{
	return animacionActual->obtenerNombre();
}
std::string Personaje::getEstadoAnimacion()
{
	return intToString(animacionActual->obtenerIndiceSprite());
}

Personaje::~Personaje(){
	if (texturaSonic != NULL){
		delete texturaSonic;
	}
	if (texturaCongelado != NULL){
		delete texturaCongelado;
	}
	if(texturaEscudo != NULL){
		delete texturaEscudo;
	}
	if(texturaInvencible != NULL){
		delete texturaInvencible;
	}
	delete puntaje;
	delete puntos;
}

void Personaje::dejarDeEstarQuieto()
{
	if (estaQuieto)
	{
		estaQuieto = false;
		animacionActual->detener();
	}
}

void Personaje::animarSalto()
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

void Personaje::saltar()
{
	if (!saltando)
	{
		velocidadY = -personajeVelocidad;
		saltando = true;
	}
}

void Personaje::dejarDeSaltar()
{
	if(velocidadY < (-personajeVelocidad/2))
	{
		velocidadY = (-personajeVelocidad/2);
	}
}

void Personaje::correr(bool estaCorriendo)
{
	corriendo = estaCorriendo;
}

void Personaje::resbalar(Orientacion haciaDonde)
{
	saltando = false;
	resbalando = true;
	switch (haciaDonde)
	{
		case IZQUIERDA:
			velocidadX = -personajeVelocidad;
			break;
		case DERECHA:
			velocidadX = personajeVelocidad;
			break;
	}
}

void Personaje::rebotar()
{
	velocidadY = -velocidadY;
}

void Personaje::herir(ControlServidor *control)
{
	if (esInmortal)
		return;

	if (esInvencible)
		return;

	if(herido)
		return;

	if (tieneEscudo)
	{
		quitarseEscudo();
		return;
	}

	if(puntos->getCantAnillos() > 0)
	{
		//Sonic tiene anillos. Sacarselos
		puntos->setCantAnillos(0);
		titilarPorHerida(control);
		//Titilar
	}
	else
	{
		if(puntos->getVidas() <= 0)
		{
			if (esInmortal)
			{
				titilarPorHerida(control);
				return;
				//Titilar
			}
			else
			{
				//Aca Sonic pierde el juego
				cout << "Game Over!\n";
				estaVivo = false;
				control->gameOverJugador(id);
			}
		}
		else
		{
			//Sonic no tiene anillos pero tiene vidas
			puntos->restarUnaVida();
			serInvencible(DURACION_INVENCIBLE_HERIDO);
		}
	}
}

void Personaje::irArriba()
{
	dejarDeEstarQuieto();
	animarSalto();
	animacionActual->comenzar();
}

void Personaje::irAbajo()
{
	/*this->velocidadY = this->personajeVelocidad;
	saltando = true;
	animarSalto();
	animacionActual->comenzar();*/
}

void Personaje::irIzquierda()
{
	if (this->puedeIrIzquierda)
	{
		dejarDeEstarQuieto();
		if(this->ataque){
			animacionActual = &animacionAtaqueIzq;
		}else if (corriendo){
			/*this->velocidadX -= 2*personajeAceleracion;
			if(velocidadX < (-2*personajeVelocidad))
			{
				velocidadX = -2*personajeVelocidad;
			}*/
			this->velocidadX = -2*personajeVelocidad;
			animacionActual = &animacionCorrerIzq;
		}
		else{
			/*this->velocidadX -= personajeAceleracion;
			if(velocidadX < (-personajeVelocidad))
			{
				velocidadX = -personajeVelocidad;
			}*/
			this->velocidadX = -personajeVelocidad;
			animacionActual = &animacionCaminarIzq;
		}

		orientacion = IZQUIERDA;
		animarSalto();
		animacionActual->comenzar();
	}
}

void Personaje::irDerecha()
{
	if (this->puedeIrDerecha){

		dejarDeEstarQuieto();
		if(this->ataque){
			animacionActual = &animacionAtaqueDer;
		}else if (corriendo){
			/*this->velocidadX += 2*personajeAceleracion;
			if(velocidadX > 2*personajeVelocidad)
			{
				velocidadX = 2*personajeVelocidad;
			}*/
			this->velocidadX = 2*personajeVelocidad;
			animacionActual = &animacionCorrerDer;
		}
		else{
			/*this->velocidadX += personajeAceleracion;
			if(velocidadX > personajeVelocidad)
			{
				velocidadX = personajeVelocidad;
			}*/
			this->velocidadX = personajeVelocidad;
			animacionActual = &animacionCaminarDer;
		}

		orientacion = DERECHA;
		animarSalto();
		animacionActual->comenzar();
	}
}

void Personaje::reanudarLuegoDeColision()
{
	colisionando = false;
	this->puedeIrDerecha = true;
	this->puedeIrIzquierda = true;
	this->resbalando = false;
	//velocidadX = 0;
}

void Personaje::detener()
{
	velocidadX = 0;
	saltando = false;
}

void Personaje::pararPorColision(SDL_Rect obstaculo)
{
	colisionando = true;
	detener();

	if(posicionX < obstaculo.x)
	{
		//Si sonic esta colisionando a la izquierda de la piedra
		SDL_Rect limites = obtenerLimites();
		int diferenciaX = limites.x + limites.w - obstaculo.x;
		posicionX -= diferenciaX;
	}

	if(posicionX > obstaculo.x)
	{
		//Si sonic esta colisionando a la derecha de la piedra
		SDL_Rect limites = obtenerLimites();
		int diferenciaX = obstaculo.x + obstaculo.w - limites.x;
		posicionX += diferenciaX;
	}
}


void Personaje::parar()
{
	/*if (velocidadX < 0)
	{
		velocidadX += 2*personajeAceleracion;
		if (velocidadX >= 0)
			velocidadX = 0;
	}
	else if(velocidadX > 0)
	{
		velocidadX -= 2*personajeAceleracion;
		if (velocidadX <= 0)
			velocidadX = 0;
	}*/
	if(resbalando)
		return;

	velocidadX = 0;

	if (saltando)
		return;

	if (estaQuieto)
		return;

	velocidadY = 0;

	if (velocidadX == 0){
		estaQuieto = true;

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

}

void Personaje::congelar()
{
	velocidadX = 0;
	velocidadY = 0;
	estaQuieto = true;
	saltando = false;
	corriendo = false;
	animacionActual->detener();
	animacionActual = &animacionCongelado;
	congelado = true;
}

void Personaje::descongelar()
{
	animacionActual = &animacionQuietoDer;
	congelado = false;
}

bool Personaje::bloqueaCamara(SDL_Rect *limites)
{
	if (congelado)
	{
		return false;
	}
	return ((posicionX <= limites->x) || ((posicionX + personajeAncho) >= (limites->x + limites->w)));
}

bool Personaje::bloqueaCamaraADerecha(SDL_Rect *limites)
{
	if (congelado)
	{
		return false;
	}
	return ((posicionX + personajeAncho) >= (limites->x + limites->w));
}

bool Personaje::bloqueaCamaraAIzquierda(SDL_Rect *limites)
{
	if (congelado)
	{
		return false;
	}
	return (posicionX <= limites->x);
}

bool Personaje::estaCongelado()
{
	return congelado;
}

bool Personaje::estaParado()
{
	return ((velocidadX == 0) && (velocidadY == 0));
}

bool Personaje::estaAtacando()
{
	//Agregar cuando este haciendo el SpinAttack
	if (saltando or ataque)
	{
		return true;
	}
	return false;
}

bool Personaje::sigueVivo()
{
	return estaVivo;
}

void Personaje::dejarDeEstarVivo()
{
	estaVivo = false;
	velocidadX = 0;
	velocidadY = 0;
	estaQuieto = true;
	saltando = false;
	corriendo = false;
	congelado = true;
}

std::string Personaje::intToStringConPadding(int number)
{
  ostringstream oss;
  oss<< number;
  std::string numero = oss.str();
  while(numero.length() < MAX_CANT_DIGITOS_POS){
	  numero = PADDING + numero;
  }
  return numero;
}

std::string Personaje::intToString(int number)
{
	ostringstream oss;
	oss<< number;
	return oss.str();
}

void Personaje::enviarAServer(HiloEnviarCliente *hiloEnviar, std::string mensaje)
{int getGrupo();
	mensaje = intToString(id) + mensaje + "x" + intToStringConPadding(posicionX) + "y" + intToStringConPadding(posicionY);

	char buffer[LARGO_MENSAJE_POSICION_CLIENTE] = "";
	strcpy(buffer, mensaje.c_str());
	//hiloEnviar->parametros.buffer = buffer;

	hiloEnviar->enviarDato(buffer);
	//cout << "Cliente envio: " << buffer << endl;

}

Puntaje* Personaje::getPuntaje() {
	return puntaje;
}

void Personaje::setPuntaje(Puntaje* puntaje) {
	this->puntaje = puntaje;
}

Puntos* Personaje::getPuntos() {
	return puntos;
}

void Personaje::setPuntos(Puntos* puntaje) {
	this->puntos = puntaje;
}

void Personaje::setGrupo(int grupo)
{
	this->grupo = grupo;
}

std::string Personaje::obtenerMensajeEstado()
{
	//Tamano es 15. Ej: 1x-300y--20AcD1
	return (intToString(id)
			+ "x" + intToStringConPadding(posicionX)
			+ "y" + intToStringConPadding(posicionY)
			+ getNombreAnimacion() + getEstadoAnimacion());
}

std::string Personaje::obtenerMensajeEstadoBonus()
{
	std::string nombreAnimacion;
	if (animacionBonus != NULL){
		nombreAnimacion = animacionBonus->obtenerNombre();
	}
	else{
		nombreAnimacion = ANIMACION_SIN_BONUS;
	}

	return ( Util::intToString(getId())
		+ "x" + Util::intToStringConPadding(getPosicionX())
		+ "y" + Util::intToStringConPadding(getPosicionY())
		+ nombreAnimacion + PADDING);
}

SDL_Rect Personaje::obtenerLimites(){

	SDL_Rect limites = {this->posicionX+15, this->posicionY+15, this->personajeAncho-30, this->personajeAlto-25};
	return limites;
}

/*----------Para bonus. Los usa el servidor----------*/
void Personaje::aumentarCantidadAnillos(int cantidad)
{
	puntaje->setCantAnillos(puntaje->getCantAnillos()+cantidad);
	puntos->sumarXanillos(cantidad);
}

void Personaje::ponerseEscudo()
{
	tieneEscudo = true; //Al ser atacado preguntar por este bool
	esInvencible = false;
	animacionBonus = &animacionEscudo;
}

void Personaje::quitarseEscudo()
{
	tieneEscudo = false;
	animacionBonus = NULL;
}

void Personaje::serInvencible()
{
	//Para el cliente
	esInvencible = true;
	tieneEscudo = false;
	animacionBonus = &animacionInvencible;
}

void Personaje::serInvencible(int segundos)
{
	//Para el servidor
	time(&tiempoInicioInvencible);
	esInvencible = true;
	tieneEscudo = false;
	animacionBonus = &animacionInvencible;
	duracionInvencibilidad = segundos;
}

void Personaje::dejarDeSerInvencible()
{
	esInvencible = false;
	animacionBonus = NULL;
}

bool Personaje::sigueSiendoInvencible()
{
	time_t tiempoFin;
	time(&tiempoFin);
	double tiempoTranscurrido;

	tiempoTranscurrido = difftime(tiempoFin, tiempoInicioInvencible);
	tiempoTranscurrido = fabs(tiempoTranscurrido);

	if (tiempoTranscurrido < duracionInvencibilidad)
	{
		return true;
	}
	return false;
}

bool Personaje::agarroBonusInvencible()
{
	return esInvencible;
}

void Personaje::serInmortalODejarDeSerlo()
{
	if (esInmortal){
		cout << "[MODO INMORTAL] Desactivado.\n";
		esInmortal = false;
	}
	else{
		cout << "[MODO INMORTAL] Activado.\n";
		esInmortal = true;
	}
}
int Personaje::getEquipo(){

	return this->grupo;

}
void Personaje::atacar(){
	if(!this->ataque){
		this->ataque = true;
		//this->cargaAtaque = true;
		time(&tiempoDeAtaque);
		//dejarDeEstarQuietoAtaque();
		dejarDeEstarQuieto();
		//animacionActual = &animacionSaltarIzq;

		//this->velocidadX = 2*personajeVelocidad;
		//animacionActual = &animacionCorrerDer;

		switch (orientacion)
		{
			case IZQUIERDA:
				animacionActual = &animacionAtaqueIzq;
				this->velocidadX = -2*personajeVelocidad;

				break;
			case DERECHA:
				animacionActual = &animacionAtaqueDer;
				this->velocidadX = 2*personajeVelocidad;
				break;
		}
		animacionActual->comenzar();
	}
}
bool Personaje::getAtaque(){
	return this->ataque;
}
/*void Personaje::ataqueMover(){
	this->cargaAtaque = false;
}
void Personaje::inicializarTiempoAtaque(){
	time(&tiempoDeAtaque);
	this->cargaAtaque = false;
}*/
bool Personaje::sigueAtaque()
{
	time_t tiempoFin;
	time(&tiempoFin);
	double tiempoTranscurrido;

	tiempoTranscurrido = difftime(tiempoFin, tiempoDeAtaque);
	tiempoTranscurrido = fabs(tiempoTranscurrido);
	//cout<<"valor de hora: "<<tiempoTranscurrido<<endl;
	if (tiempoTranscurrido < DURACION_ATAQUE)
	{
		return true;
	}
	return false;
}
void Personaje::dejarDeAtacar(){
	this->ataque = false;
}

void Personaje::estarHerido(bool herida)
{
	herido = herida;
}

bool Personaje::estaHerido()
{
	return herido;
}

bool Personaje::sigueEstandoHerido()
{
	time_t tiempoFin;
	time(&tiempoFin);
	double tiempoTranscurrido;

	tiempoTranscurrido = difftime(tiempoFin, tiempoInicioHerida);
	tiempoTranscurrido = fabs(tiempoTranscurrido);

	if (tiempoTranscurrido < DURACION_HERIDA)
	{
		return true;
	}
	return false;
}

void Personaje::titilarPorHerida(ControlServidor *control)
{
	herido = true;
	time(&tiempoInicioHerida);
	std::string mensaje = Util::intToString(id)
		+ "x" + Util::intToStringConPadding(posicionX)
		+ "y" + Util::intToStringConPadding(posicionY)
		+ ANIMACION_TITILAR + PADDING;
	control->enviarATodos(mensaje);
}
