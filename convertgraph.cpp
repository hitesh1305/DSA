#include <iostream>
using namespace std;

const int MAX = 100;

// Convert directed graph to undirected
void directedToUndirected(int directed[MAX][MAX], int undirected[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (directed[i][j] == 1) {
                undirected[i][j] = 1;
                undirected[j][i] = 1; // add reverse edge
            }
        }
    }
}

// Convert undirected graph to directed
void undirectedToDirected(int undirected[MAX][MAX], int directed[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (undirected[i][j] == 1) {
                directed[i][j] = 1;
                // do NOT add reverse edge
            }
        }
    }
}

// Print the adjacency matrix
void printGraph(int graph[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

// Main function
int main() {
    int n = 4; // number of nodes
    int directed[MAX][MAX] = {0};
    int undirected[MAX][MAX] = {0};
    int converted[MAX][MAX] = {0};

    // Sample directed graph
    directed[0][1] = 1;
    directed[1][2] = 1;
    directed[2][3] = 1;

    cout << "Directed Graph:\n";
    printGraph(directed, n);

    directedToUndirected(directed, undirected, n);
    cout << "\nConverted to Undirected Graph:\n";
    printGraph(undirected, n);

    undirectedToDirected(undirected, converted, n);
    cout << "\nConverted back to Directed Graph:\n";
    printGraph(converted, n);

    return 0;
}
