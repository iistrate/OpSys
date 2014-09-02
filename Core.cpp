#include "Core.h"

Core::Core() :m_brunning(false), m_pRenderer(0), m_pWindow(0), m_fps(0), 
m_fpsCap(Globals::FPS_CAP), m_turn(0), m_bdebugMode(false), m_bcameraMode(false), m_bexecute(false),
m_commandCursor(0), m_bshowcPanel(false), m_bcreatedPanel(false), m_bshowDate(false), m_bshowHelp(false), m_bshowVersion(false) {
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
	
	time_t tm;
	std::string stime;

	//create panel
	GUI* Panel = new GUI(300, 400, 500, 300);
	//get images
	Panel->getImages(m_Images_CMD);

	do {
		//events
		uinput = Ui.getCommand();
		//written
		//get command from input
		m_scommand = Ui.getStringCommand();
		//send string to python and get sanitized string and list of commands as a vector of ints
		//m_scommand = Sparser.parseString(m_icommand, m_scommand);
		Ui.setStringCommand(m_scommand);

		switch (uinput) {
			case CONTROLS::QUIT:
				quit();
				break;
			case CONTROLS::DEBUG_MODE:
				m_bdebugMode = m_bdebugMode == false ? true : false;
				break;
			case CONTROLS::RIGHT_CLICK:
				//check if panel is opened
				if (m_bshowcPanel) {
					//check if it is in the panel are
					if (Ui.getMouseX() >= 480 && Ui.getMouseX() <= 730) {
						if (Ui.getMouseY() >= 290 && Ui.getMouseY() <= 570) {
							//send x and y to panel
							switch (Panel->clicked(Ui.getMouseX(), Ui.getMouseY())) {
							case SHOW_VERSION:
								m_bshowVersion = m_bshowVersion == false ? true : false;
								break;
							case SHOW_DATE:
								m_bshowDate = m_bshowDate == false ? true : false;
								break;
							case SHOW_HELP:
								m_bshowHelp = m_bshowHelp == false ? true : false;
								break;
							case DEBUG_MODE:
								m_bdebugMode = m_bdebugMode == false ? true : false;
								break;
							case SHOW_DIRECTORY:
								break;
							case QUIT:
								quit();
								break;
							}
							//std::cout << "clicked panel area" << std::endl;  //debug
						}
					}
				}
				break;
			case CONTROLS::CPANEL:
				m_bshowcPanel = m_bshowcPanel == false ? true : false;
				break;
			case CONTROLS::CAMERA_MODE:
				m_bshowcPanel = m_bshowcPanel == false ? true : false;
				break;
		}

		time(&tm);
		stime = getTime(tm);

		//clear window
		SDL_RenderClear(m_pRenderer);

		//set color bg to white
		SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

		//show images
		Tmanager.draw(m_pRenderer, m_Images);
		//show panel
		m_bshowcPanel = true;
		if (m_bshowcPanel) {
			Tmanager.draw(m_pRenderer, m_Images_CMD);
			Tmanager.drawText(m_pRenderer, "Display Version", 490, 330);
			Tmanager.drawText(m_pRenderer, "Display Date", 490, 360);
			Tmanager.drawText(m_pRenderer, "Display Help", 490, 390);
			Tmanager.drawText(m_pRenderer, "Directory Explorer", 490, 420);
			Tmanager.drawText(m_pRenderer, "Debug Mode", 490, 450);
			Tmanager.drawText(m_pRenderer, "Quit", 490, 480);
			Tmanager.drawText(m_pRenderer, "Command: " + m_scommand, 490, 520, Globals::COMMAND_PANEL_LINE_WRAP, true);
		}

		//draw text
		if (m_bshowVersion) {
			Tmanager.drawText(m_pRenderer, "E1 200 ver: Pawn Chess", 20, 30);
		}
		if (m_bshowDate) {
			Tmanager.drawText(m_pRenderer, stime, 20, 10);
		}
		if (m_bshowHelp) {
			Tmanager.drawText(m_pRenderer, stime, 20, 10);
		}

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

std::string Core::getTime(const time_t time) {

	struct tm ts;
	char szBuffer[80] = "DD-MM-YY"; //  HH:MM:SS

	errno_t err = localtime_s(&ts, &time);

	if (err)
	{
	}
	else
	{
		// Format the time
		strftime(szBuffer, sizeof(szBuffer), "Date is: %d %b %Y", &ts); //  %X%p
	}
	return szBuffer;
}
Core::~Core() {
	//sdl cleanup; font cleanup handled in tmanager
	SDL_Quit();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;
}
