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

template <typename T>
class RedBlackTree: public BinarySearchTree<T> {
	// overriding root with our redblacktreenode class (which extends the treenode class)
	RedBlackTreeNode<T>* root;

public:
	
	void insertNode(T element) {

	}

	void deleteNode(T element) {

	}
}