#include "BinarySearchTree.cpp"

/*
	Implementation of a red-black tree: a type of binary search tree that rotates (balances) to maintain O(lgn) height
*/

template <typename T>
class RedBlackTreeNode: public TreeNode<T> {
	// in addition to item, parent, left, right subtrees, our node has a binary "color"
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
		this->size = 1;
	}

	/*
		Inserting an element into a red black tree, we may need to rotate the tree to maintain a balanced height
		element is the item to insert
	*/
	void insertNode(T element) {
		
	}
	
	/*
		Inserting an element into a red black tree, we may need to rotate the tree to maintain a balanced height
		element is the item in the tree to delete
		If the item does not exist, an exception is thrown
	*/
	void deleteNode(T element) {

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