#include <iostream> 
#include <queue> 
#include <vector> 
#include <omp.h> 
using namespace std; 

// 🔵 Sequential BFS
void bfs_sequential(int source, vector<vector<int>>& adj_list, int n) {
    vector<bool> visited(n + 1, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        cout << curr << " ";

        for (int i = 0; i < adj_list[curr].size(); i++) {
            int neighbour = adj_list[curr][i];

            if (!visited[neighbour]) {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }
}

// 🔴 Parallel BFS
void bfs_parallel(int source, vector<vector<int>>& adj_list, int n) {
    vector<bool> visited(n + 1, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        cout << curr << " ";

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < adj_list[curr].size(); i++) {
            int neighbour = adj_list[curr][i];

            if (!visited[neighbour]) {

                #pragma omp critical
                {
                    if (!visited[neighbour]) {
                        visited[neighbour] = true;
                        q.push(neighbour);
                    }
                }
            }
        }
    }
}

int main() {
    int num_vertices, num_edges, source;

    cout << "Enter vertices, edges and source: ";
    cin >> num_vertices >> num_edges >> source;

    vector<vector<int>> adj_list(num_vertices + 1);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < num_edges; i++) {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    double start, end;

    // Sequential BFS
    cout << "\nSequential BFS: ";
    start = omp_get_wtime();
    bfs_sequential(source, adj_list, num_vertices);
    end = omp_get_wtime();
    cout << "\nSequential Time: " << end - start << endl;

    // Parallel BFS
    cout << "\nParallel BFS: ";
    start = omp_get_wtime();
    bfs_parallel(source, adj_list, num_vertices);
    end = omp_get_wtime();
    cout << "\nParallel Time: " << end - start << endl;

    return 0;
}