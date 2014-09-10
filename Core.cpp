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

	//create process queues
	Ready = new PCBQueue(true);
	Blocked = new PCBQueue(false);


	//create panel
	GUI* Panel = new GUI(300, 400, 500, 300);
	//get images
	Panel->getImages(m_Images_CMD);
	std::string directory = listDir();

	StringParser* Parser = new StringParser;
	Parser->init();

	do {
		//events
		uinput = Ui.getCommand();
		//written
		//get command from input
		m_scommand = Ui.getStringCommand();
		//send string to python and get sanitized string and list of commands as a vector of ints
		m_scommand = Parser->parseString(m_icommand, m_scommand);
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
								m_bshowDir = m_bshowDir == false ? true : false;
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
		Tmanager.drawText(m_pRenderer, "Howdy, welcome to the E1 2000 please press right ctrl for menu Thanks!", 470, 210);

		//show panel
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
			Tmanager.drawText(m_pRenderer, "E1 2000 ver: Pawn Chess", 20, 30);
		}
		if (m_bshowDate) {
			Tmanager.drawText(m_pRenderer, stime, 20, 10);
		}
		if (m_bshowHelp) {
			Tmanager.drawText(m_pRenderer, "Help: Howdy murricans; please press version for op sys version, date for showing date, help for showing this text, directory for showing the directory and quit for quit; please note that you can also add commands to the command line. Thanks!", 20, 50);
		}
		if (m_bshowDir) {
			Tmanager.drawText(m_pRenderer, directory, 1000, 230);
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


			//testing PCB
			PCB* test = new PCB();
			test->setClass(PCBi::APPLICATION);
			test->setName("Some name");
			test->setPriority(120);
			test->setState(PCBi::PROCESS_STATE_BLOCKED);

			std::cout << "PCB Class: " << test->getClass() << std::endl;
			std::cout << "PCB Name: " << test->getName() << std::endl;
			std::cout << "PCB State: " << test->getState() << std::endl;
			std::cout << "PCB Priority: " << test->getPriority() << std::endl;

			//testing setup in queue
			std::cout << "name from setupPCB " << Ready->setupPCB("name", 120, APPLICATION)->getName();
			//testing insertion and finding
			Ready->insertPCB(Ready->setupPCB("my first pcb", 120, APPLICATION));
//			Ready->removePCB(Ready->findPCB("my first pcb"));
			std::cout << "Node size is: " << Ready->getPCBCount() << std::endl;
			std::cout << "Find pcb by name; getting priority: " << Ready->findPCB("my first pcb")->getPriority() << std::endl;
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
std::string Core::listDir() {
	//setup 
	//Py Objects
	PyObject *m_POname, *m_POmodule, *m_POfunctionName, *m_POvalues, *m_POstring, *m_POlist;
	//gil state
	PyGILState_STATE m_gstate;

	//begin
	Py_Initialize();
	//init threads
	if (!PyEval_ThreadsInitialized()) {
		PyEval_InitThreads();
	}
	//on init lock gil state
	m_gstate = PyGILState_Ensure();

	//module name
	const char module[] = "ListDir";

	//build c string to py object string
	m_POname = Py_BuildValue("s", module);
	//load module into py object
	m_POmodule = PyImport_Import(m_POname);

	if (Py_IsInitialized) {
		//if module is loaded
		if (m_POmodule) {
			//load function
			m_POfunctionName = PyObject_GetAttrString(m_POmodule, "listDir");
		}
		//if function exists and is callable
		if (m_POfunctionName && PyCallable_Check(m_POfunctionName)) {
			m_POvalues = PyObject_CallFunction(m_POfunctionName, NULL);
		}
		m_POstring = m_POvalues;
	}
	Py_Finalize();
	//return parsed string
	return PyUnicode_AsUTF8(m_POstring);
}