#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
	class Node {
	private:
		int m_size;
		Node* m_next;
	public:
		Node(int size) : m_size(size), m_next(0) {}

		int getSize(void) {
			return m_size;
		}
		Node* getNext(void) {
			return m_next;
		}

		void setSize(int size) {
			m_size = size;
		}
		void setNext(Node* node) {
			m_next = node;
		}
	};
	int m_size;
	Node* m_root;
public:
	Memory(int size) : m_size(size), m_root(0) {}
	
	int getSize(void) {
		return m_size;
	}
	void setSize(int size) {
		m_size = size;
	}

	void firstFit(Node* node);
	void nextFit(Node* node); 
	void bestFit(Node* node);
	void worstFit(Node* node);

	void coalescing(void);
	void compacting(void);

};

#endif //end Memory.h