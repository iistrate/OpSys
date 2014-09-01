#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>


#include "Image.h"

class TextureManager {
private:
	SDL_Rect m_dstRect;
	SDL_Rect m_srcRect;
	SDL_Texture* m_pTexture;

	//font
	SDL_Surface* m_pTextSurface;
	TTF_Font* m_pfont;
	const char *m_pcstr;
	std::string m_scommand;
	int m_ifontWidth;

	Uint32 FPS;

	//camera position
	int m_icamX;
	int m_icamY;
	int m_icamSpeed;

	//level dimension
	int m_ilevelWidth;
	int m_ilevelHeight;

	//screen dimension
	int m_iscreenWidth;
	int m_iscreenHeight;

public:
	TextureManager();
	~TextureManager();

	int getFontWidth();

	void draw(SDL_Renderer* f_prenderer, std::vector < Image* > f_Images, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawImage(SDL_Renderer* f_prenderer, Image* f_Image);
	void drawText(SDL_Renderer* f_prenderer, std::string s, int x, int y, int wrap = 305, bool showCursor = false);
	void sortByLayer(std::vector < Image* > f_Images);

	void initFont(int);

	void setCamX(int);
	void setCamY(int);
};
#endif // end TextureManager.h