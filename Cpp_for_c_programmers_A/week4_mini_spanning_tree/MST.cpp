#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

// Class of Graph
class Graph {
    private:
        int numV;
        vector<vector<int>> edges;
    public:
        Graph();
        Graph(int numVertices, vector<vector<int>> edges);
        int getNumberVertices();
        int getEdgeValue(int node1, int node2);
        void setEdgeValue(int node1, int node2, int value);
        bool isAdjacent(int node1, int node2);
        void addEdge(int node1, int node2, int value);
        void deleteEdge(int node1, int node2);
        vector<vector<int>> getEdgeTable();
};

Graph::Graph() {
    numV = 0;
    edges.clear();
}

Graph::Graph(int numVertices, vector<vector<int>> edgeTable) {
    numV = numVertices;
    edges = edgeTable;
}

int Graph::getNumberVertices() {
    return numV;
}

int Graph::getEdgeValue(int node1, int node2) {
    return edges[node1][node2];
}

void Graph::setEdgeValue(int node1, int node2, int value) {
    edges[node1][node2] = edges[node2][node1] = value;
}

bool Graph::isAdjacent(int node1, int node2) {
    bool isAdj = (edges[node1][node2] == 0) ? false : true;
    return isAdj;
}

void Graph::addEdge(int node1, int node2, int value) {
    if (edges[node1][node2] == 0) {
        setEdgeValue(node1, node2, value);
    }
}

void Graph::deleteEdge(int node1, int node2) {
    setEdgeValue(node1, node2, 0);
}

vector<vector<int>> Graph::getEdgeTable() {
    return edges;
}

// Helper Function
void printEdges(vector<vector<int>> edgeTable) {
    cout << "Table of edges: " << endl;
    for (int i=0; i<edgeTable.size(); ++i) {
        for (int j=0; j<edgeTable[i].size(); ++j) {
            cout << edgeTable[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// MST
class MST {
    public:
        void mstPrim(Graph graph);
};

int minKey(vector<int> key, vector<bool> explored, int numV) { 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < numV; v++) 
        if (explored[v] == false && key[v] < min) {
            min = key[v]; 
            min_index = v; 
        }
    return min_index; 
} 

// A utility function to print the 
// constructed MST stored in parent[] 
void printMST(vector<int> parent, vector<vector<int>> graph) { 
    int numV = graph.size();
    cout<<"Edge     \tWeight\n"; 
    for (int i = 1; i < numV; i++) {
        cout<<parent[i]<<" - "<<i<<"   \t"<<graph[i][parent[i]]<<" \n"; 
    }
    cout << endl;
}

// Calculate MST cost
int calMST(vector<int> parent, vector<vector<int>> graph) {
    int numV = graph.size();
    int sum = 0;
    for (int i = 1; i < numV; i++) {
        sum += graph[i][parent[i]];
    }
    cout << "MST total cost: " << sum << endl; 
    return sum;
}

// Function to construct and print MST for 
// a graph represented using adjacency 
// matrix representation
void MST::mstPrim(Graph graph) {
    vector<vector<int>> edgeTable = graph.getEdgeTable();
    int numV = edgeTable.size();
    
    vector<bool> explored(numV, false); // vector of explored nodes
    vector<int> key(numV, INT_MAX); // store minimum weight
    vector<int> parent(numV); // store constructed MST
    
    int firstNode = 0;
    key[firstNode] = 0; 
    parent[firstNode] = -1;
    
    // MST have numV vertices
    for (int i=0; i<numV; ++i) {
        // Pick the minimum key vertex from the 
        // set of vertices not yet included in MST 
        int u = minKey(key, explored, numV); 
        
        // Add the picked vertex to the MST Set
        explored[u] = true;

        // Update key value and parent index of 
        // the adjacent vertices of the picked vertex. 
        // Consider only those vertices which are not 
        // yet included in MST 
        for (int v = 0; v < numV; v++) {
            // graph[u][v] is non zero only for adjacent vertices of m 
            // mstSet[v] is false for vertices not yet included in MST 
            // Update the key only if graph[u][v] is smaller than key[v] 
            if (edgeTable[u][v] && explored[v] == false && edgeTable[u][v] < key[v]) {
                parent[v] = u, key[v] = edgeTable[u][v]; 
            }
        }
    }
    // print the constructed MST 
    printMST(parent, edgeTable);
    calMST(parent, edgeTable);
}

// Main section
int main() {
    string filename = "graph_input.txt";
    ifstream graph_file(filename);
    int number;

    // Error in reading file
    if (!graph_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }
    
    graph_file >> number;
    int numVertices = number;
    cout << "Number of vertices: " << numVertices << endl;

    // Initialize edgeTable
    vector<vector<int>> edgeTable(numVertices, vector<int> (numVertices, 0));

    // Load edgeTable from input file
    int pos = 0;
    int node1 = 0;
    int node2 = 0;
    int value = 0;

    while (graph_file >> number) {
        node1 = (pos == 0) ? number : node1;
        node2 = (pos == 1) ? number : node2;
        value = (pos == 2) ? number : value;
        if (pos == 2) {
            edgeTable[node1][node2] = value;
        }
        pos++;
        pos %= 3;
    }

    // Graph
    Graph mst_graph(numVertices, edgeTable);
    printEdges(mst_graph.getEdgeTable());
    // MST
    MST mst;
    mst.mstPrim(mst_graph);
    
    graph_file.close();
    return EXIT_SUCCESS;
}