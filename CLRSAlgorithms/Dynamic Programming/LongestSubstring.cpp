#include <string>
#include <set>

/*
    We find the length of the longest substring of s (substring is a contiguous portion of a string, NOT a subsequence)
    s: input string
*/
int lengthOfLongestSubstring(string s) {
    // M(i,j+1) is M(i,j)+1 if s[j+1] is not in M(i,j), and 0 otherwise 

    int longest = 0;
    set<char> seen;
    for (int i = 0; i < s.size(); i++) {
        // longest so far is just 1 (s[i])
        seen.insert(s[i]);
        longest = max(longest,1)
        for (int j = i + 1; j < s.size(); j++) {
            if (seen.find(s[j]) == seen.end()) {
                seen.insert(s[j]);
                if (longest < seen.size()) {
                    longest = seen.size();
                }
            }
            else {
                break;
            }
        }

        if (longest < seen.size()) {
            longest = seen.size();
        }
        seen.clear();
    }
    return longest;
}