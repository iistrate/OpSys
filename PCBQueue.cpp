#include "PCBQueue.h"

//set state of PCB
PCBQueue::PCBQueue(bool state): m_head(0), m_tail(0), m_iPCBcount(0) {
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
PCB* PCBQueue::setupPCB(std::string name, int priority, int classType) {
	PCB* pcb = 0;
	bool allocate = false;
	//errror check
	if (name.size() > 0) {
		if (priority >= -127 && priority <= 127) {
			if (classType == SYSTEM_TYPE || classType == APPLICATION) {
				allocate = true;
			}
		}
	}
	//allocate pcb
	if (allocate) {
		PCB* pcb = allocatePCB();
		pcb->setName(name);
		pcb->setClass(classType);
		pcb->setPriority(priority);
		pcb->setState(PROCESS_STATE_READY);
	}
	return pcb;
}
void PCBQueue::insertPCB(PCB* pcb) {
	//if there's no PCB's
	if (m_iPCBcount == 0) {
		//create node for pcb
		PCBNode* newNode = 0;
		//assign passed pcb to node
		newNode->Pcb = pcb;
		//link frontend
		m_head->next = newNode;
		m_head->prev = 0;
		//we don't want pcb's in head or tail
		m_head->Pcb = 0;
		//integrate in list
		newNode->next = m_tail;
		//link backend
		m_tail->next = 0;
		m_tail->prev = newNode;
		//we don't want pcb's in head or tail
		m_tail->Pcb = 0;
	}
	//if there's PCB's in queue then navigate nodes to find the last one; pretty much just get the prev from last
	else {
		//we know the last node is m_tail; we want the prev from it
		//create node for pcb
		PCBNode* newNode = 0;
		//assign passed pcb to node
		newNode->Pcb = pcb;
		//integrate in list
		//link newNode to tail
		newNode->next = m_tail;
		//get last pcb node from tail and link it to new node
		m_tail->prev->next = newNode;
		//link tail to new node 
		m_tail->prev = newNode;
	}
	//increase PCB count
	m_iPCBcount++;
}
PCB* PCBQueue::findPCB(std::string name) {
	//create node navigator
	PCBNode* navigator = 0;
	//link navigator to start of list
	navigator = m_head;
	//traverse nodes
	while (navigator != 0) {
		navigator = navigator->next;
		if (navigator->Pcb->getName() == name) {
			return navigator->Pcb;
			std::cout << navigator->Pcb->getName() << std::endl;
		}
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