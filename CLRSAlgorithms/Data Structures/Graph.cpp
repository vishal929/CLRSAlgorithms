/*
	Defining various graph representations and some standard operations we can do on them
	We will define all our graphs as directed as undirected graphs are just special cases of them
*/

#include "LinkedList.cpp"
#include <vector>


/*
	A weighted graph based on an adjacency list is represented by a list of linked lists of edges
	I.E node 0 is indexed by the first entry of the list and the linked list holds pointers to the other neighbors of node 0
*/
template<typename T>
class WeightedListGraph {

public:
	// our adjacency list
	// index 0 holds the list of indices of nodes connected to this one
	// the first item in the pair is the vertex index and the second item in the pair is the edge weight
	std::vector<LinkedList<std::pair<int,float>>*> adjList;

	// our nodes (index 0 is the value of node 0)
	std::vector<T> nodes;
	
	// constructer given an existing adjacency List and existing node values
	ListGraph(std::vector < LinkedList<std::pair<int,float>>* adjList, std::vector<T> nodeValues) {
		this->adjList = adjList;
		this->nodes = nodeValues;
	}
	
	//  adding a vertex to our graph with a specific value
	void addVertex(T nodeValue) {
		nodes.push_back(nodeValue);
	}
	
	// inserts the edge (vertexOne, vertexTwo) into the adjacency list of vertexOne with a given weight
	void addEdge(int vertexOne, int vertexTwo, float weight) {
		adjList[vertexOne]->insert(make_pair(vertexTwo,weight), 0);
	}

};

// an unweighted graph is just a special case of a weighted graph with weight 1
// we will do this just to make our life easier, but we would need to implement differently if space was a huge concern
template<typename T>
class ListGraph(WeightedListGraph) {
public:
	
	// overloading addEdge with the unweighted version
	void addEdge(int vertexOne, int vertexTwo) {
		adjList[vertexOne]->insert(make_pair(vertexTwo,1), 0);
	}
}


/*
	A weighted graph based on an adjacency matrix
	This means we have an n x n matrix where if node i is adjacent to node j, then entry i,j will be the weight and if otherwise, then 0
*/
template<typename T>
class WeightedMatrixGraph {

public:
	// our adjacency matrix of weights
	std::vector<std::vector<float>> adjMatrix;

	// our node values (i.e index 0 holds the value of node 0)
	std::vector<T> nodes;

	// constructor given existing adjacency matrix and existing node values
	MatrixGraph(std::vector<std::vector<float>> adjMatrix, std::vector<T> nodeValues) {
		this->adjMatrix = adjMatrix;
		this->nodes = nodeValues;
	}
	
	// adds a vertex to our graph with a specific value
	void addVertex(T nodeValue) {
		nodes.push_back(nodeValue);

		// need to expand our adjacency matrix also
		adjMatrix.push_back(std::vector<float>());
	}
	
	// inserts the edge (vertexOne, vertexTwo) into our adjacency matrix with a specific weight
	void addEdge(int vertexOne, int vertexTwo, float weight) {
		adjMatrix[vertexOne][vertexTwo] = weight;
	}
};

/*
	An unweighted matrix graph is just a special case of the weighted graph with weights=1
*/
template<typename T>
class MatrixGraph(WeightedMatrixGraph) {
public:
	
	// overloading the weighted version of addEdge with the unweighted version here
	void addEdge(int vertexOne, int vertexTwo) {
		adjMatrix[vertexOne][vertexTwo] = 1;
	}
}