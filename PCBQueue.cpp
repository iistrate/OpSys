#include "PCBQueue.h"

//set state of PCB
PCBQueue::PCBQueue(bool state) : m_PCBcount(0), m_state(state), m_head(0), m_tail(0) {}

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
PCB* PCBQueue::setupPCB(std::string name, int priority, int classType, int memory, int executionTime, int executionStart, int cpuUsed) {
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
		pcb->setMemorySize(memory);
		pcb->setTimeOfExecution(executionTime);
		pcb->setTimeOfArrival(executionStart);
		pcb->setCPU(cpuUsed);
	}
	return pcb;
}
void PCBQueue::insertPCBatEnd(PCB* pcb) {
	//node to be inserted
	PCBNode* newNode = new PCBNode(pcb);
	//if there's no PCB's allocate node to head
	if (m_PCBcount == 0) {
		m_head = newNode;
	}
	else if (m_PCBcount == 1) {
		m_tail = newNode;
		m_head->setNext(m_tail);
		m_tail->setPrev(m_head);
	}
	else {
		PCBNode* temp = m_tail;
		m_tail = newNode;
		temp->setNext(m_tail);
		m_tail->setPrev(temp);
	}
	//increase PCB count
	m_PCBcount++;
}
PCB* PCBQueue::findPCB(std::string name) {
	//create node navigator, link navigator to start of list
	PCBNode* navigator = m_head;
	//traverse nodes
	while (navigator != 0) {	
		if (navigator->getPCB() != 0) {
			if (navigator->getPCB()->getName() == name) {
				return navigator->getPCB();
			}
		}
		navigator = navigator->getNext();
	}
	return 0;
}
PCB* PCBQueue::getPCBatIndex(int index) {
	//create node navigator, link navigator to start of list
	PCBNode* navigator = m_head;
	//traverse nodes
	int count = 0;
	while (navigator != 0) {
		if (count == index) {
			return navigator->getPCB();
		}
		navigator = navigator->getNext();
		count++;
	}
	return 0;
}

void PCBQueue::printPCBs() {
	PCBNode* navigator = m_head;
	while (navigator != 0) {
		cout << navigator->getPCB()->getName() << endl;
		navigator = navigator->getNext();
	}
}

void PCBQueue::printPCBsReverse() {
	PCBNode* navigator = m_tail;
	while (navigator != 0) {
		cout << navigator->getPCB()->getName() << endl;
		navigator = navigator->getPrev();
	}
}

void PCBQueue::clearQueue() {
	PCBNode* navigator = m_head;
	PCBNode* temp;
	while (navigator != 0) {
		temp = navigator->getNext();
		delete navigator;
		navigator = temp;
		m_PCBcount--;
	}
}

void PCBQueue::removePCB(PCB* pcb) {
	//find node containing pcb then remove it from list, and destroy the pcb
	PCBNode* navigator = m_head;
	while (navigator != 0) {
		if (navigator->getPCB() != 0) {
			if (navigator->getPCB()->getName() == pcb->getName()) {
				if (navigator == m_head) {
					if (m_PCBcount > 1) {
						m_head = navigator->getNext();
						m_head->setPrev(0);
					}
				}
				else if (navigator == m_tail) {
					m_tail = navigator->getPrev();
					m_tail->setNext(0);
				}
				else {
					PCBNode *next, *prev, *temp;
					next = navigator->getNext();
					prev = navigator->getPrev();
					prev->setNext(next);
					next->setPrev(prev);
				}
				m_PCBcount--;
				break;
			}
		}
		navigator = navigator->getNext();
	}
}

//return PCB count
int PCBQueue::getPCBCount(){
	return m_PCBcount;
}
//return Queue state ready or blocked
bool PCBQueue::getState() {
	return m_state;
}