

/*
	Implementation of a linked list, doubly connected linked list, circular linked list, and circular doubly connected linked list
*/
template <typename I>
class LinkedListNode {
	public:
		// element to hold	
		I item;
		// reference to next element
		LinkedListNode* next;


		explicit LinkedListNode(I item) {
			this->item = item;
			this->next = nullptr;
		}

		explicit LinkedListNode(I item, LinkedListNode* next) {
			this->item = item;
			this->next = next;
		}
};

template <typename I>
class DoublyLinkedListNode: public LinkedListNode {
	public:
		// in addition to the linked list node, this holds a reference to a previous node
		LinkedListNode* prev;

		explicit DoublyLinkedListNode(I item):LinkedListNode(item) {
			this->prev = nullptr;
		}

		explicit DoublyLinkedListNode(I item, LinkedListNode* next) : LinkedListNode(item, next) {
			this->prev = nullptr;
		}
		
		explicit DoublyLinkedListNode(I item, LinkedListNode* next, LinkedListNode* prev) : LinkedListNode(item, next) {
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

template <typename I>
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

	LinkedList(LinkedListNode<I>* head) {
		this->head = head;
		this->size = 1;
	}

	int size() {
		return this->size;
	}
	
	// inserting an element at a given index of the linked list (0 index is the head)
	// if there is an element already at this index, we push it over, so that it becomes the next for the inserted node
	void insert(I element, int index) {
		if (index > size) {
			// invalid operation
			throw "Invalid index provided: index cannot be greater than the current size of the linked list!";
		}
		
		LinkedListNode<I>* prev = nullptr;
		LinkedListNode<I>* runner = head;
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
			head = new LinkedListNode<I>(element);
			head->next = runner;
		}
		else {
			prev->next = new LinkedListNode<I>(element);
			prev->next->next = runner;
		}
		size++;
		
	}

	// removing an element at a given index (0 index is the head)
	// then the nodes to the right of it shift to the left to compensate
	void erase(int index) {
		if (index > size) {
			// invalid operation
			throw "Invalid index provided: index cannot be greater than the current size of the linked list!";
		}

		LinkedListNode<I>* prev = nullptr;
		LinkedListNode<I>* runner = head;
		int currIndex = 0;
		while (currIndex != index) {
			prev = runner;
			runner = runner->next;
			currIndex++;
		}
		if (prev == nullptr) {
			// we are removing the head
			if (head != nullptr) {
				head = head->next;
				size--;
			}
		}
		else {
			prev->next = runner->next;
			size--;
		}
	}
	
	//todo: finish swap
	// swapping two nodes in a linked list
	void swap(int indexOne, int indexTwo) {
		if (indexOne > size || indexTwo > size) {
			// invalid operation
			throw "Indices for the swap cannot be greater than the size of the array";
		}
		else if (indexOne == indexTwo) {
			// swapping an element with itself
			return;
		}
		LinkedListNode<I>* onePrev = nullptr;
		LinkedListNode<I>* oneRunner = head;
		int oneIndex = 0;
		while (oneIndex != indexOne) {
			onePrev = oneRunner;
			oneRunner = oneRunner->next;
			oneIndex++;
		}

		LinkedListNode<I>* twoPrev = nullptr;
		LinkedListNode<I>* twoRunner = head;
		int twoIndex = 0;
		while (twoIndex != indexTwo) {
			twoPrev = twoRunner;
			twoRunner = twoRunner->next;
			twoIndex++;
		}

		// swapping
		if (onePrev == nullptr) {
			//swapping head
			twoPrev->next = twoRunner->next;
			twoRunner->next = head->next;
			twoPrev->next = head;

			head = twoRunner;
		}
		else if (twoPrev == nullptr) {
			// swapping head in other orientation
			onePrev->next = oneRunner->next;
			oneRunner->next = head->next;
			onePrev->next = head;

			head = oneRunner;
		}
		else {
			// disconnecting nodes to swap
			twoPrev->next = twoRunner->next;
			onePrev->next = oneRunner->next;

			// setting new next pointers for nodes to swap
			oneRunner->next = twoPrev->next;
			twoRunner->next = onePrev->next;

			// adjusting final connections 
			onePrev->next = twoRunner;
			twoPrev->next = oneRunner;
		}

	}

	// performing insertion sort on a linked list
	// we basically create a new list but using the same space (this maintains the invariant: at each iteration the subarray is sorted)
	void insertionSort() {
		LinkedListNode<I>* sorted = nullptr;
		
		LinkedListNode<I>* runner = head;

		while (runner != nullptr) {
			LinkedListNode<I>* toInsert = runner;
			// finding the best place to insert this node into the sorted linked list
			LinkedListNode<I>* sortedPrev = nullptr;
			LinkedListNode<I>* sortedRunner = sorted;
			while (sortedRunner != nullptr && sortedRunner->item < toInsert->item) {
				sortedPrev = sortedRunner;
				sortedRunner = sortedRunner->next;
			}
			// insertion
			if (sortedPrev == nullptr) {
				// node becomes head of the sorted linked list
				toInsert->next = sortedRunner;
				sorted = toInsert;
			}
			else {
				// we found the best place to insert the node in sorted order
				sortedPrev->next = toInsert;
				toInsert->next = sortedRunner;
			}
			runner = runner->next;
		}

		// setting the head to the head of the sorted list
		head = sorted;
	}

};

template <typename I>
class DoublyLinkedList {
	
};

template <typename I>
class CircularLinkedList {

};

template<typename I>
class CircularDoublyLinkedList {

};

