#include "../Data Structures/BinarySearchTree.cpp"
#include <vector>
#include <stack>

/*
	We can use dynamic programming to construct an optimal binary search tree given keys and probabilities for each key being searched
	The optimal binary search tree minimizes the expected searching cost for all keys in the tree
	keys is the data that should be present within nodes in our tree. These keys are SORTED in ascending order
	probs is the probability of each key being searched (i.e probs[i] is the probability of keys[i] being searched)
	dummyProbs is the probability of increasing key miss 
		(i.e dummyProbs[0] is the probability of searching for key less than keys[0] 
		and dummyProbs[i] 0<i<n is prob of searching for key greater than keys[i-1] but less than keys[i]
		and dummyProbs[n] is the probability of searching for key greater than keys[n-1])
	We return the cost of the binary tree and the split matrix (which can be used to construct the BST)
*/
std::pair<float,std::vector<std::vector<int>>> constructOptimalBST(std::vector<int> keys,  std::vector<float> probs,
	std::vector<float> dummyProbs) {
	using namespace std;
	// this is similar to the optimal matrix chain multiplication problem
	// for each set of keys k_i to k_j, we are picking a split where k_i <= k_r <= k_j is the root of the constructed binary tree
	
	// let M[i,j] = cost of optimal bst containing keys k_i to k_j
	// let root[i,j] = idx of the key chosen as the root for this subtree
	// substructure update:
	/*
		M[i,j] = min_(i<=k<=j) {
					M[i,k-1] + M[k+1,j] + sum of probabilities of dummys and keys from i to j					
				}
				or dummyProbs[i] if j==i-1 (no keys, just an empty tree basically)
	*/
	vector<vector<float>> M(keys.size()+1, vector<float>(keys.size()+1,0));
	// keeping track of the root at each step
	vector<vector<int>>root(keys.size()+1, vector<int>(keys.size()+1,-1));
	// sum(i,j) is the sum of probabilities of key hits and misses from k_i to k_j ( we will need this for the update)
	vector<vector<float>> Sum(keys.size()+1, vector<float>(keys.size()+1,0));
	for (int i = 1; i <= keys.size(); i++) {
		Sum[i][i-1] = dummyProbs[i - 1];
		M[i][i-1] = dummyProbs[i - 1];
		double runningSum = probs[i];
		for (int j = i ; j <= keys.size(); j++) {
			// probability of hit and miss
			Sum[i][j] = Sum[i][j - 1] + probs[i-1] + dummyProbs[i];
		}
	}

	// dp update:
	for (int l = 1; l <= keys.size(); l++) {
		for (int i = 1; i <= keys.size()-l+1; i++) {
			int j = i + l - 1;
			M[i][j] = FLT_MAX;
			for (int k = i; k <= j; k++) {
				float proposedCost = M[i][k - 1] + Sum[i][j] + M[i][k + 1];
				if (proposedCost < M[i][j]) {
					M[i][j] = proposedCost;
					// saving the split
					root[i][j] = k;
				}
			}
		}
	}

	return make_pair(M[1][keys.size()], root);
}

/*
	Building a binary search tree from the saved roots of the optimal BST algorithm
	keys is the vector of keys to be inserted into the binary search tree for searching
	roots are the splits for the optimal binary search tree obtained from the constructOptimalBST routine
	We return a Binary Search Tree Object with the keys inserted
*/
BinarySearchTree<int>* buildTree(std::vector<int> keys, std::vector<std::vector<int>> roots) {
	using namespace std;
	BinarySearchTree<int>* bst = new BinarySearchTree<int>();
	// we can use a stack to build the tree
	stack<pair<int,int>> s;
	// need to keep track of treenode objects to add to and on which subtree (left = false, right=true)
	stack<pair<TreeNode<int>*,bool>> nodeS;
	if (keys.size() > 0) {
		// only do this if we have things to put in the tree
		// push the first split to the stack
		s.push(make_pair(1, keys.size()));
		nodeS.push(make_pair(nullptr,false));
	}

	while (s.size() > 0) {
		int low = s.top().first;
		int high = s.top().second;
		int splitIdx = roots[low][high];
		s.pop();
		TreeNode<int>* parent = nodeS.top().first;
		bool right = nodeS.top().second;
		nodeS.pop();
		TreeNode<int>* newNode = new TreeNode<int>(keys[splitIdx]);
		if (parent == nullptr) {
			// this node is the root
			bst->root = newNode;
		}
		else {
			// we either place this node on the left subtree of the parent or on the right subtree
			right ? parent->right = newNode : parent->left = newNode;
		}
		// we expanding subtrees via the stack
		if (low != high) {
			// right subtree
			nodeS.push(make_pair(newNode, true));
			s.push(make_pair(splitIdx + 1, high));
			// left subtree
			nodeS.push(make_pair(newNode, false));
			s.push(make_pair(low, splitIdx - 1));
		}
			
	}

	return bst;
	
}