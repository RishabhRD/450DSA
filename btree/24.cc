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

int checkMirrorTree(int n, int e, int a[], int b[]) {
  unordered_map<int, stack<int>> mp;
  for(int i = 0; i < 2 * e; i += 2){
    mp[a[i]].push(a[i + 1]);
  }

  for(int i = 0; i < 2 * e; i += 2){
    if(mp[b[i]].top() != b[i + 1]) return false;
    mp[b[i]].pop();
  }
  return true;
}
