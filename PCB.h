#ifndef PCB_H
#define PCB_H

#include <string>
#include "Globals.h"

class PCB {
private:
	//process name
	std::string m_sname;
	//process class system or app
	const int m_iprocessClass;
	//process priority
	int m_ipriority;
	//process state
	int m_iprocessState;

public:
};

#endif