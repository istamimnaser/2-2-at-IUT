#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

// --- Bellman-Ford Negative Cycle Detection ---
bool hasNegativeCycle(int n, const vector<Edge>& edges) {
   
    vector<long long> dist(n + 1, 0);

    // Phase 1: Relax all edges up to n - 1 times
    for (int i = 0; i < n - 1; ++i) {
        bool any_update = false;
        
        for (const auto& edge : edges) {
            // Since all initial distances are 0, we don't need an INF check
            if (dist[edge.u] + edge.w < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.w;
                any_update = true;
            }
        }
        
        // If no distances were updated, the graph has settled.
        // No negative cycles exist.
        if (!any_update) {
            return false;
        }
    }

    // Phase 2: Check for a negative cycle on the n-th pass
    for (const auto& edge : edges) {
        if (dist[edge.u] + edge.w < dist[edge.v]) {
            // If we can STILL optimize a path, a negative cycle exists
            return true;
        }
    }

    return false;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<Edge> edges(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    
    if (hasNegativeCycle(n, edges)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}