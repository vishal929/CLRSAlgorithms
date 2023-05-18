#include <vector>
#include <algorithm>

/*
    given a vector of integers, return tuples (nums[i],nums[j],nums[k]) where i \neq j \neq k such that the tuple sums to 0
*/
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    using namespace std;
    vector<vector<int>> solutions;
    // sorting nums
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        while (i > 0 && i < nums.size() && nums[i] == nums[i - 1]) i++;
        int j = i + 1;
        int k = nums.size() - 1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum == 0) {
                //solution
                vector<int> sol{ nums[i],nums[j],nums[k] };
                solutions.push_back(sol);
                j++;
                // simple check to remove dupes
                while (j < k && nums[j] == nums[j - 1]) j++;
            }
            else if (sum > 0) {
                // overshoot
                k--;
            }
            else {
                // undershoot
                j++;
            }
        }
    }
    return solutions;
}