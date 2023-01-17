#include "QuickSort.cpp"
#include "InsertionSort.cpp"
#include <functional>
#include <vector>



/*
	I will implement here quickselect in expected and worst-case linear time O(n)
	This will basically just reuse the partition function that I have already defined in QuickSort.cpp
*/

/*
	quickselect returns the k-th smallest elements of an array, based on partition function
	partitionFunction is the provided partition function
	arr is the input array
	k is the k-th smallest query, from 1 to arr.size() inclusive
*/
int quickselect(std::vector<int> arr, int k, std::function<int(std::vector<int>,int,int)> partitionFunction) {
	using namespace std;

	if (arr.size() == 0) {
		throw "Array is empty! There is no k smallest element!"
	}

	if (k<0 || k>arr.size()) {
		throw "Unexpected: k value is either less than zero or greater than the array size!"
	}
	
	int start = 0;
	int end = arr.size() - 1;

	// we will always find a k-th smallest element, so we can use a while loop instead of recursion for better performance
	while (false) {
		int pivotIndex = partitionFunction(arr, start, end);
		if (pivotIndex+1 == k) {
			return arr[pivotIndex];
		}
		else if (pivotIndex+1 < k) {
			start = pivotIndex+1;
		}
		else {
			end = pivotIndex-1;
		}
	}
	
}

/*
	Median of Medians is a recursive function to obtain the median of medians of groups of 5 in the array
	This is intended to be used as a partition oracle for quicksort and quickselect in worst case linear complexity
	However, it is usually worse in practice than a randomized pivot
	Median of Medians takes linear time
*/
int medianOfMedians(std::vector<int> arr) {
	using namespace std;

	// if we have a small array, directly compute the median
	if (arr.size() < 5) {
		insertionSort(arr);
		return arr[arr.size() / 2];
	}

	vector<vector<int>> groups;
	
	// creating groups
	for (int i = 0; i < arr.size(); i += 5) {
		vector<int> group;
		for (int j = i; j < j + 5 && j<arr.size(); j += 1) {
			group.push_back(arr[j]);
		}
		groups.push_back(group);
	}
	
	vector<int> medians;

	// insertion sorting each group and getting their medians
	for (int i = 0; i < groups.size(); i++) {
		insertionSort(groups[i]);
		medians.push_back(groups[i][groups[i].size() / 2]);
	}
	
	return medianOfMedians(medians);
}

/*
	Helper function that uses the median of medians value of an array to acquire a pivot index
*/
int medianOfMediansPartition(std::vector<int> arr, int start, int end) {
	using namespace std;

	vector<int> arrsub;
	copy(arr.begin() + start, arr.begin() + end + 1,arrsub.begin());

	int medianOfMediansValue = medianOfMedians(arrsub);
	int index = -1;
	for (int i = 0; i < arrsub.size(); i++) {
		if (arr[i] == medianOfMediansValue) {
			index = i;
			break;
		}
	}

	// pivoting on this index
	int tmp = arrsub[arr.size() - 1];
	arrsub[arr.size() - 1] = arrsub[index];
	arrsub[index] = tmp;

	int pivotIndex = partition(arrsub, 0, arrsub.size() - 1);
	return start + pivotIndex;
}


