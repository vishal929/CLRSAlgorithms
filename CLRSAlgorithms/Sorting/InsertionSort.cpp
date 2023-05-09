
#include <vector>

/*
	Standard implementation of insertion sort in O(n^2) time to use as a helper function
*/

/*
	Implementation of insertion sort in place
	Insertion sort is worst case O(n^2) time and uses the idea that we maintain a subarray that is sorted
	arr is the input array of integers to sort
*/
template<class RandomAccessIterator>
void insertionSort(RandomAccessIterator first, RandomAccessIterator last){
	for (RandomAccessIterator i = first+1; i != last; i++) {
		RandomAccessIterator j = i-1;
		for (RandomAccessIterator j = i - 1; j >= first; j--) {
			if (*i >= *j) {
				// this is the right position for i
				break;
			}
		}
		int tmp = *(j + 1);
		*(j + 1) = *i;
		*i = tmp;
	}
}

template<class RandomAccessIterator, class Compare>
void insertionSort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp){
	for (RandomAccessIterator i = first+1; i != last; i++) {
		RandomAccessIterator j = i-1;
		for (RandomAccessIterator j = i - 1; j >= first; j--) {
			if (cmp(*i, *j)) {
				// this is the right position for i
				break;
			}
		}
		int tmp = *(j + 1);
		*(j + 1) = *i;
		*i = tmp;
	}
}