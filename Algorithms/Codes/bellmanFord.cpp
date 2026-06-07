#include <bits/stdc++.h>
using namespace std;

// Bellman-Ford algorithm (single-source shortest paths)
// - Handles negative edge weights
// - Detects negative-weight cycles reachable from the source
//
// Returns: pair of (distances vector, hasNegativeCycle)
// - distances: 1-indexed vector of shortest distances from `source` to every vertex
// - hasNegativeCycle: true if a negative-weight cycle is reachable from `source`

const long long INF = LLONG_MAX / 4;

pair<vector<long long>, bool> bellmanFord(int n, int source, const vector<tuple<int,int,int>> &edges) {
    // Initialize distances to "infinity" and source to 0.
    vector<long long> dist(n + 1, INF);
    dist[source] = 0;

    // Relax all edges up to n-1 times.
    // After k iterations, distances that use at most k edges are finalized.
    for (int iter = 1; iter <= n - 1; ++iter) {
        bool changed = false; // optimization: stop early if no update
        for (const auto &e : edges) {
            int u, v, w;
            tie(u, v, w) = e;
            // Only relax if the source side is reachable
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if (!changed) // no change in this pass -> distances stabilized
            break;
    }

    // Check for negative-weight cycles reachable from the source.
    // If we can relax any edge further, there is a negative cycle.
    bool hasNegativeCycle = false;
    for (const auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    return {dist, hasNegativeCycle};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input format:
    // n m
    // m lines: u v w   (edge from u -> v with weight w)
    // source
    // Vertices are assumed 1..n.

    int n, m;
    if (!(cin >> n >> m))
        return 0; // no input

    vector<tuple<int,int,int>> edges;
    edges.reserve(m);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    int source;
    cin >> source;

    auto [dist, hasNegCycle] = bellmanFord(n, source, edges);

    if (hasNegCycle) {
        // Inform the user that distances are undefined due to a negative cycle.
        cout << "Negative cycle detected\n";
        return 0;
    }

    // Print distances: use INF to indicate unreachable vertices.
    for (int v = 1; v <= n; ++v) {
        if (dist[v] == INF)
            cout << "INF";
        else
            cout << dist[v];
        if (v < n) cout << ' ';
    }
    cout << '\n';

    return 0;
}
