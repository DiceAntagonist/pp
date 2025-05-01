#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

int main() {
    int n, edges;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> edges;

    vector<vector<int>> adj(n);
    cout << "Enter edges (u v):" << endl;
    
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // If undirected graph
    }

    vector<bool> visited(n, false);
    queue<int> q;
    int start;

    cout << "Enter start node: ";
    cin >> start;

    visited[start] = true;
    q.push(start);

    cout << "BFS traversal:" << endl;

    while (!q.empty()) {
        int level_size = q.size();
        vector<int> next_level;

        #pragma omp parallel for
        for (int i = 0; i < level_size; i++) {
            int node;

            #pragma omp critical
            {
                node = q.front();
                q.pop();
            }

            cout << node << " ";

            for (int neighbor : adj[node]) {
                bool need_visit = false;

                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        need_visit = true;
                    }
                }

                if (need_visit) {
                    #pragma omp critical
                    next_level.push_back(neighbor);
                }
            }
        }

        for (int node : next_level) {
            q.push(node);
        }
    }

    cout << endl;
    return 0;
}
