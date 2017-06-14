#ifndef JEFE_H_
#define JEFE_H_

#include "Enemigo.h"
#include "Bola.h"
#define CANTIDAD_VIDAS_JEFE 5

class Jefe: public Enemigo {
private:
	std::vector<SDL_Rect> sprites;
	Textura *textura;
	float velocidad;
	int maximoX;
	int minimoX;
	float velocidadBolaX;
	float velocidadBolaY;
	int numeroMaximoSprites;
	int contadorSprite;
	int vidas;
	bool herido;
	Bola *bola;
	Uint32 tiempo;
	time_t duracionHerido;

public:
	Jefe(int x, int y);
	void setBola(Bola *bol);
	void calcularNumeroDeSprite();
	void actualizarPosicion();
	void actualizarPosicionBola();
	SDL_Rect obtenerDimensiones();
	void restarVida();


	~Jefe();
	Jefe(std::string mensaje, std::string tipo, VistaSDL *vista);
	void cargarSprites(int x, int y, int cantidad);
	void renderizar(int camaraX, int camaraY);
};

 /* namespace std */

#endif /* JEFE_H_ */
