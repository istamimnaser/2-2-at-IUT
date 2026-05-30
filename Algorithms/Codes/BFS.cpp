#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// Graph representation:
// - `graph` is an adjacency list.
// - `graph[i]` contains the list of neighbors for node `i`.
// - This is a common graph structure because it is efficient for sparse graphs.
//
// Example graph implementation using adjacency list:
// vector<vector<int>> graph = {
//     {1, 2},    // neighbors of node 0
//     {0, 3, 4}, // neighbors of node 1
//     {0},       // neighbors of node 2
//     {1},       // neighbors of node 3
//     {1}        // neighbors of node 4
// };
//
// For an undirected graph, add both directions for each edge:
// graph[u].push_back(v);
// graph[v].push_back(u);
//
// For a directed graph, add only one direction:
// graph[u].push_back(v);

void bfs(vector<vector<int>>&graph, int start){
    int n = graph.size();
    vector<bool> visited(n, false); // visited[i] is true when node i has been discovered
    queue<int> q;

        // Start BFS from the `start` node.
    visited[start] = true;
    q.push(start);

    while(!q.empty()){
        int current = q.front();
        q.pop();

        cout<<current<<" ";

        // Iterate over all neighbors of the current node.
        for(int k = 0; k < graph[current].size(); k++){
            int neighbor = graph[current][k];

            // If this neighbor has not been visited yet, mark it and enqueue it.
            if(!visited[neighbor]){
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
//time complexity: O(V + E) where V is the number of vertices and E is the number of edges in the graph
//space complexity: O(V) for the visited array and O(V) for the queue in the worst case when all vertices are visited.