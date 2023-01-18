#include <vector>
#include "LinkedList.cpp"
#include <functional>

/*
	Implementing various hash tables and hashing structures described in LCRS textbook
*/

/*
	Class to represent the direct addressing table, represented by an array
	This is a very simple class that takes key value pairs of integers and stores them with basic set methods
*/
class DirectAddressTable {

	// table of keys for each value
	std::vector<int> table;

	// array that stores the validity of each index
	// ideally, we can save some space by using a bitmap here (setting bits in chars), but we wont do that since this is a simple example
	std::vector<bool> tableValidity;

public:
	DirectAddressTable(int universeSize) {
		table = std::vector<int>(universeSize);
		tableValidity = std::vector<int>(universeSize, false);
	}

	// returns the value associated with the integer key or throws key not found exception
	int searchEntry(int key) {
		if (tableValidity[key]) {
			return table[key];
		}
		else {
			throw "Key Not Found Exception";
		}
	}

	// we do not care about collisions here, we just insert the key value pair into the table
	void insertEntry(std::pair<int,int> keyVal) {
		table[keyVal.first] = keyVal.second;
		tableValidity[keyVal.first] = true;
	}

	void deleteEntry(int key) {
		// just set the validity to false
		tableValidity[key] = false;
	}
};


/*
	Our first hash table class
	We will use chaining to address the collision issue (where two keys hash to the same integer index)
	Chaining will use the linked list underlying structure for O(1) chaining
*/
template <typename K,typename T>
class HashTable {
	// the table is just an array of linked lists where the index is the hash of the key
	// we use a doubly linked list just for faster deletion
	std::vector<DoublyLinkedList<T>*> table;

	// we need a hash function that takes a key and returns an integer
	std::function<int(K)> hashFunction;

public:
	HashTable(int universeSize) {
		table = std::vector<LinkedList<T>*>(universeSize, nullptr);
	}

	T searchEntry(K key) {
		int hashValue = hashFunction(key);
		if (table[hashValue] != nullptr) {
			// for our purposes we return the first element in the linked list with this key
			return table[hashValue]->head->item;
		}
		else {
			throw "Key Not Found Exception";
		}
	}

	void insertEntry(std::pair<K, T> entry) {
		int hashValue = hashFunction(entry.first);
		DoublyLinkedListNode<T> toInsert = DoublyLinkedListNode(entry.second);
		if (table[hashValue] == nullptr) {
			// need to initialize the list
			table[hashValue] = new DoublyLinkedList<T>(toInsert);
		}
		else {
			table[hashValue]->insert(toInsert);
		}
	}

	void deleteEntry(std::pair<K, T> entry) {
		int hashValue = hashFunction(entry.first);
		if (table[hashValue] != nullptr) {
			table[hashValue]->eraseByEntry(entry.second);
		}
		else {
			throw "Entry Not Found Exception";
		}
	}
};

// we may use universal hashing to reduce the number of collision and provide better average performance
// universal hashing is the practice of choosing randomly from a set of hashing functions instead of relying on a single hash function
// this is provided as a theoretical defense against an adversary who knows exactly which hash function you are using

// we just require that our universal hash functions satisfy some probabilistic guarantees:
// we need the probability of collisions to be less than 1/m, where m is the number of slots in the table


