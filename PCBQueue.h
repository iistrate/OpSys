#ifndef PCBQUEUE_H
#define PCBQUEUE_H

#include "PCBNode.h"

using std::cout;
using std::endl;


class PCBQueue {
private:
	PCBNode* m_head;
	PCBNode* m_tail;

	//count of PCB's
	int m_PCBcount;
	//ready or blocked
	bool m_state;

public:
	PCBQueue(bool state);

	//create pcb
	PCB* allocatePCB(void);
	//destroy pcb
	void freePCB(PCB*);
	//setup PCB
	PCB* setupPCB(std::string name, int priority, int classType, int memory, int executionTime, int executionStart, int cpuUsed);
	//insert pcb at end
	void insertPCBatEnd(PCB* pcb);
	//find pcb by name
	PCB* findPCB(std::string name);
	//remove pcb
	void removePCB(PCB* pcb);
	//count pcbs in queue
	int getPCBCount(void);
	//get type of queue
	bool getState(void);
	void addPCB(void);

	//get pcb at index
	PCB* getPCBatIndex(int index);
	void printPCBs(void);

	//clear pcb queue
	void clearQueue();
};

#endif