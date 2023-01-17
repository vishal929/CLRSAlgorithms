
#include <vector>

/*
	Standard implementation of insertion sort in O(n^2) time to use as a helper function
*/

/*
	Implementation of insertion sort in place
	Insertion sort is worst case O(n^2) time and uses the idea that we maintain a subarray that is sorted
	arr is the input array of integers to sort
*/
void insertionSort(std::vector<int> arr){
	using namespace std;

	for (int i = 1; i < arr.size(); i++) {
		int j = 0;
		for (j = i - 1; j >= 0; j--) {
			if (arr[i] >= arr[j]) {
				// then we found the right position for i (namely j+1)
				break;
			}
		}
		
		int tmp = arr[j + 1];
		arr[j + 1] = arr[i];
		arr[i] = tmp;
	}
}