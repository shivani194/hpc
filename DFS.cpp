#include <iostream> 
#include <vector> 
#include <omp.h> 
using namespace std; 

const int MAXN = 1e5; 
vector<int> adj[MAXN+5]; 

bool visited_parallel[MAXN+5]; 
bool visited_seq[MAXN+5]; 

// 🔴 Parallel DFS
void dfs_parallel(int node) { 
    visited_parallel[node] = true; 

    #pragma omp parallel for 
    for (int i = 0; i < adj[node].size(); i++) { 
        int next_node = adj[node][i]; 

        if (!visited_parallel[next_node]) { 
            dfs_parallel(next_node); 
        } 
    } 
} 

// 🔵 Sequential DFS
void dfs_sequential(int node) { 
    visited_seq[node] = true; 

    for (int i = 0; i < adj[node].size(); i++) { 
        int next_node = adj[node][i]; 

        if (!visited_seq[next_node]) { 
            dfs_sequential(next_node); 
        } 
    } 
} 

int main() { 
    cout << "Enter number of nodes and edges: "; 
    int n, m; 
    cin >> n >> m; 

    // Input edges
    cout << "Enter edges (u v):\n";
    for (int i = 1; i <= m; i++) { 
        int u, v; 
        cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    } 

    int start_node; 
    cout << "Enter starting node: "; 
    cin >> start_node; 

    double start, end; 

    //  Sequential DFS
    start = omp_get_wtime(); 
    dfs_sequential(start_node); 
    end = omp_get_wtime(); 

    cout << "\nSequential DFS visited nodes: "; 
    for (int i = 1; i <= n; i++) { 
        if (visited_seq[i]) cout << i << " "; 
    } 
    cout << "\nSequential DFS Time: " << end - start << endl; 

    // Parallel DFS
    start = omp_get_wtime(); 
    dfs_parallel(start_node); 
    end = omp_get_wtime(); 

    cout << "\nParallel DFS visited nodes: "; 
    for (int i = 1; i <= n; i++) { 
        if (visited_parallel[i]) cout << i << " "; 
    } 
    cout << "\nParallel DFS Time: " << end - start << endl; 

    return 0; 
}