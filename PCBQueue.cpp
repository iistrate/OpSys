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
	PCBNode* newNode = new PCBNode(pcb);
	//if there's no PCB's allocate node to head
	if (m_PCBcount == 0) {
		//link frontend
		m_head = newNode;
		//integrate in list
		m_head->setNext(m_tail);
	}
	//if theres one PCB link tail
	else if (m_PCBcount == 1) {
		//link end
		m_tail = newNode;
		m_tail->setPrev(m_head);
		m_head->setNext(m_tail);
	}
	//if there's PCB's in queue then navigate nodes to find the last one; pretty much just get the prev from last
	else {
		PCBNode* tmp;
		//store tail in tmp
		tmp = m_tail;
		//make newNode as my last link
		m_tail = newNode;
		//get last pcb node from tail and link it to new node
		tmp->getPrev()->setNext(m_tail);
		//link tail to new node 
		m_tail->setPrev(tmp->getPrev());
	}
	//increase PCB count
	m_PCBcount++;
}
PCB* PCBQueue::findPCB(std::string name) {
	//create node navigator, link navigator to start of list
	PCBNode* navigator = m_head;
	//traverse nodes
	do {
		if (navigator->getPCB() != 0) {
			if (navigator->getPCB()->getName() == name) {
				return navigator->getPCB();
			}
		}
		navigator = navigator->getNext();
	}
	while (navigator != 0);
	return 0;
}

void PCBQueue::removePCB(PCB* pcb) {
	//find node containing pcb then remove it from list, and destroy the pcb
	PCBNode* navigator = m_head;
	bool unlinked = false;
	do {
		if (navigator->getPCB() != 0) {
			if (navigator->getPCB()->getName() == pcb->getName()) {
				//if start node
				if (navigator == m_head) {
					if (m_PCBcount > 1) {
						m_head = m_head->getNext();
						m_head->setPrev(0);
					}
					//if it's just head delete; no unlinking needed
					unlinked = true;
				}
				//if end node
				else if (navigator == m_tail) {
					m_tail = m_tail->getPrev();
					m_tail->setNext(0);
					unlinked = true;
				}
				//if any other node
				else {
					navigator->getPrev()->setNext(navigator->getNext());
					navigator->getNext()->setPrev(navigator->getPrev());
					unlinked = true;
				}
			}
		}
		if (unlinked) {
			//deallocate memory
			delete navigator;
			//decrease count
			m_PCBcount--;
			//with navigator deleted can't go to next line so just break
			break;
		}
		navigator = navigator->getNext();
	} while (navigator != 0);
}

//return PCB count
int PCBQueue::getPCBCount(){
	return m_PCBcount;
}
//return Queue state ready or blocked
bool PCBQueue::getState() {
	return m_state;
}