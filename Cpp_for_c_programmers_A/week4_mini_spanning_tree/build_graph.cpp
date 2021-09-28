#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

// return a random number [0, 1]
double prob() {
    return (static_cast<double>(rand())/RAND_MAX);
}

int main() {
    int size = 15; 
    double density;
    cout << "graph size?" << endl;
    cin >> size;
    cout << "graph density (0,1)?" << endl;
    cin >> density;
    bool ** graph;
    int ** color;
    int ** cost;
    srand(time(0)); // seed random number generator

    graph = new bool*[size];
    color = new int*[size];
    cost = new int*[size];

    for (int i=0; i<size; ++i) {
        graph[i] = new bool[size];
        color[i] = new int[size];
        cost[i] = new int[size];
    }

    for (int i=0; i<size; ++i) { // generate undirected edges
        for (int j=0; j<size; ++j) {
            if (i==j) {
                graph[i][j] = false;
            }
            else {
                graph[i][j] = graph[j][i] = (prob() < density);
            }
        }
    }

    for (int i=0; i<size; ++i) { //generate costs and color
        for (int j=0; j<size; ++j) {
            if (graph[i][j]) {
                color[i][j] = color[j][i] = rand()%3;
                cost[i][j] = cost[j][i] = prob()*30;
            }
        }
    }

    // Print to output file
    ofstream outp("graph_data.txt");
    outp << size << "\n";
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            if (graph[i][j]) {
                outp << i << "\t" << j << "\t" << cost[i][j] << "\t" << color[i][j] << "\t";
            }
        }
    }

    return 0;
}