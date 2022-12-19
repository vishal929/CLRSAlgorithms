#include <vector>


/*
	Implementation of a heap (I will use a max heap here)
	In order to get a min heap, we can just take the negative of the inputs
*/

class Heap {
public:
	int size;
	std::vector<int> arr;
	
	// constructor with nothing
	Heap() {
		size = 0;
		arr = std::vector<int>();
	}
	
	// overloaded constructor with input array already
	Heap(std::vector<int> inputArr) {
		size = inputArr.size();
		arr = inputArr;
		// we want to heapify the array
		// basically, we just insert elements one by one to the heap

		// we can sift down for each elements bottom up
		// however,the bottom half of the elements are already a heap (leaves) 
		// so,we minimize sift down operations, resulting in linear time heap creation
		for (int i = size/2; i >=0; i--) {
			siftDown(i);
		}
	}

	// Heap methods

	// return the current maximum of the heap without removing it	
	int top() {
		if (size == 0) {
			// then we have no top
			throw "Heap is empty!";
		} 
		return arr.front();
	}

	// return the current maximum of the heap and remove it from the heap (sift down operations)
	int pop() {
		int val = top();
		// now the idea is that we can replace the top value with the last value in the array (rightmost child)
		// thus, we can call siftdown and then swap on the way down

		if (size == 1) {
			// then we do not need to sift down, just delete this element
			arr.erase(arr.begin());
			size--;
		}
		else {
			//replacing top value with the final child
			arr[0] = arr[arr.size() - 1];
			arr.pop_back();
			size--;
			// sifting down
			siftDown(0);
		}
		
		
		return val;
	}

	// push a new value onto the heap (sift up operation)
	void push(int newVal) {
		arr.push_back(newVal);
		size++;
		siftUp(size-1);
	}
	
	// this function is just a sanity check to verify that heap invariant is maintained
	bool verifyHeap() {
		for (int i = 0; i < size; i++) {
			// all we do is check that this entry is at least as large as its largest child
			int left = leftChild(i);
			int right = rightChild(i);

			if (left <= size && arr[i] < arr[left]) {
				return false;
			}

			if (right <= size && arr[i] < arr[right]) {
				return false;
			}
		}
		return true;
	}

	// heapsort for an array (in place) (O(nlog(n)) time ) 
	static void heapsort(std::vector<int> arr) {
		if (arr.size() == 0) return;
		// initializing some instance of the class	
		// initializing the heap with the class already invokes heapify, so now arr is a max-heap
		Heap sorter = Heap(arr);
		for (int i = sorter.size - 1; i >= 0; i--) {
			int temp = arr[i];
			arr[i] = arr[0];
			arr[0] = temp;
			sorter.size--;
			sorter.siftDown(0);
		}

		// now arr is sorted in place!
	}

	// returning the index of the parent
	static inline int parent(int index) {
		return (index-1) / 2;
	}

	// return a left child index of a node (when heap is visualized as a binary tree)
	static inline int leftChild(int index) {
		return index * 2 +1 ;
	}

	// return a right child index of a node (when heap is visualized as a binary tree)
	static inline int rightChild(int index) {
		return 2*(index +1);
	}

private:
	// sift up will make comparisons going upwards through each level after insertions
	void siftUp(int index) {
		do {
			int parentIndex = parent(index);

			// below happens if we try this on the root index (0)
			if (parentIndex < 0) break;
			if (arr[parentIndex] < arr[index]) {
				//swap them
				int temp = arr[index];
				arr[index] = arr[parentIndex];
				arr[parentIndex] = temp;
				index = parentIndex;
			}
			else {
				// then no need to continue sifting up
				break;
			}
		} while (true);
	}

	// sift down will make comparisons going downwards through each level
	// basically, we need to maintain the heap invariant for a max heap: the parent should be at least as large as the children
	void siftDown(int index) {
		do {
			int left = leftChild(index);
			// we are done sifting if we hit the next condition because if there is no left child there is definitely no right child
			if (left >= size) break;

			int right = rightChild(index);
			int maxIndex = left;
			if (right < size && arr[right] < arr[left]) maxIndex = right;
			
			if (arr[index] < arr[maxIndex]) {
				// swap these and continue
				int temp = arr[maxIndex];
				arr[maxIndex] = arr[index];
				arr[index] = temp;
				index = maxIndex;
			}
			else {
				// then this index is in the right spot
				break;
			}
		} while (true);

	}
};


