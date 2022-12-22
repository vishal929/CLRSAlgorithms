

/*
	Implementation of a linked list, doubly connected linked list, circular linked list, and circular doubly connected linked list
*/

class LinkedListNode {
	public:
		// element to hold	
		int item;
		// reference to next element
		LinkedListNode* next;


		explicit LinkedListNode(int item) {
			this->item = item;
			this->next = nullptr;
		}

		explicit LinkedListNode(int item, LinkedListNode* next) {
			this->item = item;
			this->next = next;
		}
};

class DoublyLinkedListNode: public LinkedListNode {
	public:
		// in addition to the linked list node, this holds a reference to a previous node
		LinkedListNode* prev;

		explicit DoublyLinkedListNode(int item):LinkedListNode(item) {
			this->prev = nullptr;
		}

		explicit DoublyLinkedListNode(int item, LinkedListNode* next) : LinkedListNode(item, next) {
			this->prev = nullptr;
		}
		
		explicit DoublyLinkedListNode(int item, LinkedListNode* next, LinkedListNode* prev) : LinkedListNode(item, next) {
			this->prev = prev;
		}	
};

/*
	For each class we just have a couple of basic methods 
	insert(element, index)
	delete(element, index)
	swap(indexOne, indexTwo)
	size()
*/

class LinkedList {
private:
	// reference to the head of the list
	LinkedListNode* head;
	// size of the list
	int size;

public:
	LinkedList() {
		this->head = nullptr;
		this->size = 0;
	}

	LinkedList(LinkedListNode* head) {
		this->head = head;
		this->size = 1;
	}

	int size() {
		return this->size;
	}
	
	// inserting an element at a given index of the linked list
	// if there is an element already at this index, we push it over, so that it becomes the next for the inserted node
	void insert(int element, int index) {
		if (index > size) {
			// invalid operation
			throw "Invalid index provided: index cannot be greater than the current size of the linked list!";
		}
		
		LinkedListNode* prev = nullptr;
		LinkedListNode* runner = head;
		// finding the index
		int currIndex = 0;
		while (currIndex != index) {
			prev = runner;
			runner = runner->next;
			currIndex++;
		}
		//insertion
		if (prev == nullptr) {
			// inserted node becomes the head
			head = new LinkedListNode(element);
			head->next = runner;
		}
		else {
			prev->next = new LinkedListNode(element);
			prev->next->next = runner;
		}
		size++;
		
	}

	// removing an element at a given index
	// then the nodes to the right of it shift to the left to compensate
	void erase(int index) {
		if (index > size) {
			// invalid operation
			throw "Invalid index provided: index cannot be greater than the current size of the linked list!";
		}

		LinkedListNode* prev = nullptr;
		LinkedListNode* runner = head;
		int currIndex = 0;
		while (currIndex != index) {
			prev = runner;
			runner = runner->next;
			currIndex++;
		}
		if (prev == nullptr) {
			// we are removing the head
			if (head != nullptr) head = head->next;
			size--;
		}
		else {
			prev->next = runner->next;
			size--;
		}
	}

};

class DoublyLinkedList {
	
};

class CircularLinkedList {

};

class CircularDoublyLinkedList {

};

