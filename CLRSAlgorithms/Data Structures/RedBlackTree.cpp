#include "BinarySearchTree.cpp"

/*
	Implementation of a red-black tree: a type of binary search tree that rotates (balances) to maintain O(lgn) height
*/

template <typename T>
class RedBlackTreeNode: public TreeNode<T> {
	// in addition to item, parent, left, right subtrees, our node has a binary "color"
	// false is red, true is black
	bool color;
public:
	RedBlackTreeNode(T item): TreeNode(T item) {
		color = false;
	}
};

/*
	A red black tree has the following rules:
	1) Every node is either red or black 
	2) The root is black
	3) The leaves as null pointers are black
	4) If a node is red, then its children are black
	5) For each node, the path to leaves contain the same number of black nodes (does not include the node itself)
*/
template <typename T>
class RedBlackTree: public BinarySearchTree<T> {

public:

	RedBlackTree() : BinarySearchTree() {

	}

	// adjusting the constructor for root to be a RedBlackTreeNode (a derived class of TreeNode) at runtime!
	// this is so we can make use of polymorphism from the binary search tree base class and not have to implement those methods again :)
	RedBlackTree(RedBlackTreeNode* root) {
		this->root = root;
		// must ensure that the root is black
		this->root->color = true;
		this->size = 1;
	}

	/*
		Inserting an element into a red black tree, we may need to rotate the tree to maintain a balanced height
		element is the item to insert
	*/
	void insertNode(T element) {
		RedBlackTreeNode<T>* toInsert = new RedBlackTreeNode(element);
		RedBlackTreeNode<T>* start = root;

		if (start == nullptr) {
			root = toInsert;
			// the root must be black
			root->color = true;
			size++;
			// no need to rotate in this case
			return;
		}
		
		RedBlackTreeNode<T>* par = nullptr;
		while (start != nullptr) {
			if (start->item < element) {
				start = start->right;
			}
			else {
				start = start->left;
			}
		}
		
		if (par->item < element) {
			par->right = toInsert;
		}
		else {
			par->left = toInsert;
		}
		toInsert->parent = par;

		size++;

		// need to check if rotations/recoloring needs to be made up the binary tree
		redBlackInsertFixUp(toInsert);
	}

	// helper method for deletion for swapping positions of nodes
	void redBlackTransplant(RedBlackTreeNode<T>* u, RedBlackTreeNode<T>* v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}
	
	/*
		Inserting an element into a red black tree, we may need to rotate the tree to maintain a balanced height
		element is the item in the tree to delete
		If the item does not exist, an exception is thrown
	*/
	void deleteNode(T element) {
		RedBlackTreeNode<T>* toDelete = search(element);
		RedBlackTreeNode<T>* toFixup = toDelete;
		bool origColor = toDelete->color;
		
		if (toDelete->left == nullptr) {
			toFixup = toDelete->right;
			redBlackTransplant(toDelete, toDelete->right);
		}
		else if (toDelete->right == nullptr) {
			toFixup = toDelete->left;
			redBlackTransplant(toDelete, toDelete->left);
		}
		else {
			// getting minimum node in right subtree
			toFixup = toDelete->right;
			while (toFixup->left != nullptr) toFixup = toFixup->left;
			origColor = toFixup->color;

			RedBlackTreeNode<T>* right = toFixup->right;

			if (toFixup->parent == toDelete && right!=nullptr) {
				right->parent = toFixup;
			}
			else if (right != nullptr) {
				redBlackTransplant(toFixup, right);
				toFixup->right = toDelete->right;
				toFixup->right->parent = toFixup;
			}

			redBlackTransplant(toDelete, toFixup);
			toFixup->left = toDelete->left;
			if (toFixup->left != nullptr) toFixup->left->parent = toFixup;
			toFixup->color = toDelete->color;
			
			// need to adjust the fixup node
			toFixup = right;
		}

		if (origColor) redBlackDeleteFixUp(toFixup);
	}

