#include <vector>
/*
	Node class to be used in the binary search tree
*/
template <typename T>
class TreeNode {
public:
	T item;
	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode<T>* parent;

	TreeNode(T item) {
		this->item = item;
		left, right, parent = nullptr;
	}

	// inorder traversal visits the left subtree, the root, and then the right subtree
	static void inorderTraversal(TreeNode<T>* root) {
		// stack instead of recursion
		forward_list stack;
		if (root != nullptr) stack.push_front(root);

		while (stack.size() > 0) {

		}
		if (root != nullptr) {
			inorderTraversal(root->left);
			cout << root->item;
			inorderTraversal(root->right);
		}
	}

	// postorder traversal visits the left subtree, the right subtree, and then the root
	static void postorderTraversalIterative(TreeNode<T>* root) {
		// using stack instead of recursion
		stack<TreeNode<T>*> s1;
		stack<TreeNode<T>*> s2;
		if (root != nullptr) s1.push(root);
		while (s1.size() > 0) {
			TreeNode<T>* node = s1.top();
			s1.pop();
			if (node->left != nullptr) s1.push(node->left);
			if (node->right != nullptr) s1.push(node->right);
			s2.push(node);
		}

		while (s2.size() > 0) {
			TreeNode<T>* node = s2.top();
			s2.pop();
			//TODO: implement generic function for visiting a node instead of printing

		}

	}

	static void postorderTraversal(TreeNode<T>* root) {
		if (root != nullptr) {
			postorderTraversal(root->left);
			postorderTraversal(root->right);
			// TODO: implement generic function for visiting a node instead of printing
			cout << root->item;
		}
	}
	
	// preorder traversal visits the root, then the left subtree, then the right subtree
	static void preorderTraversalIterative(TreeNode<T>* root) {
		// using stack instead of recursion
		forward_list<TreeNode<T>*> stack;
		if (root != nullptr) stack.push_front(root);
		while (stack.size() > 0) {
			TreeNode<T>* node = stack.front();
			stack.pop_front();

			// TODO: do node specific logic using generic function

			// pushing the right subtree then left subtree due to fifo
			if (node->right != nullptr) stack.push_front(node->right);
			if (node->left != nullptr) stack.push_front(node->left);
		}
		
	}

	static void preorderTraversal(TreeNode<T>* root) {
		if (root != nullptr) {
			// TODO: do node specific logic using generic function instead of print
			cout << root->item;
			inorderTraversal(root->left);
			inorderTraversal(root->right);
		}
	}
	
	// level traversal visits each depth separately (if space is a huuuge concern, we can visit nodes like in dfs and map output by depth)
	static void levelTraversal(TreeNode<T>* root) {
		vector<vector<TreeNode*>> levels;
		if (root != nullptr) {
			levels.push_back(vector<TreeNode*> first{ root });
		}
		
		// we only keep the last level and the new level to build in memory
		while (levels.size() > 0) {
			vector<TreeNode*> curr_level = levels.back();
			levels.pop_back();
			vector<TreeNode*> new_level;
			for (int i = 0; i < curr_level.size(); i++) {
				TreeNode* node = curr_level[i];

				// do node specific logic
				// TODO: add generic function here for node specific logic				

				// add children to the new level
				if (node->left != nullptr) new_level.push_back(node->left);
				if (node->right != nullptr) new_level.push_back(node->right);
			}
			if (new_level.size() > 0) levels.push_back(new_level);
		}
	}
};


template <typename T>
class BinarySearchTree {

public:
	// root of tree
	TreeNode<T>* root;

	// number of elements in the binary search tree
	int size;

	BinarySearchTree() {
		root = nullptr;
		size = 0;
	}

	BinarySearchTree(TreeNode<T>* root) {
		this->root = root;
		size = 1;
	}

	/*
		Search returns a pointer to the node containing the element if its in the tree
		If the element does not exist in the tree, we return a nullptr
	*/
	TreeNode<T>* search(T element) {

		TreeNode<T>* toSearch = root;
					
		while (toSearch!=nullptr && toSearch->item!=element) {
			toSearch = (toSearch->item) < element ? toSearch->left : toSearch->right;
		}

		return toSearch;
	}

