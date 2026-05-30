#include<iostream>
#include<vector>
#include<stack>
using namespace std;

stack<int> st;

void dfs(vector<vector<int>>&graph, vector<bool>&visited,int node){
    visited[node]= true;

    for(int i : graph[node]){
        if(!visited[i]){
            dfs(graph, visited, i);
        }
    }
    st.push(node);
}


void topologicalSort(vector<vector<int>>&graph, int start){
    int n = graph.size();
    vector<bool> visited(n, false); // visited[i] is true when node i has been discovered
    dfs(graph, visited, start);

    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();