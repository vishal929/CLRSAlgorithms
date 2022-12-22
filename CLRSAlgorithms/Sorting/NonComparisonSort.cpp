#include <vector>
#include <unordered_map>
#include "LinkedList.cpp"


/*
	Implementation of Sorting algorithms that are not comparison based
*/


// counting sort runs in O(n+k) time where k is the maximum value in the array
// The assumption is that all the integers in the input array are values from 0 to k (k>0)
// Note that counting sort is STABLE (if two elements are equal, then sorting will preserve their order in the input array)
std::vector<int> countingSort(std::vector<int> arr, int k) {
	using namespace std;
	vector<int> store = vector<int>(k,0);
	vector<int> result = vector<int>(arr.size(),0);
	for (int i = 0; i < arr.size(); i++) {
		store[arr[i]] ++;
	}

	for (int j = 1; j < store.size(); j++) {
		// store[j] is now the number of elements less than or equal to j
		store[j] = store[j - 1] + 1;
	}
	
	for (int i = arr.size()-1; i >=0; i--) {
		result[store[arr[i]]-1] = arr[i];
		store[arr[i]]--;
	}

	return result;
}

// helper for radix sort that just sorts arr on a specific digit (in base 10)
std::vector<int> countingSortRadixHelper(std::vector<int> arr, int k, int digit) {
	using namespace std;


	vector<int> store = vector<int>(k,0);
	vector<int> result = vector<int>(arr.size(),0);
	for (int i = 0; i < arr.size(); i++) {
		int digitValue = ((int)(arr[i] / pow(10, digit))) % 10;
		store[digitValue] ++;
	}

	for (int j = 1; j < store.size(); j++) {
		// store[j] is now the number of elements less than or equal to j
		store[j] = store[j - 1] + 1;
	}
	
	for (int i = arr.size()-1; i >=0; i--) {
		int digitValue = ((int)(arr[i] / pow(10, digit))) % 10;
		result[store[digitValue]-1] = arr[i];
		store[digitValue]--;
	}

	return result;
	
}

// implementation of counting sort using a hash map (gets around the negative value conundrum)
// we also sort in place here (using an unordered map, we do not have a stable sort!)
// takes O(k+n) time because we iterate through k elements but we insert at most n 
void countingSortHashMap(std::vector<int> arr) {
	using namespace std;
	unordered_map<int, int> map = new unordered_map<int, int>();
	// we need to keep track of the smallest and largest element
	int smallest = INT32_MAX;
	int largest = INT32_MIN;
	for (int i = 0; i < arr.size(); i++) {
		if (map.find(arr[i]) != map.end()) {
			map[arr[i]] ++;
		}
		else {
			map.insert(make_pair(arr[i], 1));
		}
		if (arr[i] < smallest) smallest = arr[i];
		if (arr[i] > largest) largest = arr[i];
	}
	
	int insertionPosition = 0;
	for (int i = smallest; i <= largest; i++) {
		if (map.find(i) != map.end()) {
			for (int j = 0; j < map[i]; j++) {
				arr[insertionPosition] = i;
				insertionPosition++;
			}
		}
	}
}

std::vector<int> countingSortRadixBinaryHelper(std::vector<int> arr, int digit) {
	using namespace std;


	vector<int> store = vector<int>(2,0);
	vector<int> result = vector<int>(arr.size(),0);
	for (int i = 0; i < arr.size(); i++) {
		int bitmask = 2 << digit;
		int digitValue = (arr[i] & bitmask) >> digit;
		store[digitValue] ++;
	}

	for (int j = 1; j < store.size(); j++) {
		// store[j] is now the number of elements less than or equal to j
		store[j] = store[j - 1] + 1;
	}
	
	for (int i = arr.size()-1; i >=0; i--) {
		int bitmask = 2 << digit;
		int digitValue = (arr[i] & bitmask) >> digit;
		result[store[digitValue]-1] = arr[i];
		store[digitValue]--;
	}

	return result;
	
}


// given d-digit numbers where digits can range from 0 to k, radix sort takes O(d(n+k)) time
// we use counting sort as a subroutine for radix sort
// we assume here that digits are from 0-9
std::vector<int> radixSort(std::vector<int> arr, int d) {
	using namespace std;
	vector<int> res = arr;
	for (int i = 0; i < d; i++) {
		res = countingSortRadixHelper(res,9,d);
	}
	return res;
}

// radix sort on the input using the binary representation of the integers -> O(dn) time where d is the number of bits
// the hope is that in practice, using the binary representation in radix sort is the faster than base 10 representation
std::vector<int> radixSortBinary(std::vector<int> arr, int d) {
	using namespace std;
	vector<int> res = arr;
	for (int i = 0; i < d; i++) {
		res = countingSortRadixBinaryHelper(res,d);
	}
	return res;
	
}

// bucket sort splits the input into buckets and then sorts within buckets
// we use a linked list of buckets in order to accomplish this
// the input array are values from [0,1), note that we can just divide any array by the largest value + 1 to achieve something similar 
// we sort in place
// todo: implement generics
void bucketSort(std::vector<int> arr) {
	// initializing a bucket-list	
	std::vector<LinkedList> buckets = new std::vector<LinkedList>(arr.size(), new LinkedList());

	for (int i = 0; i < arr.size(); i++) {
		buckets[(int)(arr[i] * arr.size())].insert(arr[i], 0);
	}

	// sorting each bucket
	for (int i = 0; i < buckets.size(); i++) {
		buckets[i].insertionSort();
	}

	// returning the buckets concatenated
	int insertionIndex = 0;
	for (int i = 0; i < buckets.size(); i++) {
		LinkedListNode* runner = buckets[i];
		while (runner != nullptr) {
			arr[insertionIndex] = runner->item;
			runner = runner->next;
			insertionIndex++;
		}
	}
}





