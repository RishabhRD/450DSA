#include <bits/stdc++.h>
using namespace std;

#define f(i,k,n) for(int i = k; i < n; i++)
#define fo(i,k,n) for(i = k; i < n; i++)

template<typename T>
void print(T ele, string message = ""){
  cout<<message<<ele<<endl;
}

template<typename T>
void print(T begin, T end, string message = ""){
  cout<<message;
  while(begin < end){
    cout<<*begin<<" ";
    begin++;
  }
  cout << endl;
}

bool findUncolored(int* nodeColors, int v, int& node){
  for(int i = 0; i < v; i++){
    if(nodeColors[i] == 0){
      node = i;
      return true;
    }
  }
  return false;
}

bool isSafeToColor(int node, int color, bool graph[101][101], int* nodeColors, int v){
  bool* graphNode = graph[node];
  f(i, 0, v){
    if(graphNode[i] == true){
      if(nodeColors[graphNode[i]] == color){
        return false;
      }
    }
  }
  return true;
}

bool graphColoringUtil(int* nodeColors, bool graph[101][101], int m, int v, int currentNode){
  if(currentNode >= v){
    return true;
  }
  for(int i = 1; i <= m; i++){
    if(isSafeToColor(currentNode, i, graph, nodeColors, v)){
      nodeColors[currentNode] = i;
      if(graphColoringUtil(nodeColors, graph, m, v, currentNode + 1)){
        return true;
      }
      nodeColors[currentNode] = 0;
    }
  }
  return false;
}

bool graphColoring(bool graph[101][101], int m, int V) {
  int nodeColors[V];
  f(i, 0, V){
    nodeColors[i] = 0;
  }
  return graphColoringUtil(nodeColors, graph, m, V, 0);
}

int main()
{
  int n, m, e;
  cin>>n>>m>>e;
  bool graph[101][101];
  f(i, 0, 101){
    f(j, 0, 101){
      graph[i][j] = 0;
    }
  }
  f(i, 0, e){
    int first, second;
    cin>>first>>second;
    graph[first-1][second-1] = true;
    graph[second-1][first-1] = true;
  }
  cout<< graphColoring(graph, m, n) << endl;
}
