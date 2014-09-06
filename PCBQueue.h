#ifndef PCBQUEUE_H
#define PCBQUEUE_H

#include "PCB.h"

class PCBQueue {
private:

	struct PCBNode {
		PCBNode* next;
		PCBNode* prev;
		PCB* data;
	};

	//count of PCB's
	int m_iPCBcount;
	//ready or blocked
	bool m_bstate;

	PCBNode* start;
public:
	PCBQueue(bool state);

	PCB* allocatePCB();

	int getPCBCount();
	bool getState();
	void addPCB();
};

#endif