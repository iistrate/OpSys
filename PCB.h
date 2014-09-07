#ifndef PCB_H
#define PCB_H

#include <string>
#include "Globals.h"

class PCB {
private:
	//process name
	char** m_sname;
	//process class system or app
	int m_iprocessClass;
	//process priority
	int m_ipriority;
	//process state
	int m_iprocessState;

public:
	PCB();
	~PCB();
	void setName(char** name);
	void setClass(int pclass);
	void setPriority(int priority);
	void setState(int state);
	
	char** getName();
	int getClass();
	int getPriority();
	int getState();

};

#endif