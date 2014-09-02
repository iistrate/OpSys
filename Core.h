#ifndef CORE_H
#define CORE_H

#include <ctime>
#include <string>

#include "TextureManager.h"
#include "Globals.h"
#include "UserInput.h"
#include "GUI.h"


class Core {
private:
	//setup vars
	int m_turn;
	int m_commandCursor;
	std::vector < int > m_icommands;

	//SDL vars
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	//switches
	bool m_bdebugMode;
	bool m_bexecute;
	bool m_brunning;
	bool m_bcameraMode;
	bool m_bcontrolPanel;
	bool m_bcreatedPanel;

	//fps thingy
	Uint32 m_fps;
	Uint32 m_fpsCap;

	//holds string command
	std::string m_scommand;
	//holds translated commands
	std::vector < int > m_icommand;

	//composition
	TextureManager Tmanager;
	UserInput Ui;
	GUI* Panel;

	//image sets
	std::vector < Image* > m_Images;
	std::vector < Image* > m_Images_CMD;

public:
	Core();
	//handles sdl vars
	~Core();

	//runs command loop
	void run();
	//inits vars and sdl
	void init(const char* title, int x, int y, int w, int h, int flags);
	//quit game loop
	void quit();
	//fps
	void fpsCap();
	//get time
	std::string getTime(const time_t time);
};

#endif