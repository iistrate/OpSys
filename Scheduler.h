#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <fstream>
#include <sstream>

#include "PCBQueue.h"
#include "Globals.h"

class Scheduler {
private:
	PCBQueue& m_Ready;
	PCBQueue& m_Blocked;
public:
	//with Queues
	Scheduler(PCBQueue& Ready, PCBQueue& Blocked): m_Ready(Ready), m_Blocked(Blocked) {}
	
	std::vector < std::vector < std::string > > parseFile(std::string filename);
	void addPCBS(std::string filename, const int sortBy);
};

#endif