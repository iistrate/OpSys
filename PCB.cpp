#include "PCB.h"

PCB::PCB(): m_priority(0), m_processClass(0), m_processState(0), m_name("empty") {
}


void PCB::setName(std::string name) {
	m_name = name;
}
void PCB::setClass(int pclass) {
	m_processClass = pclass;
}
void PCB::setPriority(int priority) {
	m_priority = priority;
}
void PCB::setState(int state) {
	m_processState = state;
}

std::string PCB::getName() {
	return m_name;
}
int PCB::getClass() {
	return m_processClass;
}
int PCB::getPriority() {
	return m_priority;
}
int PCB::getState() {
	return m_processState;
}