	/*
		Method that restores red black properties if needed after a deletion
		We have 8 cases, where 4 cases are for fixing on one side of the tree, and the other 4 are symmetric for the other side
		The below 4 cases are for fixing along a node who is the left child of its parent
		1) The nodes sibling is red
		2) The nodes sibling is black and both of the siblings children are black
		3) The nodes sibling is black and its left child is red and right child is black
		4) The nodes sibling is black and its right child is red
		The below 4 cases are for fixing along a node who is the right child of its parent
		5) the nodes sibling is red
		6) the nodes sibling is black and both of the siblings children are black
		7) the nodes sibling is black and its left child is black and right child is red
		8) the nodes sibling is black and its left child is red
	*/
	void redBlackDeleteFixUp(RedBlackTreeNode<T>* node) {
		// note that the sibling of this node cannot be nullptr due to red black tree properties
		while (root != node && node->color) {
			if (node == node->parent->left) {
				// node is the left child of its parent
				RedBlackTreeNode<T>* sibling = node->parent->right;
				if (!sibling->color) {
					// transforming case 1 to some other case of 2,3,4
					// sibling is red
					sibling->color = true;
					node->parent->color = false;
					leftRotate(node->parent);
					sibling = node->parent->right;
				}
				
				if ((sibling->left == nullptr || sibling->left->color) && (sibling->right == nullptr && sibling->right->color)) {
					// case 2 
					sibling->color = false;
					node = node->parent;
				}
				else {
					if (sibling->right == nullptr || sibling->right->color) {
						// case 3 to case 4 transformation
						sibling->left->color = true;
						sibling->color = false;
						rightRotate(sibling);
						sibling = node->parent->right;
					}
					// handling case 4
					sibling->color = node->parent->color;
					node->parent->color = true;
					if (sibling->right != nullptr) sibling->right->color = true;
					leftRotate(node->parent);
					node = root;
				}
			}
			else {
				// node is the right child of its parent
				RedBlackTreeNode<T>* sibling = node->parent->left;
				if (!sibling->color) {
					// sibling is red

					// transforming case 5 to any of case 6,7,8
					sibling->color = true;
					node->parent->color = false;
					leftRotate(node->parent);
					sibling = node->parent->left;
				}
				
				if ((sibling->left == nullptr || sibling->left->color) && (sibling->right == nullptr && sibling->right->color)) {
					// handling case 6
					sibling->color = false;
					node = node->parent;
				}
				else {
					if (sibling->left == nullptr || sibling->left->color) {
						// transforming case 7 to case 8
						sibling->right->color = true;
						sibling->color = false;
						leftRotate(sibling);
						sibling = node->parent->left;
					}

					// handling case 8
					sibling->color = node->parent->color;
					node->parent->color = true;
					if (sibling->left != nullptr) sibling->left->color = true;
					rightRotate(node->parent);
					node = root;
				}
			}
		}
		
		// the root should be black
		if (node!=nullptr) node->color = true;
	}

	/*
		Method that restores red black properties if needed after an insert
		// we have 6 cases of which 3 are for fixing along one side of the tree and 3 are symmetric for the other side
		// the below 3 cases are when the nodes parent is the node's grandparents left child
		1) the node's uncle is red
		2) The node's uncle is black and the node is a right child of its parent
		3) The node's uncle is black and the node is a left child of its parent
		// the below 3 cases are when the nodes parent is the node's grandparent's right child
		4) The node's uncle is red
		5) The node's uncle is black and the node is a left child of its parent
		6) the node's uncle is black and the node is a right child of its parent
	*/
	void redBlackInsertFixUp(RedBlackTreeNode<T>* node) {
		// the root is black (True) so we are guaranteed to terminate
		// when we enter the loop, the parent must be red (False) so we know that node->parent->parent exists (not null)
		while (!node->parent->color) {
			if (node->parent == node->parent->parent->left) {
				RedBlackTreeNode<T>* uncle = node->parent->parent->right;
				if (!uncle->color) {
					// case 1
					//uncle is red
					node->parent->color = true;
					uncle->color = true;
					node->parent->parent->color = false;
					node = node->parent->parent;
				}
				else {
					// uncle is black
					if (node == node->parent->right) {
						// transforming case 2 to case 3
						// this node is its parents right child
						node = node->parent;
						leftRotate(node);
					}
					// handling case 3
					node->parent->color = true;
					node->parent->parent->color = false;
					rightRotate(node->parent->parent);
				}
			}
			else {
				RedBlackTreeNode<T>* uncle = node->parent->parent->left;
				if (!uncle->color) {
					// case 4
					//uncle is red
					node->parent->color = true;
					uncle->color = true;
					node->parent->parent->color = false;
					node = node->parent->parent;
				}
				else {
					// uncle is black
					if (node == node->parent->left) {
						// transforming case 5 to case 6
						// this node is its parents right child
						node = node->parent;
						rightRotate(node);
					}
					// handling case 6
					node->parent->color = true;
					node->parent->parent->color = false;
					leftRotate(node->parent->parent);
				}
			}
		}
		//the root should be black
		if (root != nullptr) root->color = true;
	}
	
