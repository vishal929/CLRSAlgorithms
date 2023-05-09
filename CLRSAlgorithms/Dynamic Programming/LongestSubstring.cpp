#include <string>
#include <set>

/*
    We find the length of the longest substring of s without repeating characters
    (substring is a contiguous portion of a string, NOT a subsequence)
    s: input string
*/
int lengthOfLongestSubstring(string s) {
    // O(n) solution using two pointers
    int best = 0;
    int left = 0;
    int curr = 0;
    // only dealing with chars which are 1 byte (can just use a map otherwise)
    vector<int> seen(256, -1);

    for (int i = 0; i < s.size(); i++) {
        if (seen[s[i]] != -1) {
            // we have seen this before
            for (; left < i; left++) {
                seen[s[left]] = -1;
                curr--;
            }
        }
        seen[s[i]] = i;
        curr++;
        best = max(best, curr);
    }
    return best;
}