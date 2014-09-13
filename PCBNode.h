#ifndef PCBNODE_H
#define PCBNODE_H

#include "PCB.h"

class PCBNode {
	friend class PCBQueue;
private:
	PCBNode* m_next;
	PCBNode* m_prev;
	PCB* m_Pcb;
public:
	//empty node
	PCBNode(void) : m_next(NULL), m_prev(NULL), m_Pcb(NULL) {}
	//node with pcb
	PCBNode(PCB* pcb) : m_next(NULL), m_prev(NULL), m_Pcb(pcb) {}

	//when node is deleted get rid of pcb
	~PCBNode() {
		delete m_Pcb;
	}

	//get value
	PCB* getPCB(void) {
		return m_Pcb;
	}
	PCBNode* getNext(void) {
		return m_next;
	}
	PCBNode* getPrev(void) {
		return m_prev;
	}
	//set value
	void setPCB(PCB* pcb) {
		m_Pcb = pcb;
	}
	void setNext(PCBNode* next) {
		m_next = next;
	}
	void setPrev(PCBNode* prev) {
		m_prev = prev;
	}
};

#endif