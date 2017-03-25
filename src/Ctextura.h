#include <iostream>
class Ctextura{
	public:
	Ctextura();
		~Ctextura();

		//carga la imagen
		bool cargarImagen( std::string path , SDL_Renderer *render);

		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//elimina la textura
		void free();


		void setColor( Uint8 red, Uint8 green, Uint8 blue );


		void setBlendMode( SDL_BlendMode blending );


		void setAlpha( Uint8 alpha );


		void render( int x, int y, SDL_Renderer *render, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getLargo();
		int getAncho();
		SDL_Texture *getTexture();

	private:
		SDL_Texture* miTextura;

		//dimensiones
		int texturaLargo;
		int texturaAncho;
};
