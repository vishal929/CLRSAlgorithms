#include <vector>


/*
	Implementation of a heap (I will use a max heap here)
	In order to get a min heap, we can just take the negative of the inputs
*/

class Heap {
public:
	std::vector<int> arr;
	
	// constructor with nothing
	Heap() {
		arr = std::vector<int>();
	}
	
	// overloaded constructor with input array already
	Heap(std::vector<int> inputArr) {
		arr = std::vector<int>();
		// we want to heapify the array
		// basically, we just insert elements one by one to the heap
		// we have n elements to insert and each siftUp costs logn time, so this is O(nlogn) time
		for (int i = 0; i < inputArr.size(); i++) {
			push(inputArr[i]);
		}
	}

	// Heap methods

	// return the current maximum of the heap without removing it	
	int top() {
		if (arr.size() == 0) {
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

		if (arr.size() == 1) {
			// then we do not need to sift down, just delete this element
			arr.erase(arr.begin());
		}
		else {
			//replacing top value with the final child
			arr[0] = arr[arr.size() - 1];
			arr.pop_back();
			// sifting down
			siftDown();
		}
		
		
		return val;
	}

	// push a new value onto the heap (sift up operation)
	void push(int newVal) {
		arr.push_back(newVal);
		siftUp();
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
	void siftUp() {
	}

	// sift down will make comparisons going downwards through each level
	void siftDown() {
		bool swapsMade = true;
		int index = 0;
		do {
			int left = leftChild(index);
			// we are done sifting if we hit the next condition because if there is no left child there is definitely no right child
			if (left >= arr.size()) break;

			int right = rightChild(index);
			int maxIndex = left;
			if (right < arr.size() && arr[right] < arr[left]) maxIndex = right;
			
			if (arr[index] > arr[maxIndex]) {
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


// sorting an array using the above heap class
void heapsort() {

}

