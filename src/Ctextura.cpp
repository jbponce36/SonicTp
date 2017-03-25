#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Ctextura.h"
#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

Ctextura::Ctextura()
{
	this->miTextura = NULL;
	this->texturaLargo = 0;
	this->texturaAncho = 0;
}

Ctextura::~Ctextura()
{
	free();
}

bool Ctextura::cargarImagen( std::string path , SDL_Renderer *render )
{
	//elimina la textura anterior si no apunta a null
	free();

	SDL_Texture* nuevaTextura = NULL;

	//carga la imagen
	SDL_Surface* imagenCargadaSurface = IMG_Load( path.c_str() );
	if( imagenCargadaSurface == NULL )
	{
		printf( "error en cargar la imagen (IMG_Load): %s\n", IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( imagenCargadaSurface, SDL_TRUE, SDL_MapRGB( imagenCargadaSurface->format, 0, 0xFF, 0xFF ) );

        nuevaTextura = SDL_CreateTextureFromSurface( render, imagenCargadaSurface );
		if( nuevaTextura == NULL )
		{
			printf( "error en la carga de la textura: %s\n", SDL_GetError() );
		}
		else
		{
			this->texturaLargo = imagenCargadaSurface->w;
			this->texturaAncho = imagenCargadaSurface->h;
		}

		SDL_FreeSurface( imagenCargadaSurface );
	}


	this->miTextura = nuevaTextura;
	return this->miTextura != NULL;
}

#ifdef _SDL_TTF_H
bool Ctextura::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{

	free();


	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{

        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

void Ctextura::free()
{

	if( miTextura != NULL )
	{
		SDL_DestroyTexture( miTextura );
		miTextura = NULL;
		this->texturaLargo = 0;
		this->texturaAncho = 0;
	}
}

void Ctextura::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( this->miTextura, red, green, blue );
}

void Ctextura::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( miTextura, blending );
}

void Ctextura::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( miTextura, alpha );
}

void Ctextura::render( int x, int y, SDL_Renderer *render, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{

	SDL_Rect renderQuad = { x, y, this->texturaLargo, this->texturaAncho};

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(render, this->miTextura, clip, &renderQuad, angle, center, flip );
}

int Ctextura::getLargo()
{
	return this->texturaLargo;
}

int Ctextura::getAncho()
{
	return this->texturaAncho;
}
SDL_Texture *Ctextura::getTexture(){
	return this->miTextura;
}
