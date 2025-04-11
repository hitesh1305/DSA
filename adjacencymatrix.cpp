#include <stdio.h> 
 
#define MAX 10 // Maximum number of vertices 
 
// Function to initialize the adjacency matrix 
void initializeMatrix(int matrix[MAX][MAX], int vertices) { 
    for (int i = 0; i < vertices; i++) { 
        for (int j = 0; j < vertices; j++) { 
            matrix[i][j] = 0; // No edges initially 
        } 
    } 
} 
 
 
 
// Function to add an edge to the graph 
void addEdge(int matrix[MAX][MAX], int src, int dest) { 
    matrix[src][dest] = 1; // Add edge from source to destination 
    matrix[dest][src] = 1; // For undirected graph, add edge back 
} 
 
// Function to display the adjacency matrix 
void displayMatrix(int matrix[MAX][MAX], int vertices) { 
    printf("Adjacency Matrix:\n"); 
    for (int i = 0; i < vertices; i++) { 
        for (int j = 0; j < vertices; j++) { 
            printf("%d ", matrix[i][j]); 
        } 
        printf("\n"); 
    } 
} 
 
int main() { 
    int matrix[MAX][MAX]; // Adjacency matrix 
    int vertices, edges, src, dest; 
 
    // Input number of vertices 
    printf("Enter the number of vertices: "); 
    scanf("%d", &vertices); 
 
    // Initialize the adjacency matrix 
    initializeMatrix(matrix, vertices); 
 
    // Input number of edges 
    printf("Enter the number of edges: "); 
    scanf("%d", &edges); 
 
 
 
    // Input edges 
    for (int i = 0; i < edges; i++) { 
        printf("Enter source and destination for edge %d (0-based indexing): ", i + 1); 
        scanf("%d %d", &src, &dest); 
        addEdge(matrix, src, dest); 
    } 
 
    // Display the adjacency matrix 
    displayMatrix(matrix, vertices); 
 
    return 0; 
}