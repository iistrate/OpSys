#ifndef CORE_H
#define CORE_H

#include "TextureManager.h"
#include "Globals.h"

class Core {
private:
	//setup vars
	bool m_brunning;

	//SDL vars
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

public:
	Core();
	//runs command loop
	void run();
	//inits vars and sdl
	void init(const char* title, int x, int y, int w, int h, int flags);
};

#endif