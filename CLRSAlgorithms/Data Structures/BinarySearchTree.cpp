#include <vector>
/*
	Node class to be used in the binary search tree
*/
template <typename T>
class TreeNode {
	T item;
	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode<T>* parent;

public:
	TreeNode(T item) {
		this->item = item;
		left, right, parent = nullptr;
	}
};


template <typename T>
class BinarySearchTree {

	// root of tree
	TreeNode<T>* root;

	// number of elements in the binary search tree
	int size;

public:
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
				if (runner->left == nullptr) {
					// we found the place to insert
					runner->left = toInsert;
					return;
				}
				runner = runner->left;
			}
			else {
				if (runner->right == nullptr) {
					// we found the insertion point
					runner->right = toInsert;
					return;
				}
				runner = runner->right;
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
	
	// inorder traversal visits the left subtree, the root, and then the right subtree
	static void inorderTraversal(TreeNode<T>* root) {
		if (root != nullptr) {
			inorderTraversal(root->left);
			cout << root->item;
			inorderTraversal(root->right);
		}
	}

	// postorder traversal visits the left subtree, the right subtree, and then the root
	static void postorderTraversal(TreeNode<T>* root) {
		if (root != nullptr) {
			inorderTraversal(root->left);
			inorderTraversal(root->right);
			cout << root->item;
		}
	}
	
	// preorder traversal visits the root, then the left subtree, then the right subtree
	static void preorderTraversal(TreeNode<T>* root) {
		if (root != nullptr) {
			cout << root->item;
			inorderTraversal(root->left);
			inorderTraversal(root->right);
		}
	}
};

