#include "Core.h"

Core::Core() :m_brunning(false), m_pRenderer(0), m_pWindow(0), m_fps(0), 
m_fpsCap(Globals::FPS_CAP), m_turn(0), m_bdebugMode(false), m_bcameraMode(false), m_bexecute(false),
m_commandCursor(0), m_bcontrolPanel(false) {
}

void Core::init(const char* title, int x, int y, int w, int h, int flags) {
	//start loop
	m_brunning = true;

	//initialize sdl
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags);

		if (m_pWindow) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
		}
		else {
			std::cout << "Window failed to load" << std::endl;
		}
	}
	else {
		std::cout << "SDL failed to initialize" << std::endl;
	}
}

void Core::run() {
	init("the E1 2000 Operating System", 50, 50, WINDOW::SCREEN_WIDTH, WINDOW::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	int uinput;
	
	do {
		uinput = Ui.getCommand();

		std::cout << uinput << std::endl;

		switch (uinput) {
		case CONTROLS::QUIT:
			quit();
			break;
		case CONTROLS::DEBUG_MODE:
			m_bdebugMode = m_bdebugMode == true ? false : true;
			break;
		case CONTROLS::RIGHT_CLICK:
			m_bcontrolPanel = true;
			break;
		}

		//Conways->getImages(m_Images);

		//clear window
		SDL_RenderClear(m_pRenderer);

		//set color bg to white
		SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

		//draw images
		//Tmanager.draw(m_pRenderer, m_Images);
		Tmanager.drawText(m_pRenderer, "E1 200 ver: Pawn Chess", 20, 10);


		//Debug mode
		if (m_bdebugMode) {
			/*
			text
			*/
			//show command
			Tmanager.drawText(m_pRenderer, "Command: " + std::to_string(uinput), 550, 10);
			//show turn
			Tmanager.drawText(m_pRenderer, "TURN: " + std::to_string(m_turn) + "  FPS:" + std::to_string(m_fpsCap), 1000, 10);
			//show mouse position
			Tmanager.drawText(m_pRenderer, "X: " + std::to_string(Ui.getMouseX()) + " Y: " + std::to_string(Ui.getMouseY()), 570, 870);
		}


		SDL_RenderPresent(m_pRenderer);
		//cap fps
		fpsCap();
		//increase game turn
		m_turn++;
	} while (m_brunning);
}

void Core::fpsCap() {
	//time in seconds
	m_fps = SDL_GetTicks() / 1000;
	if (m_fps < 1000 / m_fpsCap) {
		//fps per seconds - time difference from when the loop started till the end in seconds
		SDL_Delay((1000 / m_fpsCap) - (m_fps / 1000));
	}
}
void Core::quit() {
	m_brunning = false;
}
Core::~Core() {
	//sdl cleanup; font cleanup handled in tmanager
	SDL_Quit();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;
}