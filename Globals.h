#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>

namespace Globals {
	const int FPS_CAP = 90;
	const int COMMAND_PANEL_LINE_WRAP = 200;
	const int TASK_MANAGER_LINE_WRAP = 370;
}

enum WINDOW {
	SCREEN_WIDTH = 1200,
	SCREEN_HEIGHT = 900
};

enum CONTROLS {
	QUIT = 1,
	DEBUG_MODE,
	CAMERA_MODE,
	LEFT_CLICK,
	RIGHT_CLICK,
	CPANEL,
	SHOW_VERSION,
	SHOW_DATE,
	SHOW_HELP,
	SHOW_DIRECTORY
};

enum PCBi {
	APPLICATION = 1,
	SYSTEM_TYPE,
	PROCESS_STATE_RUNNING,
	PROCESS_STATE_READY,
	PROCESS_STATE_BLOCKED,
	PROCESS_STATE_SUSPENDED,
	PROCESS_STATE_NOT_SUSPENDED,
	PROCESS_STATE_COMPLETED
};

enum Commands {
	CREATE_PCB = 1,
	DELETE_PCB,
	BLOCK,
	UNBLOCK,
	SUSPEND,
	RESUME,
	SET_PRIORITY,
	SHOW_PCB,
	SHOW_ALL,
	SHOW_READY,
	SHOW_BLOCKED,
	HIDE_TASK_MANAGER,
	READ_FROM_FILE,
	SHOW_RUNNING,
	START_PROCESSES,
	SHOW_COMPLETED,
	CLEAR_COMPLETED
};

#endif