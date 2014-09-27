#ifndef CORE_H
#define CORE_H

//libraries
#include <ctime>
#include <string>
#include <cassert>
//user defined headers
#include "TextureManager.h"
#include "Globals.h"
#include "UserInput.h"
#include "GUI.h"
#include "PCBQueue.h"
#include "StringParser.h"


class Core {
private:
	//setup vars
	int m_turn;
	int m_commandCursor;

	//SDL vars
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	//switches
	bool m_debugMode;
	bool m_execute;
	bool m_running;
	bool m_cameraMode;
	bool m_showcPanel;
	bool m_showVersion;
	bool m_showDate;
	bool m_showHelp;
	bool m_showDir;
	bool m_showTM;

	bool m_bcreatedPanel;



	//fps thingy
	Uint32 m_fps;
	Uint32 m_fpsCap;

	//holds visual string command for sdl
	std::string m_scommand;
	//holds translated commands
	std::vector < int > m_icommand;
	//holds parameter commands
	std::vector < std::string > m_parameters;
	//hold error codes
	std::vector < int > m_errorCodes;

	//composition
	TextureManager Tmanager;
	UserInput Ui;
	GUI* Panel;
	StringParser* Parser;
	//process queues
	PCBQueue* Ready;
	PCBQueue* Blocked;

	//image sets
	std::vector < Image* > m_Images;
	std::vector < Image* > m_Images_CMD;
	std::vector < Image* > m_Images_TM;

	enum ErrorCodes {
		INVALID_SYNTAX,
	};

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

	//list dir
	std::string listDir();
};

#endif