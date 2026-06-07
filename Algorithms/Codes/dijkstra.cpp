#include <bits/stdc++.h>
using namespace std;

// A large value to represent "infinity" for distances.
const long long INF = LLONG_MAX / 4;

// Dijkstra's algorithm returns the shortest distance from source to all vertices.
// n      : number of vertices in the graph
// source : the starting vertex
// adj    : adjacency list where adj[u] contains pairs (v, weight)
vector<long long> dijkstra(int n, int source, const vector<vector<pair<int, int>>> &adj) {
    // dist[v] = current best known distance from source to v
    vector<long long> dist(n + 1, INF);
    // vis[v] = whether the shortest path to v is finalized
    vector<bool> vis(n + 1, false);

    // Distance to the source is zero.
    dist[source] = 0;

    // Min-heap priority queue ordered by distance.
    // Each element is (distance, vertex).
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // If u was already visited, skip it.
        if (vis[u])
            continue;

        // Mark u as finalized.
        vis[u] = true;

        // Check all neighbors of u.
        for (auto &[v, w] : adj[u]) {
            // Skip neighbors whose shortest distance is already finalized.
            if (vis[v])
                continue;

            // Relax the edge u -> v.
            if (d + w < dist[v]) {
                dist[v] = d + w;
                // Push the updated distance to the queue.
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Graph is stored as adjacency list. 1-indexed vertices.
    vector<vector<pair<int, int>>> adj(n + 1);

    // Read m edges: u, v, weight.
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // remove this line for a directed graph
    }

    int source;
    cin >> source;

    // Compute shortest distances from source.
    vector<long long> dist = dijkstra(n, source, adj);

    // Print distances for vertices 1..n.
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF)
            cout << "INF";
        else
            cout << dist[i];

        if (i < n)
            cout << ' ';
    }
    cout << '\n';

    return 0;
}
