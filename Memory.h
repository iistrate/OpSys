#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Memory {
private:
	class Node {
	private:
		int m_size;
		Node* m_next;
		Node* m_prev;
		bool m_free;
		string m_identifier;
	public:
		Node(int size, string identifier) : m_size(size), m_next(0), m_free(false), m_identifier(identifier) {}

		int getSize(void) {
			return m_size;
		}
		Node* getNext(void) {
			return m_next;
		}
		Node* getPrev(void) {
			return m_prev;
		}
		bool isFree(void) {
			return m_free;
		}
		string getIdentifier(void) {
			return m_identifier;
		}

		void setSize(int size) {
			m_size = size;
		}
		void setNext(Node* node) {
			m_next = node;
		}
		void setPrev(Node* node) {
			m_prev = node;
		}
		void setFree(bool b) {
			m_free = b;
		}
		void setIdentifier(string identifier) {
			m_identifier = identifier;
		}
	};
	int m_maxSize;
	int m_freeMemory;
	int m_fragments;

	Node* m_head;
	Node* m_tail;
public:
	Memory(int size) : m_maxSize(size), m_freeMemory(size), m_fragments(0), m_head(0), m_tail(0) {}
	
	int getMaxSize(void) {
		return m_maxSize;
	}
	int getFreeMemory(void) {
		return m_freeMemory;
	}
	int getFragmentCount(void) {
		return m_fragments;
	}

	void setFragmentCount(int fragmentsCount) {
		m_fragments = fragmentsCount;
	}
	void setFreeMemory(int size) {
		m_freeMemory = size;
	}
	void setMaxSize(int size) {
		m_maxSize = size;
	}

	void allocate(int size, string identifier);
	void free(Node* node);

	void firstFit(Node* node);
	void nextFit(Node* node); 
	void bestFit(Node* node);
	void worstFit(Node* node);

	void coalescing(void);
	void compacting(void);

	bool isAlocatted(string identifier);

};

#endif //end Memory.h