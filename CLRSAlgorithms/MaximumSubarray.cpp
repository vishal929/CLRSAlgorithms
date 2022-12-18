#include <vector>

/*
	Exercise in Ch 4 of CLRS section 1 (Kadanes Algorithm Implementation)
*/


/*
	Given an array of integers, find the maximum contiguous subarray
	We return the pair of indices which represent the start and end of the subarray
	If the subarray is empty, we return (-1,-1)
	Otherwise we return (index1,index2) where index1 <= index2
*/
std::pair<int,int> findMaxSubarray(std::vector<int> arr) {
	using namespace std;

	//using the idea that at the i-th iteration, we compute the maximum subarray ending at A[i] 
	// this works because the maximum contiguous subarray is either empty or ends at some index in the array	

	int max_global = 0;
	int max_so_far = 0;
	int local_start = 0;
	int local_end = 0;
	int global_start = -1;
	int global_end = -1;
	for (int i = 0; i < arr.size(); i++) {
		if (max_so_far<0) {

			local_start = i;
			local_end = i;
			max_so_far = arr[i];
		}
		else {
			max_so_far += arr[i];
			local_end = i;
		}
		
		if (max_so_far > max_global) {
			max_global = max_so_far;
			global_start = local_start;
			global_end = local_end;
		}
	}

	return make_pair(global_start,global_end);
		
	}
