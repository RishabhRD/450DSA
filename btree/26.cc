#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

bool has_cycle(vector<int>* adj, vector<bool>& visited, int i, int parent){
  visited[i] = true;
  for(auto x : adj[i]){
    if(!visited[x]){
      if(has_cycle(adj, visited, x, i)){
        return true;
      }
    }else if(x != parent){
      return true;
    }
  }
  return false;
}

bool isTree(int V, vector<int> adj[]) {
  vector<bool> visited(V);

  bool cycle = has_cycle(adj, visited, 0, -1);
  if(cycle) return false;
  for(int i = 0; i < V; i++){
    if(!visited[i]){
      return false;
    }
  }
  return true;
}
