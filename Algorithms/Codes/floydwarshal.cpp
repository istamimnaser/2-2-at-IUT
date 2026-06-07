#include <bits/stdc++.h>
using namespace std;

// Floyd–Warshall algorithm: all-pairs shortest paths
// - Handles positive and negative edge weights (but no negative cycles)
// - Time complexity: O(n^3)
//
// Input format:
// n m
// m lines: u v w   (directed edge u -> v with weight w)
// Vertices are 1..n
//
// Output: n x n matrix of shortest distances. "INF" denotes unreachable.
// If a negative cycle exists (dist[i][i] < 0 for some i), prints "Negative cycle detected".

const long long INF = LLONG_MAX / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m))
        return 0; // no input

    // Initialize distance matrix with INF; zero on the diagonal.
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; ++i)
        dist[i][i] = 0;

    // Read edges and set initial distances.
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // If multiple edges exist, keep the smallest weight.
        dist[u][v] = min(dist[u][v], w);
    }

    // Floyd–Warshall core: consider each vertex k as an intermediate.
    // After processing k, dist[u][v] holds shortest path using vertices {1..k} as intermediates.
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (dist[i][k] == INF) continue; // skip unreachable intermediate
            for (int j = 1; j <= n; ++j) {
                if (dist[k][j] == INF) continue; // skip unreachable
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative cycles: any dist[i][i] < 0 indicates a negative cycle reachable from i.
    for (int i = 1; i <= n; ++i) {
        if (dist[i][i] < 0) {
            cout << "Negative cycle detected\n";
            return 0;
        }
    }

    // Print the distance matrix.
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dist[i][j] == INF)
                cout << "INF";
            else
                cout << dist[i][j];
            if (j < n) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}
