#include <bits/stdc++.h>
using namespace std;

#define f(i, k, n) for (int i = k; i < n; i++)
#define fo(i, k, n) for (i = k; i < n; i++)

template <typename T> void print(T ele, string message = "") {
  cout << message << ele << endl;
}

template <typename T> void print(T begin, T end, string message = "") {
  cout << message;
  while (begin != end) {
    cout << *begin << " ";
    begin++;
  }
  cout << endl;
}

template <typename T> T toNumber(const string &s) {
  T answer = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    T num = s[i] - '0';
    answer = (answer * 10) + num;
  }
  return answer;
}

using ll = long long;
#define toInt toNumber<int>
#define toLL toNumber<ll>
#define toLong toLong<long>

bool pathMoreThanKUtil(int src, int k, vector<unordered_map<int, int>> &graph,
                       vector<bool> visited) {
  if (k < 0) {
    return true;
  }
  visited[src] = true;
  auto &nodeList = graph[src];
  for (auto &adjacentNode : nodeList) {
    if(!visited[adjacentNode.first]){
      if (pathMoreThanKUtil(adjacentNode.first, k - adjacentNode.second, graph,
            visited)) {
        return true;
      }
    }
  }
  visited[src] = false;
  return false;
}

bool pathMoreThanK(int src, int k, vector<unordered_map<int, int>> &graph) {
  int size = graph.size();
  vector<bool> visited(size);
  for (int i = 0; i < size; i++) {
    visited[i] = false;
  }
  return pathMoreThanKUtil(src, k, graph, visited);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int e;
    cin>>e;
    vector<unordered_map<int, int>> graph(n);
    f(i, 0, e) {
      int src, dest, weight;
      cin >> src >> dest >> weight;
      graph[src][dest] = weight;
      graph[dest][src] = weight;
    }
    int src;
    cin >> src;
    int k;
    cin >> k;
    cout << pathMoreThanK(src, k, graph) << endl;
  }
}
