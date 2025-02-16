#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Graph{
  public:
    unordered_map<int, list<pair<int, int>>> adj;


    void addedge(int u, int v, int weight){
      pair<int, int> p = make_pair(v,weight);

      adj[u].push_back(p);
    }

    void printAdj(){
      for(auto i : adj){
        cout << i.first << " -> ";
        for(auto j : i.second){
          cout << "(" << j.first << "," << j.second << "), ";
        }
        cout<<endl;
      }
    }

    void dfs(stack<int> &s, unordered_map<int, bool> &vis, int node){
      vis[node] = true;

      for(auto neighbour : adj[node]){
        if(!vis[neighbour.first]){
          dfs(s, vis, neighbour.first);
        }
      }

      s.push(node);
    }

    void getShortestPath(int src, vector<int> &dist, stack<int> &s){
      dist[src] = 0;

      while(!s.empty()){
        int top = s.top();
        s.pop();
        if(dist[top] != INT_MAX){
          for(auto &i : adj[top]){
            if(dist[top] + i.second < dist[i.first])
              dist[i.first] = dist[top] + i.second; 
          }
        }
      }
    }

};

int main() {
  Graph g;
  g.addedge(0,1,5);
  g.addedge(0,2,3);
  g.addedge(1,2,2);
  g.addedge(1,3,6);
  g.addedge(2,3,7);
  g.addedge(2,4,4);
  g.addedge(2,5,2);
  g.addedge(3,4,-1);
  g.addedge(4,5,-2);

  cout<<"the given graph is as follows"<<endl;
  g.printAdj();

  int n = 6;
  
  // topological sort
  unordered_map<int, bool> visited;
  stack<int> stack;
  for(int i = 0; i < n; i++){
    
      if(!visited[i]){
        g.dfs(stack, visited, i);
      }  
  }

  int src = 1;
  vector<int> dist(n);
  
  for(int i = 0; i < n; i++){
    dist[i] = INT_MAX;
  }

  g.getShortestPath(src, dist, stack);

  cout<<"answer is"<<endl;

  for(int i = 0; i < dist.size(); i++){
    cout<<dist[i]<<" ";
  }cout<<endl;

  return 0;
}