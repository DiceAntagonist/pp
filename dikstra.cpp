#include <iostream>
#include <vector>
#include <climits>
#include <omp.h>

using namespace std;

const int INF = INT_MAX;

int main() {
    int n, edges;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> edges;

    vector<vector<pair<int, int>>> adj(n);
    cout << "Edges (u v w):" << endl;

    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int start;
    cout << "Start node: ";
    cin >> start;

    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        int min_dist = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        #pragma omp parallel for
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v]) {
                #pragma omp critical
                {
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }
    }

    cout << "Shortest distance from start node:" << endl;
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF)
            cout << "Node " << i << ": Not defined" << endl;
        else
            cout << "Node " << i << ": " << dist[i] << endl;
    }

    return 0;
}
