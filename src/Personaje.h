#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <SDL2/SDL_image.h>
#include "Textura.h"
#include "Animacion.h"
#include "ConexCliente.h"
#include "HiloEnviarCliente.h"
#include "Definiciones.h"
#include <time.h>
#include "Puntos.h"

#define GRAVEDAD 9
#define IMAGEN_POR_DEFECTO "images/sonicSprite.png"
#define REGULADOR_ALTURA_SALTO 0.05 //Regula la altura del salto (Es como un "promedio" de tiempoDeJuego)

class Puntaje;
class ControlServidor;

class Personaje
{
	public:
		enum Orientacion {IZQUIERDA, DERECHA};

	private:

		Textura *texturaSonic;
		Textura *texturaCongelado;
		Textura *texturaPuntaje;
		Textura *texturaEscudo;
		Textura *texturaInvencible;

		int id;
		int personajeAncho;
		int personajeAlto;
		int personajeVelocidad;
		int personajeAceleracion;
		int posicionX, posicionY;
		int velocidadX, velocidadY;
		int grupo;

		Animacion animacionQuietoDer;
		Animacion animacionCaminarDer;
		Animacion animacionCorrerDer;
		Animacion animacionSaltarDer;
		Animacion animacionQuietoIzq;
		Animacion animacionCaminarIzq;
		Animacion animacionCorrerIzq;
		Animacion animacionSaltarIzq;
		Animacion animacionCongelado;

		Animacion *animacionActual;

		Animacion animacionEscudo;
		Animacion animacionInvencible;

		Animacion *animacionBonus; //Se suponerpone

		Orientacion orientacion;
		Puntaje *puntaje;
		Puntos *puntos;

		bool saltando;
		bool corriendo;
		bool estaQuieto;
		bool congelado;
		bool puedeIrDerecha;
		bool puedeIrIzquierda;
		bool tieneEscudo;
		bool esInvencible; //Bonus. Mata a los enemigos que toque.
		bool esInmortal; //No pierde la ultima vida pero pierde vidas y anillos.
        bool colisionando;
        bool resbalando;
        bool estaVivo;
		time_t tiempoInicioInvencible;
		int duracionInvencibilidad;
		Logger *log;

		void animarSalto();
		void cargarSpriteSonic();
		void dejarDeEstarQuieto();

		std::string intToStringConPadding(int number);

    public:

		Personaje(int id, int velocidad,SDL_Renderer *render, int altoEscenario, Logger *log);
		virtual ~Personaje();

		void mover(SDL_Rect *limites, float tiempoDeJuego);

		void render(int camX, int camY);
		std::string intToString(int number);
		void posicionarseEn(int x, int y);
		void posicionarseConAnimacion(int x, int y, std::string animacion, int indiceAnimacion);
		int getPosicionX();
		int getPosicionY();
		int getVelocidadX();
		int getAlto();
		int getAncho();
		int getId();
		std::string getNombreAnimacion();
		std::string getEstadoAnimacion();

		void saltar();
		void dejarDeSaltar();
		void correr(bool estaCorriendo);
		void resbalar(Orientacion haciaDonde);
		void rebotar();
		void herir(ControlServidor *control);

		void irArriba();
		void irAbajo();
		void irIzquierda();
		void irDerecha();
		void parar();

		void pararPorColision(SDL_Rect rectangulo);
		void reanudarLuegoDeColision();
		void detener();

		void congelar();
		void descongelar();

		bool bloqueaCamara(SDL_Rect *limites);
		bool bloqueaCamaraADerecha(SDL_Rect *limites);
		bool bloqueaCamaraAIzquierda(SDL_Rect *limites);
		bool estaCongelado();
		bool estaParado();
		bool estaAtacando();
		bool sigueVivo();
		void dejarDeEstarVivo();

		SDL_Rect obtenerLimites();

		void enviarAServer(HiloEnviarCliente *hiloEnviar, std::string mensaje);
		std::string obtenerMensajeEstado();
		std::string obtenerMensajeEstadoBonus();
		Puntaje* getPuntaje();
		void setPuntaje(Puntaje* puntaje);
		Puntos* getPuntos();
		void setPuntos(Puntos*);
		void setGrupo(int grupo);
		void aumentarCantidadAnillos(int cantidad);
		void ponerseEscudo();
		void quitarseEscudo();
		void serInvencible();
		void serInvencible(int segundos);
		void dejarDeSerInvencible();
		bool sigueSiendoInvencible();
		bool agarroBonusInvencible();
		void serInmortalODejarDeSerlo();
};

#endif
