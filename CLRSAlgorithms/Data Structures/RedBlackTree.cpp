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

	// helper method for deletion
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
	*/
	void redBlackDeleteFixUp(RedBlackTreeNode<T>* node) {
		// note that the sibling of this node cannot be nullptr due to red black tree properties
		while (root != node && node->color) {
			if (node == node->parent->left) {
				// node is the left child of its parent
				RedBlackTreeNode<T>* sibling = node->parent->right;
				if (!sibling->color) {
					// sibling is red
					sibling->color = true;
					node->parent->color = false;
					leftRotate(node->parent);
					sibling = node->parent->right;
				}
				
				if ((sibling->left == nullptr || sibling->left->color) && (sibling->right == nullptr && sibling->right->color)) {
					sibling->color = false;
					node = node->parent;
				}
				else {
					if (sibling->right == nullptr || sibling->right->color) {
						sibling->left->color = false;
						sibling->color = true;
						rightRotate(sibling);
						sibling = node->parent->right;
					}
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
					sibling->color = true;
					node->parent->color = false;
					leftRotate(node->parent);
					sibling = node->parent->right;
				}
				
				if ((sibling->left == nullptr || sibling->left->color) && (sibling->right == nullptr && sibling->right->color)) {
					sibling->color = false;
					node = node->parent;
				}
				else {
					if (sibling->right == nullptr || sibling->right->color) {
						sibling->left->color = false;
						sibling->color = true;
						rightRotate(sibling);
						sibling = node->parent->right;
					}
					sibling->color = node->parent->color;
					node->parent->color = true;
					if (sibling->right != nullptr) sibling->right->color = true;
					leftRotate(node->parent);
					node = root;
				}
			}
		}
		
		// the root should be black
		if (node!=nullptr) node->color = true;
	}

	/*
		Method that restores red black properties if needed after an insert
	*/
	void redBlackInsertFixUp(RedBlackTreeNode<T>* node) {
		// the root is black (True) so we are guaranteed to terminate
		// when we enter the loop, the parent must be red (False) so we know that node->parent->parent exists (not null)
		while (!node->parent->color) {
			if (node->parent == node->parent->parent->left) {
				RedBlackTreeNode<T>* uncle = node->parent->parent->right;
				if (!uncle->color) {
					//uncle is red
					node->parent->color = true;
					uncle->color = true;
					node->parent->parent->color = false;
					node = node->parent->parent;
				}
				else {
					// uncle is black
					if (node == node->parent->right) {
						// this node is its parents right child
						node = node->parent;
						leftRotate(node);
					}
					node->parent->color = true;
					node->parent->parent->color = false;
					rightRotate(node->parent->parent);
				}
			}
			else {
				RedBlackTreeNode<T>* uncle = node->parent->parent->left;
				if (!uncle->color) {
					//uncle is red
					node->parent->color = true;
					uncle->color = true;
					node->parent->parent->color = false;
					node = node->parent->parent;
				}
				else {
					// uncle is black
					if (node == node->parent->left) {
						// this node is its parents right child
						node = node->parent;
						rightRotate(node);
					}
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
}