#include "Core.h"


void Core::init(const char* title, int x, int y, int w, int h, int flags) {
	//start loop
	m_running = true;

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
			cout << "Window failed to load" << endl;
		}
	}
	else {
		cout << "SDL failed to initialize" << endl;
	}
}

void Core::run() {
	init("the E1 2000 Operating System", 50, 50, WINDOW::SCREEN_WIDTH, WINDOW::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	//user input
	int uinput;
	
	//time 
	time_t tm;
	string stime;
	//directory listing
	string directory = listDir();



	//create process queues
	m_Ready = new PCBQueue(true);
	m_Blocked = new PCBQueue(false);
	m_Completed = new PCBQueue(false);


	//create panel
	GUI* Panel = new GUI(300, 400, 500, 300);
	GUI* TaskManager = new GUI(400, 650, 0, 0);
	//get images for panels
	//command panel
	Panel->getImages(m_Images_CMD);
	//task manager
	TaskManager->getImages(m_Images_TM);
	//Scheduler
	Scheduler* E1Scheduler = new Scheduler(*m_Ready, *m_Blocked);

	//initialize python parser
	StringParser* Parser = new StringParser;
	Parser->init();

	do {
		//events, mouse or keyboard
		uinput = Ui.getCommand();

		//string commands
		//get command from input
		m_scommand = Ui.getStringCommand();
		//send string to python and get sanitized string, list of commands, 
		//list of parameters and a list of error codes as a vector of ints
		m_scommand = Parser->parseString(m_icommand, m_scommand, m_parameters, m_errorCodes);
		//reconsider removal used only for special chars
		Ui.setStringCommand(m_scommand);
		//end reconsider



		//add System commands
		if (!m_isystemCommands.empty()) {
			addSystem();
		}
		//if no error codes
		if (m_errorCodes.size() == 0) {
			//user written commands
			while (m_icommand.size() > 0) {
				//switch on first command
				switch (m_icommand.front()) {
				case Commands::CREATE_PCB:
					if (m_parameters.size() == 3) {
						m_Ready->insertPCBatEnd(m_Ready->setupPCB(m_parameters[0], atoi(m_parameters[1].c_str()), 
							atoi(m_parameters[2].c_str()), 0, 0, 0, 0));
					}
					break;
				case Commands::DELETE_PCB:
					if (m_parameters.size() == 1) {
						PCB* temp = m_Ready->findPCB(m_parameters[0]);
						if (temp) {
							m_Ready->removePCB(temp);
						}
					}
					break;
				case Commands::BLOCK:
					if (m_parameters.size() == 1) {
						PCB* temp = m_Ready->findPCB(m_parameters[0]);
						if (temp) {
							temp->setState(PROCESS_STATE_BLOCKED);
							m_Ready->removePCB(temp);
							m_Blocked->insertPCBatEnd(temp);
						}
					}
					break;
				case Commands::UNBLOCK:
					if (m_parameters.size() == 1) {
						PCB* temp = m_Ready->findPCB(m_parameters[0]);
						if (temp) {
							temp->setState(PROCESS_STATE_READY);
							m_Blocked->removePCB(temp);
							m_Ready->insertPCBatEnd(temp);
						}
					}
					break;
				case Commands::SUSPEND:
					if (m_parameters.size() == 1) {
						PCB* temp = m_Ready->findPCB(m_parameters[0]);
						if (temp) {
							temp->setState(PROCESS_STATE_SUSPENDED);
						}
					}
					break;
				case Commands::RESUME:
					if (m_parameters.size() == 1) {
						PCB* temp = m_Ready->findPCB(m_parameters[0]);
						if (temp) {
							temp->setState(PROCESS_STATE_NOT_SUSPENDED);
						}
					}
					break;
				case Commands::SET_PRIORITY:
					if (m_parameters.size() == 2) {
						PCB* temp;
						//look in ready queue
						temp = m_Ready->findPCB(m_parameters[0]) != NULL ? m_Ready->findPCB(m_parameters[0]) : m_Blocked->findPCB(m_parameters[0]);
						if (temp) {
							temp->setPriority(atoi(m_parameters[1].c_str()));
						}
					}
					break;
				case Commands::SHOW_PCB:
					m_TaskManager = "Individual PCB:\nN: Prty: Cl: St: Mem: ExecTime: ArrTime: CPU: \n";
					if (m_parameters.size() == 1) {
						PCB* temp = m_Ready->findPCB(m_parameters[0]);
						if (temp) {
							m_showTM = true;
							//build string
							m_TaskManager += temp->getName() + " "
								+ std::to_string(temp->getPriority()) + " "
								+ std::to_string(temp->getClass()) + " "
								+ std::to_string(temp->getState()) + " "
								+ std::to_string(temp->getMemorySize()) + " "
								+ std::to_string(temp->getExecutionTime()) + " "
								+ std::to_string(temp->getTimeOfArrival()) + " "
								+ std::to_string(temp->getCPU())
								+ "\n";
						}
					}
					break;
				case Commands::SHOW_ALL:
					m_TaskManager = "Show all PCB's\nN: Prty: Cl: St: Mem: ExecTime: ArrTime: CPU: \n";
					m_showTM = true;
					PCB* temp;
					//ready
					for (int i = 0; i < m_Ready->getPCBCount(); i++) {
						temp = m_Ready->getPCBatIndex(i);
						if (temp) {
							m_TaskManager += temp->getName() + " "
								+ std::to_string(temp->getPriority()) + " "
								+ std::to_string(temp->getClass()) + " "
								+ std::to_string(temp->getState()) + " "
								+ std::to_string(temp->getMemorySize()) + " "
								+ std::to_string(temp->getExecutionTime()) + " "
								+ std::to_string(temp->getTimeOfArrival()) + " "
								+ std::to_string(temp->getCPU())
								+ "\n";
						}
						temp = 0;
					}
					for (int i = 0; i < m_Blocked->getPCBCount(); i++) {
						temp = m_Blocked->getPCBatIndex(i);
						if (temp) {
							m_TaskManager += temp->getName() + " "
								+ std::to_string(temp->getPriority()) + " "
								+ std::to_string(temp->getClass()) + " "
								+ std::to_string(temp->getState()) + " "
								+ std::to_string(temp->getMemorySize()) + " "
								+ std::to_string(temp->getExecutionTime()) + " "
								+ std::to_string(temp->getTimeOfArrival()) + " "
								+ std::to_string(temp->getCPU())
								+ "\n";
						}
						temp = 0;
					}
					break;
				case Commands::SHOW_READY:
					m_TaskManager = "Show ready PCB's\nN: Prty: Cl: St: Mem: ExecTime: ArrTime: CPU: \n";
					m_showTM = true;
					//ready
					for (int i = 0; i < m_Ready->getPCBCount(); i++) {
						temp = m_Ready->getPCBatIndex(i);
						if (temp) {
							m_TaskManager += temp->getName() + " "
								+ std::to_string(temp->getPriority()) + " "
								+ std::to_string(temp->getClass()) + " "
								+ std::to_string(temp->getState()) + " "
								+ std::to_string(temp->getMemorySize()) + " "
								+ std::to_string(temp->getExecutionTime()) + " "
								+ std::to_string(temp->getTimeOfArrival()) + " "
								+ std::to_string(temp->getCPU())
								+ "\n";
						}
					}
					break;
				case Commands::SHOW_BLOCKED:
					m_TaskManager = "Show blocked PCB's\nN: Prty: Cl: St: Mem: ExecTime: ArrTime: CPU: \n";
					m_showTM = true;
					//blocked
					for (int i = 0; i < m_Blocked->getPCBCount(); i++) {
						temp = m_Blocked->getPCBatIndex(i);
						if (temp) {
							m_TaskManager = temp->getName() + " "
								+ std::to_string(temp->getPriority()) + " "
								+ std::to_string(temp->getClass()) + " "
								+ std::to_string(temp->getState()) + " "
								+ std::to_string(temp->getMemorySize()) + " "
								+ std::to_string(temp->getExecutionTime()) + " "
								+ std::to_string(temp->getTimeOfArrival()) + " "
								+ std::to_string(temp->getCPU())
								+ "\n";
						}
					}
					break;
				case Commands::SHOW_RUNNING:
					m_TaskManager = "Show running PCB's\nN: Prty: Cl: St: Mem: ExecTime: ArrTime: CPU: \n";
					m_showTM = true;
					//ready
					for (int i = 0; i < m_Ready->getPCBCount(); i++) {
						temp = m_Ready->getPCBatIndex(i);
						if (temp && temp->getState() == PCBi::PROCESS_STATE_RUNNING) {
							m_TaskManager += temp->getName() + " "
								+ std::to_string(temp->getPriority()) + " "
								+ std::to_string(temp->getClass()) + " "
								+ std::to_string(temp->getState()) + " "
								+ std::to_string(temp->getMemorySize()) + " "
								+ std::to_string(temp->getExecutionTime()) + " "
								+ std::to_string(temp->getTimeOfArrival()) + " "
								+ std::to_string(temp->getCPU())
								+ "\n";
						}
					}
					break;
				case Commands::HIDE_TASK_MANAGER:
					m_showTM = false;
					break;
				case Commands::SHORTEST_JOB_FIRST:
					if (m_parameters.size() > 0) {
						//from file to scheduler
						E1Scheduler->addPCBS(m_parameters[0], TIME_REMAINING);
						//show processes
						m_icommand.push_back(SHOW_READY);
						m_runType = SHORTEST_JOB_FIRST;
					}
					break;
				case Commands::PRE_EMPTIVE_SJF:
					if (m_parameters.size() > 0) {
						//from file to scheduler
						E1Scheduler->addPCBS(m_parameters[0], TIME_OF_ARRIVAL);
						//show processes
						m_icommand.push_back(SHOW_READY);
						m_runType = PRE_EMPTIVE_SJF;
					}
					break;
				case Commands::FIXED_PRIORITY_PRE_EMPTIVE:
					if (m_parameters.size() > 0) {
						//from file to scheduler
						E1Scheduler->addPCBS(m_parameters[0], TIME_OF_ARRIVAL);
						//show processes
						m_icommand.push_back(SHOW_READY);
						m_runType = FIXED_PRIORITY_PRE_EMPTIVE;
					}
					break;
				case Commands::FIRST_IN_FIRST_OUT:
					if (m_parameters.size() > 0) {
						//from file to scheduler
						E1Scheduler->addPCBS(m_parameters[0], TIME_OF_ARRIVAL);
						//show processes
						m_icommand.push_back(SHOW_READY);
						m_runType = FIRST_IN_FIRST_OUT;
					}
					break;
				case Commands::ROUND_ROBIN_SCHEDULLING:
					if (m_parameters.size() > 0) {
						//from file to scheduler
						E1Scheduler->addPCBS(m_parameters[0], TIME_OF_ARRIVAL);
						//show processes
						m_icommand.push_back(SHOW_READY);
						m_runType = ROUND_ROBIN_SCHEDULLING;
						m_timeQuantum = atoi(m_parameters[1].c_str());
					}
					break;
				case Commands::START_PROCESSES:
					for (int i = 0; i < m_Ready->getPCBCount(); i++) {
						temp = m_Ready->getPCBatIndex(i);
						if (temp) {
							temp->setState(PROCESS_STATE_RUNNING);
						}
						m_icommand.push_back(SHOW_RUNNING);
					}
					m_execute = true;
					break;
				case Commands::SHOW_COMPLETED:
					m_TaskManager = "Show Completed PCB's\nN: Prty: Cl: St: Mem: ExecTime: ArrTime: CPU: \n";
					m_showTM = true;
					//ready
					for (int i = 0; i < m_Completed->getPCBCount(); i++) {
						temp = m_Completed->getPCBatIndex(i);
						if (temp && temp->getState() == PCBi::PROCESS_STATE_COMPLETED) {
							m_TaskManager += temp->getName() + " "
								+ std::to_string(temp->getPriority()) + " "
								+ std::to_string(temp->getClass()) + " "
								+ std::to_string(temp->getState()) + " "
								+ std::to_string(temp->getMemorySize()) + " "
								+ std::to_string(temp->getExecutionTime()) + " "
								+ std::to_string(temp->getTimeOfArrival()) + " "
								+ std::to_string(temp->getCPU()) + "\n";
						}
					}
					if (m_Completed->getPCBCount()) {
						m_TaskManager += "\n\n\n Total time to completion: " + std::to_string(m_batchTime) + "\n" +
							" Average completion time: " + std::to_string(m_batchTime / m_Completed->getPCBCount());
					}
					break;
				case Commands::CLEAR_COMPLETED:
					m_Completed->clearQueue();
					m_batchTime = 0;
					m_isystemCommands.push_back(SHOW_COMPLETED);
					break;
				} //command switch
				//once we're done with the commands clear command queues 
				m_scommand.clear();
				m_parameters.clear();
				Ui.setStringCommand(m_scommand);
				//in fifo
				m_icommand.erase(m_icommand.begin());
			} //reading commands
		} //erorr codes
//test get count for all queues
		//cout << "Ready Queue: " << m_Ready->getPCBCount() << std::endl;
		//cout << "Blocked Queue: " << m_Blocked->getPCBCount() << std::endl;
		//cout << "Completed Queue: " << m_Completed->getPCBCount() << endl;
//end test
		//user predefined keys and visual buttons input
		switch (uinput) {
			case CONTROLS::QUIT:
				quit();
				break;
			case CONTROLS::DEBUG_MODE:
				m_debugMode = m_debugMode == false ? true : false;
				break;
			case CONTROLS::LEFT_CLICK:
				//check if panel is opened
				if (m_showcPanel) {
					//check if it is in the panel are
					if (Ui.getMouseX() >= 480 && Ui.getMouseX() <= 730) {
						if (Ui.getMouseY() >= 290 && Ui.getMouseY() <= 570) {
							//send x and y to panel
							switch (Panel->clicked(Ui.getMouseX(), Ui.getMouseY())) {
							case SHOW_VERSION:
								m_showVersion = m_showVersion == false ? true : false;
								break;
							case SHOW_DATE:
								m_showDate = m_showDate == false ? true : false;
								break;
							case SHOW_HELP:
								m_showHelp = m_showHelp == false ? true : false;
								break;
							case DEBUG_MODE:
								m_debugMode = m_debugMode == false ? true : false;
								break;
							case SHOW_DIRECTORY:
								m_showDir = m_showDir == false ? true : false;
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
				m_showcPanel = m_showcPanel == false ? true : false;
				break;
			case CONTROLS::CAMERA_MODE:
				m_showcPanel = m_showcPanel == false ? true : false;
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
		if (m_showcPanel) {
			Tmanager.draw(m_pRenderer, m_Images_CMD);
			Tmanager.drawText(m_pRenderer, "Display Version", 490, 330);
			Tmanager.drawText(m_pRenderer, "Display Date", 490, 360);
			Tmanager.drawText(m_pRenderer, "Display Help", 490, 390);
			Tmanager.drawText(m_pRenderer, "Directory Explorer", 490, 420);
			Tmanager.drawText(m_pRenderer, "Debug Mode", 490, 450);
			Tmanager.drawText(m_pRenderer, "Quit", 490, 480);
			Tmanager.drawText(m_pRenderer, "Command: " + m_scommand, 490, 520, Globals::COMMAND_PANEL_LINE_WRAP, true);
		}
		if (m_showTM) {
			Tmanager.draw(m_pRenderer, m_Images_TM);
			if (!m_TaskManager.empty()) {
				Tmanager.drawText(m_pRenderer, m_TaskManager, 20, 40, Globals::TASK_MANAGER_LINE_WRAP);
			}
		}

		//draw text
		if (m_showVersion) {
			Tmanager.drawText(m_pRenderer, "E1 2000 ver: Pawn Chess", 20, 30);
		}
		if (m_showDate) {
			Tmanager.drawText(m_pRenderer, stime, 20, 10);
		}
		if (m_showHelp) {
			Tmanager.drawText(m_pRenderer, "Help: Howdy please press version for op sys version, date for showing date, help for showing this text, directory for showing the directory and quit for quit; please note that you can also add commands to the command line. Thanks!", 20, 50);
		}
		if (m_showDir) {
			Tmanager.drawText(m_pRenderer, directory, 1000, 230);
		}

		//Debug mode
		if (m_debugMode) {
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

			cout << "PCB Class: " << test->getClass() << endl;
			cout << "PCB Name: " << test->getName() << endl;
			cout << "PCB State: " << test->getState() << endl;
			cout << "PCB Priority: " << test->getPriority() << endl;

			//testing setup in queue
			cout << "name from setupPCB " << m_Ready->setupPCB("tralala", 120, APPLICATION, 0, 0, 0, 0)->getName() << endl;
			//testing insertion and finding
			m_Ready->insertPCBatEnd(m_Ready->setupPCB("my first pcb", 120, APPLICATION, 0, 0, 0, 0));
			cout << "Find pcb by name; getting priority: " << m_Ready->findPCB("my first pcb")->getPriority() << endl;
			m_Ready->removePCB(m_Ready->findPCB("my first pcb"));
			cout << "Node size is: " << m_Ready->getPCBCount() << endl;
		}


		SDL_RenderPresent(m_pRenderer);
		//cap fps
		fpsCap();
		//increase game turn
		m_turn++;
		if (m_execute) {
			//run programs
			runPrograms();
		}
	} while (m_running);
}
//run pcbs return total completion time for all processes
int Core::runPrograms() {
	//time scale
	static int completionTime = 0;
	if (m_runType == SHORTEST_JOB_FIRST || m_runType == FIRST_IN_FIRST_OUT || m_runType == PRE_EMPTIVE_SJF
		|| m_runType == FIXED_PRIORITY_PRE_EMPTIVE) {
		//decrease arrival time on each iteration for all pcbs
		for (int i = 0; i < m_Ready->getPCBCount(); i++) {
			PCB* temp = m_Ready->getPCBatIndex(i);
			if (temp) {
				//only run the ones that are set to running
				if (temp->getState() == PCBi::PROCESS_STATE_RUNNING) {
					int arrivalTime = temp->getTimeOfArrival();
					if (arrivalTime > 0) {
						temp->setTimeOfArrival(--arrivalTime);
					}
				}
			}
		}
		//start running each job starting at the front once arrival time is 0
		if (m_Ready->getPCBCount()) {
			//execute on first; fifo sorted by arival time, sjf, fpps, and stcf sorted by execution time
			//in both cases we work on the first element
			PCB* first = m_Ready->getPCBatIndex(0);
			//if pre emptive shortest time to completion look at all jobs with arival 0 then see which has the fastest execution time and execute it
			if (m_runType == PRE_EMPTIVE_SJF) {
				int executionTime = first->getExecutionTime();
				for (int i = 0; i < m_Ready->getPCBCount(); i++) {
					PCB* compare = m_Ready->getPCBatIndex(i);
					if (compare->getTimeOfArrival() == 0) {
						if (compare->getExecutionTime() < executionTime) {
							first = compare;
						}
					}
				}
			}
			//sort by priority
			else if (m_runType == FIXED_PRIORITY_PRE_EMPTIVE) {
				int priority = first->getPriority();
				for (int i = 0; i < m_Ready->getPCBCount(); i++) {
					PCB* compare = m_Ready->getPCBatIndex(i);
					if (compare->getTimeOfArrival() == 0) {
						if (compare->getPriority() < priority) {
							first = compare;
						}
					}
				}
			}
			//if ready to execute
			if (first->getTimeOfArrival() == 0) {
				//execute
				int exectime = first->getExecutionTime();
				if (exectime > 0) {
					first->setTimeOfExecution(--exectime);
				}
				//remove from ready queue
				else {
					m_batchTime += completionTime;
					first->setState(PROCESS_STATE_COMPLETED);
					m_Completed->insertPCBatEnd(first);
					m_Ready->removePCB(first);
					m_isystemCommands.push_back(SHOW_COMPLETED);
//test queue removal
//					cout << m_Ready->getPCBCount() << endl;
//					system("pause");
//end test
				}
			}
		}
//test completion time
//		cout << completionTime << endl;
//end test
		completionTime++;
	}
//	//round robin without time quantum
//	for (int i = 0; i < m_Ready->getPCBCount(); i++) {
//		PCB* temp = m_Ready->getPCBatIndex(i);
//		if (temp) {
//			//only run the ones that are set to running
//			if (temp->getState() == PCBi::PROCESS_STATE_RUNNING) {
//				//get execution time
//				int exectime = temp->getExecutionTime();
//				//if still executing
//				if (exectime > 0) {
//					temp->setTimeOfExecution(--exectime);
//					completionTime++;
//				}
//				//remove from ready queue
//				else {
//					temp->setState(PROCESS_STATE_COMPLETED);
//					m_Completed->insertPCBatEnd(temp);
//					m_Ready->removePCB(temp);
//					m_isystemCommands.push_back(SHOW_COMPLETED);
////test queue removal
////					cout << m_Ready->getPCBCount() << endl;
////					system("pause");
////end test
//				}
//			}
//		}
//	}
	//once done return batchtime
	if (m_Ready->getPCBCount() == 0 && m_Completed->getPCBCount() != 0) {
		completionTime = 0;
		m_execute = false;
	}
	return completionTime;
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
	m_running = false;
}

std::string Core::getTime(const time_t time) {

	struct tm ts;
	char szBuffer[80] = "DD-MM-YY"; //  HH:MM:SS

	errno_t err = localtime_s(&ts, &time);

	if (!err)
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
	const char module[] = "Python";

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
//add system commands to user command queue
void Core::addSystem(void) {
	for (int i = 0; i < m_isystemCommands.size(); i++) {
		m_icommand.push_back(m_isystemCommands[i]);
	}
	m_isystemCommands.clear();
}