	/*
		Performing a left rotation on a given node to balance the tree
		Left rotation on a node assumes that the node has a right child (non null)
	*/
	void leftRotate(RedBlackTreeNode<T>* node) {
		RedBlackTreeNode<T>* par = node->parent;
		RedBlackTreeNode<T>* rightChild = node->right;
		RedBlackTreeNode<T>* childLeft = rightChild->left;

		// setting the nodes right subtree to its rightchild's left subtree
		node->right = rightChild->left;
		if (rightChild->left != nullptr) rightChild->left->parent = node;

		// setting the nodes childs new left subtree to the node itself
		rightChild->left = node;

		// replacing node with its rightchild with respect to the parent
		if (par == nullptr) {
			head = rightChild;
			
		}
		else if (par->left == node) {
			par->left = rightChild;
		}
		else {
			par->right = rightChild;
		}
		// adjusting parent pointers
		rightChild->parent = par;
		node->parent = rightChild;
	}
	
	/*
		Performing a right rotation on a given node to balance the tree
		Right rotation on a node assumes it has a left child (not null)
	*/
	void rightRotate(RedBlackTreeNode* node) {
		RedBlackTreeNode<T>* par = node->parent;
		RedBlackTreeNode<T>* leftChild = node->left;
		RedBlackTreeNode<T>* childRight = leftChild->right;

		// setting the nodes left subtree to its leftchilds's right subtree
		node->left = leftChild->right;
		if (leftChild->right != nullptr) leftChild->right->parent = node;

		// setting the nodes childs new right subtree to the node itself
		leftChild->right = node;

		// replacing node with its rightchild with respect to the parent
		if (par == nullptr) {
			head = leftChild;
			
		}
		else if (par->left == node) {
			par->left = leftChild;
		}
		else {
			par->right = leftChild;
		}
		// adjusting parent pointers
		leftChild->parent = par;
		node->parent = leftChild;		
	}
	
	/*
		Function that calculates the black height of a node: the number of black nodes on any simple path from this node to a leaf 
		This function is defined recursively
	*/
	static int blackHeight(RedBlackTreeNode<T>* node) {
		if (node == nullptr) {
			// leaves are null, so this is a black node
			return 1;
		}
		else {
			int inclusive = 0;
			// need to include this node in the count if it is black
			if (node->color) inclusive++;

			// by property 5 mentioned in the comment of the assertValid function, 
			// the blackheight of the left subtree equals the blackheight of the right subtree, so we do not need to check both
			return inclusive + blackHeight(node->left);
		}
	}

	/*
		Helper function that returns true if property 5 detailed in comments of the assertValid function is satisfied and false otherwise
		So, we find a single path to a leaf first, and then check if every other path has the same number of black nodes
		We can run dfs in O(n) time to get bhOnASinglePath and then verify with this method
	*/
	bool blackHeightChecker(BlackTreeNode<T>* node, int bhOnASinglePath, int bhSoFar) {
		if (node == nullptr) {
			if (bhSoFar + 1 == bhOnASinglePath) {
				return true;
			}
			return false;
		}
		
		// need to increment bhSoFar if this node is black
		if (node->color) bhSoFar++;
		return blackHeightChecker(node->left, bhOnASinglePath, bhSoFar) && blackHeightChecker(node->right, bhOnASinglePath, bhSoFar);
	}
	
	/*
		Function that returns true if this tree satisfies every rule of red black trees
		The function returns false if any rule is not satisfied
		The 5 rules are given below:
		1) Every node is either red or black
		2) The root is black
		3) Every leaf (null child) is black
		4) If a node is red, then its children are black
		5) For each node, every simple path from the node to a descendent leaf contains the same number of black nodes
	*/
	bool assertValid(RedBlackTreeNode<T>* node) {
		if (node == nullptr) return true;

		if (node == root && !node->color) {
			// the root is not black, violation of rule 2
			return false;
		}

		if (!node->color && ((node->left != nullptr && !node->left->color) || (node->right != nullptr && !node->right->color))) {
			// then this node is red, but one of its children is not black
			// violation of rule 4
			return false;
		}
		
		int bh = blackHeight(node);
		if (!blackHeightChecker(node,bh,0) {
			// violation of rule 5
			return false;
		}
		
		bool leftCheck = assertValid(node->left);
		bool rightCheck = assertValid(node->right);
	}
}