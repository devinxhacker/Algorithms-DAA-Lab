#include<iostream>
using namespace std;

#define MAX 100
#define INF 999999

int main() {
    int n, graph[MAX][MAX];
    int visited[MAX] = {0};  // To track visited vertices
    int parent[MAX];         // To store MST edges
    int key[MAX];            // Minimum weight to reach each vertex
    
    // Input number of vertices
    cout << "Enter number of vertices: ";
    cin >> n;
    
    // Input adjacency matrix
    cout << "Enter adjacency matrix (0 for no edge):\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if(graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;  // No edge means infinite weight
            }
        }
    }
    
    // Initialize all keys as infinite and parent as -1
    for(int i = 0; i < n; i++) {
        key[i] = INF;
        parent[i] = -1;
    }
    
    // Start from vertex 0
    key[0] = 0;
    
    // Find MST with n-1 edges
    for(int count = 0; count < n; count++) {
        
        // Find vertex with minimum key value (not yet in MST)
        int minKey = INF;
        int u = -1;
        
        for(int v = 0; v < n; v++) {
            if(visited[v] == 0 && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }
        
        // Add this vertex to MST
        visited[u] = 1;
        
        // Update key values of adjacent vertices
        for(int v = 0; v < n; v++) {
            // If v is not in MST and edge u-v has smaller weight
            if(visited[v] == 0 && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    
    // Print the MST edges and total cost
    int totalCost = 0;
    cout << "\nMinimum Spanning Tree Edges:\n";
    cout << "Edge \t\t Weight\n";
    
    for(int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << "\t\t" << graph[i][parent[i]] << "\n";
        totalCost += graph[i][parent[i]];
    }
    
    cout << "\nTotal cost of MST: " << totalCost << endl;
    
    return 0;
}

// 0 2 0 6
// 2 0 3 8
// 0 3 0 5
// 6 8 5 0