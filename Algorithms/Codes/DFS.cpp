#include<bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>>&graph, vector<bool>&visited,int node){
    visited[node]= true;
    cout<<node<<" ";

    for(int i : graph[node]){
        if(!visited[i]){
            dfs(graph, visited, i);
        }
    }
}

void dfs_caller(vector<vector<int>>&graph, int start){
    int n = graph.size();
    vector<bool> visited(n, false); // visited[i] is true when node i has been discovered
    dfs(graph, visited, start);
}

// time complexity: O(V + E) where V is the number of vertices and E is the number of edges in the graph
// space complexity: O(V) for the visited array and O(V) for the recursion stack