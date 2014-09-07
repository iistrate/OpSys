#include "PCBQueue.h"

//set state of PCB
PCBQueue::PCBQueue(bool state) {
	m_bstate = state;
}

//allocate PCB
PCB* PCBQueue::allocatePCB() {
	//allocate memory for new object
	PCB* pcb = new PCB();

	if (pcb == nullptr) {
		return NULL;
	}
	else {
		return pcb;
	}
}
//destroy pcb
void PCBQueue::freePCB(PCB* pcb) {
	pcb->~PCB();
}
//setup PCB
void PCBQueue::setupPCB(char** name, int priority, int classType) {
	bool allocate = false;
	if (name) {
		if (priority >= -127 && priority <= 127) {
			if (classType == SYSTEM_TYPE || classType == APPLICATION) {
				allocate = true;
			}
		}
	}
	if (allocate) {
		PCB* pcb = allocatePCB();
		pcb->setName(name);
		pcb->setClass(classType);
		pcb->setPriority(priority);
		pcb->setState(PROCESS_STATE_READY);
	}
}


//return PCB count
int PCBQueue::getPCBCount(){
	return m_iPCBcount;
}
//return Queue state ready or blocked
bool PCBQueue::getState() {
	return m_bstate;
}