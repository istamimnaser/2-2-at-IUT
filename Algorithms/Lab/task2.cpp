#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 2e18;

struct Edge {
    int u;
    int v;
    long long w;
};


void bellmanFord(int n, int s, const vector<Edge>& edges, const vector<vector<int>>& adj, vector<long long>& dist, vector<bool>& in_neg_cycle) {
    
  
    dist.assign(n + 1, INF);
    dist[s] = 0;

    
    for (int i = 0; i < n - 1; ++i) {
        bool any_update = false;
        
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.w;
                any_update = true;
            }
        }
        
        if (!any_update) break; 
    }

    
    queue<int> q;
    in_neg_cycle.assign(n + 1, false);

    for (const auto& edge : edges) {
        if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
            if (!in_neg_cycle[edge.v]) {
                in_neg_cycle[edge.v] = true;
                q.push(edge.v);
            }
        }
    }


    while (!q.empty()) {0
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!in_neg_cycle[v]) {
                in_neg_cycle[v] = true;
                q.push(v);
            }
        }
    }
}


int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<Edge> edges(m);
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].push_back(edges[i].v);
    }

 
    vector<long long> dist;
    vector<bool> in_neg_cycle;

  
    bellmanFord(n, s, edges, adj, dist, in_neg_cycle);

    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) {
            cout << "INF\n";
        } else if (in_neg_cycle[i]) {
            cout << "-INF\n";
        } else {
            cout << dist[i] << "\n";
        }
    }

    return 0;
}