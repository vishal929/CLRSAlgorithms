#include <vector>


/*
	Implementing merge sort (O(nlogn) sorting algorithm)
	Recurrence relation is T(n) = 2T(n/2) + O(n) so we have O(nlg(n)) by the master theorem
*/

/*
	Input is an array of integers
	Output is the sorted array
	This is a divide and conquer recursive algorithm
*/
std::vector<int> mergeSort(std::vector<int> arr) {
	using namespace std;
	// if the array is empty or 1, just return it
	if (arr.size() <= 1) return arr;

	// otherwise, split the array into 2 (if the array is odd, we will have one subarray with one more element than the other subarray)
	size_t const middle = arr.size() / 2;
	vector<int>::iterator middleIterator = arr.begin();
	advance(middleIterator, middle);

	vector<int> leftHalf = vector<int>(arr.begin(), middleIterator);
	vector<int> rightHalf = vector<int>(middleIterator, arr.end());

	mergeSort(leftHalf);
	mergeSort(rightHalf);

	return merge(leftHalf, rightHalf);
}


// merge operation to merge 2 sorted arrays
std::vector<int> merge(std::vector<int> first, std::vector<int> second) {
	using namespace std;
	vector<int> result = vector<int>(0, first.size() + second.size());
	int numInserted = 0;
	int fingerOne = 0;
	int fingerTwo = 0;

	while (fingerOne < first.size() && fingerTwo < second.size()) {
		if (first[fingerOne] < second[fingerTwo]) {
			result[numInserted] = first[fingerOne];
			fingerOne++;
		}
		else {
			result[numInserted] = second[fingerTwo];
			fingerTwo++;
		}
		numInserted++;
	}

	while (fingerOne < first.size()) {
		result[numInserted] = first[fingerOne];
		fingerOne++;
		numInserted++;
	
	}

	while (fingerTwo < second.size()) {
		result[numInserted] = second[fingerTwo];
		fingerTwo++;
		numInserted++;

	}

	return result;
}