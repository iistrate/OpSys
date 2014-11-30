#include "Memory.h"

bool Memory::isAlocatted(string identifier) {
	Node* navigator = m_head;
	while (navigator != 0) {
		//check if already allocated
		if (navigator->getIdentifier().compare(identifier) == 0) {
			return true;
		}
		navigator = navigator->getNext();
	}
	return false;
}

void Memory::allocate(int size, string identifier) {
	Node* node = new Node(size, identifier);
	//node to be inserted
	if (m_fragments == 0) {
		m_head = node;
	}
	else if (m_fragments == 1) {
		m_tail = node;
		m_head->setNext(m_tail);
		m_tail->setPrev(m_head);
	}
	else {
		Node* temp = m_tail;
		m_tail = node;
		temp->setNext(m_tail);
		m_tail->setPrev(temp);
	}
	//increase fragment count
	m_fragments++;
	m_freeMemory -= node->getSize();
	//test memory allocated
	cout << "Allocated " << node->getSize() << " free memory: " << m_freeMemory << endl;
	system("pause");
//end
}

void Memory::firstFit(Node* node) {

}
void Memory::nextFit(Node* node) {

}
void Memory::bestFit(Node* node) {

}
void Memory::worstFit(Node* node) {

}

void Memory::coalescing(void) {

}
void Memory::compacting(void) {

}