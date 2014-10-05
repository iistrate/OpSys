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
	//pcb index
	int m_index;

public:
	PCB::PCB() : m_priority(0), m_processClass(0), m_processState(0), m_name("empty") {}

	//sets name
	void setName(std::string name) {
		m_name = name;
	}	
	//sets class app or system type
	void setClass(int pclass) {
		m_processClass = pclass;
	}	
	//sets priority -127 to 127
	void setPriority(int priority) {
		m_priority = priority;
	}
	//sets state PROCESS_STATE_RUNNING, PROCESS_STATE_READY, PROCESS_STATE_BLOCKED, PROCESS_STATE_SUSPENDED, PROCESS_STATE_NOT_SUSPENDED
	void setState(int state) {
		m_processState = state;
	}
	void setIndex(int index) {
		m_index = index;
	}

	int getIndex() {
		return m_index;
	}
	std::string getName() {
		return m_name;
	}
	int getClass() {
		return m_processClass;
	}
	int getPriority() {
		return m_priority;
	}
	int getState() {
		return m_processState;
	}

};

#endif