#include "PCB.h"

PCB::PCB(): m_sname(0), m_ipriority(0), m_iprocessClass(0), m_iprocessState(0) {

}
PCB::~PCB() {
	delete this;
}


void PCB::setName(std::string name) {
	m_sname = name;
}
void PCB::setClass(int pclass) {
	m_iprocessClass = pclass;
}
void PCB::setPriority(int priority) {
	m_ipriority = priority;
}
void PCB::setState(int state) {
	m_iprocessState = state;
}

std::string PCB::getName() {
	return m_sname;
}
int PCB::getClass() {
	return m_iprocessClass;
}
int PCB::getPriority() {
	return m_ipriority;
}
int PCB::getState() {
	return m_iprocessState;
}
