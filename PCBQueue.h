#ifndef PCBQUEUE_H
#define PCBQUEUE_H

#include "PCB.h"

class PCBQueue {
private:
	
	struct PCBNode {
		PCBNode* next;
		PCBNode* prev;
		PCB* Pcb;
	};
	PCBNode* m_head;
	PCBNode* m_tail;


	//count of PCB's
	int m_iPCBcount;
	//ready or blocked
	bool m_bstate;

	PCBNode* start;
public:
	PCBQueue(bool state);

	//create pcb
	PCB* allocatePCB();
	//destroy pcb
	void freePCB(PCB*);
	//setup PCB
	PCB* setupPCB(std::string name, int priority, int classType);
	//insert pcb at end
	void insertPCB(PCB* pcb);
	//find pcb by name
	PCB* findPCB(std::string name);
	//remove pcb
	void removePCB(PCB* pcb);
	//count pcbs in queue
	int getPCBCount();
	//get type of queue
	bool getState();
	void addPCB();
};

#endif