#include <vector>


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

//todo: implement
// bucket sort splits the input into buckets and then sorts within buckets
// we use a linked list of buckets in order to accomplish this
std::vector<int> bucketSort(std::vector<int> arr) {

}