	/*
		Inserting a node into a binary search tree
		T is the element to insert
	*/
	void insertNode(T element) {
		TreeNode<T>* toInsert = new TreeNode<T>(element);

		TreeNode<T>* runner = root;

		if (runner == nullptr) {
			// then the root is empty, this new node should become the root of the tree
			root = toInsert;
		}
		
		while (runner != nullptr) {
			if (runner->item < element) {
				if (runner->right == nullptr) {
					// we found the place to insert
					runner->right= toInsert;
					return;
				}
				runner = runner->right;
			}
			else {
				if (runner->left== nullptr) {
					// we found the insertion point
					runner->left= toInsert;
					return;
				}
				runner = runner->left;
			}
		}

		// increasing the size of the binary search tree
		size++;
	}
	
	/*
		Deleting a node from a binary search tree
		T is the element to delete
	*/
	void deleteNode(T element) {
		// we need to first search for the element to delete	
		TreeNode<T>* elementNode = this->search(element);
		if (elementNode == nullptr) {
			throw "Given element does not exist in binary search tree!";
		}

		/*
			3 cases for deletion:

			1) node to delete has no children -> delete the node and set parent to point to nullptr if necessary
			2) node to delete has 1 child -> delete the node and set the parent to that single child
			3) node to delete has 2 children -> delete the node and replace it with its successor
		*/

		if (elementNode->left == nullptr && elementNode->right == nullptr) {
			if (elementNode->parent == nullptr) {
				// then the element to delete is the root
				root = nullptr;
			}
			else if (elementNode->parent->left == elementNode) {
				// the element to delete is a left child of its parent
				elementNode->parent->left = nullptr;
			}
			else {
				// the element to delete is a right child of its parent
				elementNode->parent->right = nullptr;
			}	
			delete(elementNode);
		}
		else if (elementNode->left == nullptr || elementNode->right == nullptr) {
			// then one of the two subtrees of the element to delete is nonempty
			TreeNode<T>* nonemptyTree = (elementNode->left != nullptr) ? elementNode->left : elementNode->right;
			if (elementNode->parent == nullptr) {
				// then the element to delete is the root
				root = nonemptyTree;
			}
			else if (elementNode->parent->left == elementNode) {
				// the element to delete is a left child of its parent
				elementNode->parent->left = nonemptyTree;
			}
			else {
				// the element to delete is a right child of its parent
				elementNode->parent->right = nonemptyTree;
			}

			delete(elementNode);
		}
		else {
			// then the element to delete has both subtrees nonempty -> replace with successor
			TreeNode<T>* succ = successor(elementNode);

			// since the node to delete has both subtrees, the successor of this node has no left subtree

			// we just exchange the values of the node to delete and the successor and then delete the successor with case 2
			elementNode->item = succ->item;

			// the element to delete is a left child of its parent
			succ->parent->left = succ->right;
			delete(succ);
		}
	}
	
	/*
		The predecessor of a node is the node of less than or equal value in the structure of the binary search tree
		If there is a left subtree, this is the rightmost leaf of the left subtree
		If there is no left subtree, we move up the parent hierarchy until we find a node whose right child is also an ancestor of the original root
		This method takes the root of the tree as an argument
		This method returns the node object if there is a predecessor, and nullptr otherwise
	*/
	static TreeNode<T>* predecessor(TreeNode<T>* root) {
		if (root == nullptr) return nullptr;

		TreeNode<T>* pred;
		if (root->left != nullptr) {
			pred = root->left;
			while (pred->right != nullptr) {
				pred = pred->right;
			}
			return pred;
		}
		else if (root->parent != nullptr) {
			pred = root->parent;
			while (pred->parent != nullptr) {
				TreeNode<T>* par = pred->parent;
				if (par->right == pred) {
					return par;
				}
				pred = par;
			}
		}
		
		// then our given node is the smallest node
		return nullptr;
		
	}
	
	/*
		The successor of a node is the node of greater than or equal value in the structure of the binary search tree
		If there is a right subtree, this is the leftmost leaf of the right subtree
		If there is no right subtree, we move up the parent hierarchy until we find a node whose left child is also an ancestor of the original root
		This method takes the root of the tree as an argument
		This method returns the node object if there is a successor , and nullptr otherwise
	*/
	static TreeNode<T>* successor(TreeNode<T>* root) {
		if (root == nullptr) return nullptr;

		TreeNode<T>* succ;
		if (root->right != nullptr) {
			succ = root->right;
			while (succ->left!= nullptr) {
				succ = succ->left;
			}
			return succ;
		}
		else if (root->parent != nullptr) {
			succ = root->parent;
			while (succ->parent != nullptr) {
				TreeNode<T>* par = succ->parent;
				if (par->left== succ) {
					return par;
				}
				succ = par;
			}
		}
		
		// then our node is the greatest node
		return nullptr;
	}
	

};

