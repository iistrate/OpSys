#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals {
	const int FPS_CAP = 30;
	const int COMMAND_PANEL_LINE_WRAP = 200;
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
	CPANEL
};

#endif