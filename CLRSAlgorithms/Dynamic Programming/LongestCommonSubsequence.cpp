#include <string>
#include <vector>
#include <stack>
#include <algorithm>

/*
	Given 2 strings, return the string which represents the longest common subsequence
	s1: the first string
	s2: the second string
*/
std::string LCS(std::string &s1, std::string &s2) {
	using namespace std;
	/*
		Problem Definition:
			M[i,j]=longest common subsequence of s1[0..i] and s2[0..j]
		Initial Cases:
			M[i,-1] = 0 (no second string)
			M[-1,j] = 0 (no first string)
		Substructure Update:
			M[i,j] = M[i-1,j-1] + 1 if s1[i]==s2[j]
			else max {
				M[i-1,j],
				M[i,j-1]
			}
		Rebuilding Solution:
			We just need to determine where M[n,m] came from in the substructure update, and then we can recursively build the solution!
	*/
	
	// 1+len(s1) x 1+len(s2) matrix M (we will use 1-indexes for better initial case clarity)
	vector<vector<int>> M(1+s1.size(), vector<int>(1+s2.size(), 0));
	
	// initial cases
	for (int i = 0; i < s1.size(); i++) {
		M[i][0] = 0;
	}
	for (int j = 0; j < s2.size(); j++) {
		M[0][j] = 0;
	}
	
	// substructure update
	for (int i = 1; i < s1.size()+1; i++) {
		for (int j = 1; j < s2.size()+1; j++) {
			if (s1[i - 1] == s2[j - 1]) {
				M[i][j] = 1 + M[i - 1][j - 1];
			}
			else {
				M[i][j] = max(M[i - 1][j], M[i][j - 1]);
			}
		}
	}

	// recovering the solution
	stack<char> reverse_sol;
	stack<pair<int, int>> s;
	s.push(make_pair(s1.size(), s2.size()));
	while (s.size() > 0) {
		pair<int, int> pos = s.top();
		s.pop();

		int i = pos.first, int j = pos.second;
		if (s1[i - 1] == s2[j - 1]) {
			// recurse at i-1,j-1 and update solution
			s.push(make_pair(i - 1, j - 1));
			reverse_sol.push(s1[i - 1]);
		}
		else {
			// recurse at the better pathway
			if (M[i - 1][j] > M[i][j - 1]) {
				s.push(make_pair(i - 1, j));
			}
			else {
				s.push(make_pair(i, j - 1));
			}
		}
	}

	// stack is the string in reversed order, so we just reverse and return!
	string sol;
	while (reverse_sol.size() > 0) {
		sol.push_back(reverse_sol.top());
		reverse_sol.pop();
	}

	return sol;
}

/*
	Finds the longest monotonically increasing subsequence
	nums is an array of integers
*/
std::vector<int> LMIS(std::vector<int> &nums) {
	using namespace std;
	// sort a copy of the array in O(nlgn)
	vector<int> cop(nums);
	sort(cop.begin(), cop.end());

	// key idea: the longest monotonically increasing subsequence must be present in the sorted list!
	// so, we just use LCS and reconstruct the solution
	vector<vector<int>> M(nums.size()+1, vector<int>(nums.size()+1, 0));
	
	// substructure update
	for (int i = 1; i < nums.size()+1; i++) {
		for (int j = 1; j < nums.size()+1; j++) {
			if (nums[i - 1] == cop[j - 1]) {
				M[i][j] = 1 + M[i - 1][j - 1];
			}
			else {
				M[i][j] = max(M[i - 1][j], M[i][j - 1]);
			}
		}
	}

	// recovering the solution
	stack<int> reverse_sol;
	stack<pair<int, int>> s;
	s.push(make_pair(nums.size(), nums.size()));
	while (s.size() > 0) {
		pair<int, int> pos = s.top();
		s.pop();

		int i = pos.first, int j = pos.second;
		if (nums[i - 1] == cop[j - 1]) {
			// recurse at i-1,j-1 and update solution
			s.push(make_pair(i - 1, j - 1));
			reverse_sol.push(nums[i - 1]);
		}
		else {
			// recurse at the better pathway
			if (M[i - 1][j] > M[i][j - 1]) {
				s.push(make_pair(i - 1, j));
			}
			else {
				s.push(make_pair(i, j - 1));
			}
		}
	}

	// stack is the string in reversed order, so we just reverse and return!
	vector<int> sol;
	while (reverse_sol.size() > 0) {
		sol.push_back(reverse_sol.top());
		reverse_sol.pop();
	}

	return sol;
}
