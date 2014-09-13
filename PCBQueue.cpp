#include "PCBQueue.h"

//set state of PCB
PCBQueue::PCBQueue(bool state) : m_iPCBcount(0), m_bstate(state) {
	m_phead = m_ptail = 0;
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
	delete pcb;
}
//setup PCB
PCB* PCBQueue::setupPCB(std::string name, int priority, int classType) {
	PCB* pcb = 0;
	bool allocate = false;
	//errror check
	if (!name.empty()) {
		if (priority >= -127 && priority <= 127) {
			if (classType == SYSTEM_TYPE || classType == APPLICATION) {
				allocate = true;
			}
		}
	}
	//allocate pcb
	if (allocate) {
		pcb = allocatePCB();
		pcb->setName(name);
		pcb->setClass(classType);
		pcb->setPriority(priority);
		pcb->setState(PROCESS_STATE_READY);
	}
	return pcb;
}
void PCBQueue::insertPCBatEnd(PCB* pcb) {
	//node to be inserted
	PCBNode* newNode = new PCBNode;
	//if there's no PCB's
	if (m_iPCBcount == 0) {
		//assign passed pcb to node
		newNode->setPCB(pcb);
		//link frontend
		m_phead->setNext(newNode);
		m_phead->setPrev(0);
		//integrate in list
		newNode->setNext(m_ptail);
		//link backend
		m_ptail->setNext(0);
		m_ptail->setPrev(newNode);
	}
	//if there's PCB's in queue then navigate nodes to find the last one; pretty much just get the prev from last
	else {
		//we know the last node is m_ptail; we want the prev from it
		//assign passed pcb to node
		newNode->setPCB(pcb);
		//integrate in list
		//link newNode to tail
		newNode->setNext(m_ptail);
		//get last pcb node from tail and link it to new node
		m_ptail->getPrev()->setNext(newNode);
		//link tail to new node 
		m_ptail->setPrev(newNode);
	}
	//increase PCB count
	m_iPCBcount++;
}
PCB* PCBQueue::findPCB(std::string name) {
	//create node navigator
	PCBNode* navigator = 0;
	//link navigator to start of list
	navigator = m_phead;
	//traverse nodes
	while (navigator != 0) {
		if (navigator->getPCB() != 0) {
			if (navigator->getPCB()->getName() == name) {
				return navigator->getPCB();
				std::cout << navigator->getPCB()->getName() << std::endl;
			}
		}
		navigator = navigator->getNext();
	}
	return 0;
}

void PCBQueue::removePCB(PCB* pcb) {
	//find node containing pcb then remove it from list, and destroy the pcb
	PCBNode* navigator = 0;
	navigator = m_phead;
	do {
		if (navigator->getPCB() != 0) {
			if (navigator->getPCB()->getName() == pcb->getName()) {
				if (navigator->getPrev() != 0 && navigator->getNext() != 0) {
					//connect previous to next, remove current 
					navigator->getPrev()->setNext(navigator->getNext());
					navigator->getNext()->setPrev(navigator->getPrev());
					//deallocate memory
					delete navigator->getPCB();
					delete navigator;
					//decrease count
					m_iPCBcount--;
					break;
				}
			}
		}
		navigator = navigator->getNext();
	} while (navigator != 0);
}

//return PCB count
int PCBQueue::getPCBCount(){
	return m_iPCBcount;
}
//return Queue state ready or blocked
bool PCBQueue::getState() {
	return m_bstate;
}