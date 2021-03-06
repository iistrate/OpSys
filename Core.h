#ifndef CORE_H
#define CORE_H

//libraries
#include <ctime>
#include <string>
#include <cassert>
#include <random>
#include <stdlib.h>

//user defined headers
#include "TextureManager.h"
#include "Globals.h"
#include "UserInput.h"
#include "GUI.h"
#include "StringParser.h"
#include "Scheduler.h"
#include "Memory.h"


using std::vector;
using std::cout;
using std::string;
using std::endl;


class Core {
private:
	//setup vars
	int m_turn;
	int m_commandCursor;
	int m_runType;
	int m_timeQuantum;
	int m_batchTime;
	int m_mlfq[3];
	int m_tickets;
	int m_freeMemory;

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

	bool m_createdPanel;



	//fps thingy
	Uint32 m_fps;
	Uint32 m_fpsCap;

	//holds visual string command for sdl
	string m_scommand;
	//holds translated commands
	vector < int > m_icommand;
	//holds parameter commands
	vector < string > m_parameters;
	//hold error codes
	vector < int > m_errorCodes;
	//holds task manager string
	string m_TaskManager;
	//hold forced commands
	vector < int > m_isystemCommands;

	//composition
	TextureManager Tmanager;
	UserInput Ui;
	GUI* Panel;
	StringParser* Parser;
	Memory* m_Memory;
		
	//process queues
	PCBQueue* m_Ready;
	PCBQueue* m_Blocked;
	PCBQueue* m_Completed;

	//image sets
	vector < Image* > m_Images;
	vector < Image* > m_Images_CMD;
	vector < Image* > m_Images_TM;

	enum ErrorCodes {
		INVALID_SYNTAX = 1,
		OBJ_NOT_A_STRING,
		OBJ_NOT_AN_INT,
		INT_OUT_OF_RANGE
	};

public:
	Core::Core() :m_running(false), m_pRenderer(0), m_pWindow(0), m_fps(0),
		m_fpsCap(Globals::FPS_CAP), m_turn(0), m_debugMode(false), m_cameraMode(false), m_execute(false),
		m_commandCursor(0), m_showcPanel(false), m_createdPanel(false), m_showDate(false), m_showHelp(false),
		m_showVersion(false), m_showTM(false), m_batchTime(0), m_runType(0), m_freeMemory(1024) {}

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
	string getTime(const time_t time);

	//list dir
	string listDir();

	//add system commands to user command
	void addSystem(void);

	//run pcbs; return total time
	int runPrograms();
};

#endif