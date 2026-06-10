#include <iostream>
#include <vector>

using namespace std;


const long long INF = 1e18;

struct Edge {
    int u;
    int v;
    long long w;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }


    vector<long long> dist(n + 1, INF);
    

    for (int i = 0; i < k; ++i) {
        int tower;
        cin >> tower;
        dist[tower] = 0;
    }

    for (int i = 0; i < n - 1; ++i) {
        bool any_update = false;
        
        for (int j = 0; j < m; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            long long w = edges[j].w;
            
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                any_update = true;
            }
        }
        
        
        if (!any_update) {
            break;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) {
            cout << "INF\n";
        } else {
            cout << dist[i] << "\n";
        }
    }

    return 0;
}