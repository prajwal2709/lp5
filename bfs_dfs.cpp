%%writefile main.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

// Graph and visited array
vector<vector<int>> graph;
vector<bool> visited;

// 🔹 Parallel BFS
void parallelBFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";

    while (!q.empty()) {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            int node;

            // Critical section for queue access
            #pragma omp critical
            {
                node = q.front();
                q.pop();
                cout << node << " ";
            }

            // Process neighbors
            for (int j = 0; j < graph[node].size(); j++) {
                int adj = graph[node][j];

                if (!visited[adj]) {
                    #pragma omp critical
                    {
                        if (!visited[adj]) {
                            visited[adj] = true;
                            q.push(adj);
                        }
                    }
                }
            }
        }
    }
}


// 🔹 DFS (Sequential - safer)
void dfs(int node) {
    visited[node] = true;
    cout << node << " ";

    for (int i = 0; i < graph[node].size(); i++) {
        int adj = graph[node][i];

        if (!visited[adj]) {
            dfs(adj);
        }
    }
}


// 🔹 Main Function
int main() {
    int n, m, start;

    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    graph.resize(n);
    visited.resize(n, false);

    cout << "Enter " << m << " edges (u v format):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u); // undirected graph
    }

    cout << "Enter starting node: ";
    cin >> start;

    // BFS
    parallelBFS(start);

    // Reset visited for DFS
    fill(visited.begin(), visited.end(), false);

    cout << "\nDFS Traversal: ";
    dfs(start);

    return 0;
}