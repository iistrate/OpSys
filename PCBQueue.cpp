#include "PCBQueue.h"

//set state of PCB
PCBQueue::PCBQueue(bool state) {
	m_bstate = state;
}


PCB* PCBQueue::PCBQueue() {
	PCB* pcb = new PCB();
	if (pcb) {
		return pcb;
	}
	else {
		return NULL;
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