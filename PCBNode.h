#include "PCB.h"

class PCBNode {
	friend class PCBQueue;
private:
	PCBNode* m_pnext;
	PCBNode* m_pprev;
	PCB* m_pPcb;
public:
	PCBNode(void) : m_pnext(NULL), m_pprev(NULL), m_pPcb(NULL) {}

	//get value
	PCB* getPCB(void) {
		return m_pPcb;
	}
	PCBNode* getNext(void) {
		return m_pnext;
	}
	PCBNode* getPrev(void) {
		return m_pprev;
	}
	//set value
	void setPCB(PCB* pcb) {
		m_pPcb = pcb;
	}
	void setNext(PCBNode* next) {
		m_pnext = next;
	}
	void setPrev(PCBNode* prev) {
		m_pprev = prev;
	}
};