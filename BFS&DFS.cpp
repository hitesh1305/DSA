#include <stdio.h> 
#include <stdlib.h> 
#define MAX 10 // Maximum number of vertices 
 
int adjMatrix[MAX][MAX]; // Adjacency matrix 
int visited[MAX];        // Visited array to track visited vertices 
int queue[MAX];          // Queue for BFS 
int front = -1, rear = -1; 
 
// Function to add an edge to the graph 
void addEdge(int src, int dest) { 
    adjMatrix[src][dest] = 1; 
    adjMatrix[dest][src] = 1; // For undirected graph 
} 
 
// Initialize the adjacency matrix and visited array 
void initializeGraph(int vertices) { 
    for (int i = 0; i < vertices; i++) { 
        for (int j = 0; j < vertices; j++) { 
            adjMatrix[i][j] = 0; 
        } 
        visited[i] = 0; 
    } 
} 
 
// Breadth-First Traversal (BFS) 
void bfs(int startVertex, int vertices) { 
    front = rear = -1; // Initialize queue 
    queue[++rear] = startVertex; 
    visited[startVertex] = 1; 
 
 
 
    printf("Breadth-First Traversal: "); 
    while (front != rear) { 
        int currentVertex = queue[++front]; 
        printf("%d ", currentVertex); 
 
        for (int i = 0; i < vertices; i++) { 
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) { 
                queue[++rear] = i; 
                visited[i] = 1; 
            } 
        } 
    } 
    printf("\n"); 
} 
 
// Depth-First Traversal (DFS) using recursion 
void dfs(int vertex, int vertices) { 
    printf("%d ", vertex); 
    visited[vertex] = 1; 
 
    for (int i = 0; i < vertices; i++) { 
        if (adjMatrix[vertex][i] == 1 && !visited[i]) { 
            dfs(i, vertices); 
        } 
    } 
} 
 
int main() { 
    int vertices, edges, src, dest, startVertex; 
 
    // Input the number of vertices and edges 
    printf("Enter the number of vertices: "); 
 
 
    scanf("%d", &vertices); 
    printf("Enter the number of edges: "); 
    scanf("%d", &edges); 
 
    // Initialize the graph 
    initializeGraph(vertices); 
 
    // Input the edges 
    for (int i = 0; i < edges; i++) { 
        printf("Enter source and destination for edge %d (0-based indexing): ", i + 1); 
        scanf("%d %d", &src, &dest); 
        addEdge(src, dest); 
    } 
 
    // Input the starting vertex for traversal 
    printf("Enter the starting vertex for traversal: "); 
    scanf("%d", &startVertex); 
 
    // Perform BFS 
    bfs(startVertex, vertices); 
 
    // Reset visited array for DFS 
    for (int i = 0; i < vertices; i++) { 
        visited[i] = 0; 
    } 
 
    // Perform DFS 
    printf("Depth-First Traversal: "); 
    dfs(startVertex, vertices); 
    printf("\n"); 
 
    return 0; 
 
 
} 