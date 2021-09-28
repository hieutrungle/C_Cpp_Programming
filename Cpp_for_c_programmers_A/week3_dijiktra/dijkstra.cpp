#include <iostream> // cout
#include <list>     // list container, doubly-linked list
#include <vector>   // vector container
#include<map>       // key-value container

using namespace std;

// INF is used to represent no edge/path between two nodes 
const int INF=999999;

// Convert node numbers into chars (from 0..51 to A..Za..z)
inline char int2char(int n)
{
    if (n<26)
        return static_cast<char>('A'+n);
    else
        return static_cast<char>('a'+n-26);
}

// connected_node_from_start_node, edge_distance
typedef pair<int,double> edge_t;

//==============================================================================
// Node definitions
// Used to store information about nodes/edges in the adjacency list of a graph
// Each node contains a list of neighbors containing edge weight
//==============================================================================
class Node {
    public:
        int name;
        double value;
        list<edge_t> edges;
};

//==============================================================================
// Graph Class
// Represent a Graph through an adjacency list
// Adjacency lists is a list of Nodes (identified by numbers from 0 to 51)
//==============================================================================
class Graph
{
    public:
        Graph();
        Graph(int numVertices);
        char get_node_value(int x);
        void set_node_value(char x, char name);
        int get_edge_value(char x, char y);
        void set_edge_value(char x, char y, int value);
        bool adjacent(char x, char y);
        list<char> neighbors(char x);
        int V();
        int E();
        list<char> vertices();
        void show();
    
    private:
        int numV;			// Number of nodes of the Graph
        int numE;			// Number of edges of the Graph
        vector<char> nodeNames;	// Map node numbers into node names
        map<char, int> nodeNumbers;	// Map node names into node numbers
        list<Node> adjList;		// Adjacency list representing the Graph
};


// Default constructor of Graph Class
// Create an empty graph
Graph::Graph()
{
    numV = 0;
    numE = 0;
    adjList.clear();
}

// Constructor of Graph Class
// Initialize number of nodes, should be in (0..51]
// Create adjacency list with all nodes and empty edge list
Graph::Graph(int numVertices)
{
    // Create nodes and link it to default names (0..51 -> A..Za..z)
    numV = numVertices;
    numE = 0;
    nodeNames.resize(numVertices);
    for (int i=0; i<numV; ++i)
    {  
        nodeNames[i] = int2char(i);
        nodeNumbers[int2char(i)]=i;
    }
    
    // Create adjacency list with all nodes and empty edge list
    adjList.clear();
    for(int i=0; i<numVertices; ++i)
    {
        Node newNode;
        newNode.name = i;
        newNode.value = 0;
        newNode.edges.clear(); //edges is a list container
        adjList.push_back(newNode);
    }
}

char get_node_value(int x);
void set_node_value(char x, char name);
int get_edge_value(char x, char y);
void set_edge_value(char x, char y, int value);
bool adjacent(char x, char y);
list<char> neighbors(char x);
int V();
int E();
list<char> vertices();
void show();