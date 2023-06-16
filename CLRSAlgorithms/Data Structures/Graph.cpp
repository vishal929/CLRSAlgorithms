/*
	Defining various graph representations and some standard operations we can do on them
*/

#include "LinkedList.cpp"
#include <vector>


/*
	A graph based on an adjacency list is represented by a list of linked lists of edges
	I.E node 0 is indexed by the first entry of the list and the linked list holds pointers to the other neighbors of node 0
*/
template<typename T>
class ListGraph {

public:
	// our adjacency list
	// index 0 holds the list of indices of nodes connected to this one
	std::vector<LinkedList<int>*> adjList;

	// our nodes (index 0 is the value of node 0)
	std::vector<T> nodes;
	
	// constructer given an existing adjacency List and existing node values
	ListGraph(std::vector < LinkedList<int>* adjList, std::vector<T> nodeValues) {
		this->adjList = adjList;
		this->nodes = nodeValues;
	}
	
	//  adding a vertex to our graph with a specific value
	void addVertex(T nodeValue) {
		nodes.push_back(nodeValue);
	}
	
	// inserts the edge (vertexOne, vertexTwo) into the adjacency list of vertexOne
	void addEdge(int vertexOne, int vertexTwo) {
		adjList[vertexOne]->insert(vertexTwo, 0);
	}

};


/*
	A graph based on an adjacency matrix
	This means we have an n x n matrix where if node i is adjacent to node j, then entry i,j will be 1 and if otherwise, then 0
*/
template<typename T>
class MatrixGraph {

public:
	// our adjacency matrix
	std::vector<std::vector<int>> adjMatrix;

	// our node values (i.e index 0 holds the value of node 0)
	std::vector<T> nodes;

	// constructor given existing adjacency matrix and existing node values
	MatrixGraph(std::vector<std::vector<int>> adjMatrix, std::vector<T> nodeValues) {
		this->adjMatrix = adjMatrix;
		this->nodes = nodeValues;
	}
	
	// adds a vertex to our graph with a specific value
	void addVertex(T nodeValue) {
		nodes.push_back(nodeValue);

		// need to expand our adjacency matrix also
		adjMatrix.push_back(std::vector<int>());
	}
	
	// inserts the edge (vertexOne, vertexTwo) into our adjacency matrix
	void addEdge(int vertexOne, int vertexTwo) {
		adjMatrix[vertexOne][vertexTwo] = 1;
	}
};