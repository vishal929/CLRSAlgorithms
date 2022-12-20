#include <vector>
#include <cstdlib>

/*
	Implementing the O(nlogn) quicksort algorithm as described in CLRS textbook
	Maybe I will remove the recursive structure and compare performance as well...
*/

/*
	Partitioning an array in place using the last index of the subarray as the pivot!
	We return the index where the pivot should be (basically its position in the sorted array)
	arr: array to partition on
	firstIndex: index of the start of the subarray to partition on
	lastIndex: index of the end of the subarray to partition on (INCLUSIVE)
*/
int partition(std::vector<int> arr, int firstIndex, int lastIndex) {
	int start = firstIndex - 1;
	int pivot = arr[lastIndex];
	for (int i = firstIndex; i < lastIndex; i++) {
		if (arr[i] < pivot) {
			start++;
			// swap with start
			int temp = arr[start];
			arr[start] = arr[i];
			arr[i] = temp;
		}
		
	}
	// now start points to the last element in the subarray that is less than the pivot
	// so, the pivot must be in the next index
	start++;
	arr[lastIndex] = arr[start];
	arr[start] = pivot;
	return start;
}

/*
	Recursive implementation of quicksort
	If we set usingRandomized to true, we are choosing the pivot randomly (make sure to properly set a seed for randomization!)
	If usingRandomized is false, we are using the naive partitioning scheme (last element is the pivot)
	With randomized pivot selection, expected runtime is O(nlog(n))
*/
void quicksortRecursive(std::vector<int> arr, int start, int end, bool usingRandomized) {
	if (start < end) {
		if (usingRandomized) {
			int randomIndex = (rand() % (end - start)) + start;
			int temp = arr[randomIndex];
			arr[randomIndex] = arr[end];
			arr[end] = temp;
		}
		int sortedPosition = partition(arr, start, end);
		quicksortRecursive(arr, start, sortedPosition - 1, usingRandomized);
		quicksortRecursive(arr, sortedPosition + 1, end, usingRandomized);
	}
}

/*
	Non-Recursive implementation of quicksort using a stack
	If we set usingRandomized to true, we are choosing the pivot randomly (make sure to properly set a seed for randomization!)
	If usingRandomized is false, we are using the naive partitioning scheme (last element is the pivot)
	With randomized pivot selection, expected runtime is O(nlog(n))
*/
void quicksort(std::vector<int> arr, int start, int end, bool usingRandomized) {

}



