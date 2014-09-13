#ifndef PCB_H
#define PCB_H

#include <string>
#include "Globals.h"

class PCB {
private:
	//process name
	std::string m_name;
	//process class system or app
	int m_processClass;
	//process priority
	int m_priority;
	//process state
	int m_processState;

public:
	PCB();
	//sets name
	void setName(std::string name);
	//sets class app or system type
	void setClass(int pclass);
	//sets priority -127 to 127
	void setPriority(int priority);
	//sets state PROCESS_STATE_RUNNING, PROCESS_STATE_READY, PROCESS_STATE_BLOCKED, PROCESS_STATE_SUSPENDED, PROCESS_STATE_NOT_SUSPENDED
	void setState(int state);
	
	std::string getName();
	int getClass();
	int getPriority();
	int getState();

};

#endif