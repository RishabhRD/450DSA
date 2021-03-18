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

static const int R = 12;
static const int C = 10;

int moveRow[4] = {-1, 1, 0, 0};
int moveCol[4] = {0, 0, 1, -1};

bool isSafe(int row, int col, bool plot[R][C], bool visited[R][C]) {
  int mineCheckRow[4] = {-1, 1, 0, 0};
  int mineCheckCol[4] = {0, 0, 1, -1};
  bool isFine = row >= 0 && col >= 0 && row < R && col < C &&
                plot[row][col] == true && visited[row][col] == false;
  if (!isFine) {
    return false;
  }
  f(i, 0, 4) {
    int newX = row + mineCheckRow[i];
    int newY = col + mineCheckCol[i];
    if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
      if (plot[newX][newY] == false) {
        return false;
      }
    }
  }
  return true;
}

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 

int shortestLandminesUtil(int row, int col, bool plot[R][C], bool visited[R][C],
                          unordered_map<pair<int, int>, int, hash_pair> &shortestPathMap) {
  if (col == C - 1) {
    return 0;
  }
  pair<int, int> rowColPair = {row, col};
  if(shortestPathMap.find(rowColPair) != shortestPathMap.end()){
    return shortestPathMap[rowColPair];
  }
  int min = INT_MAX;
  f(i, 0, 4) {
    int newRow = row + moveRow[i];
    int newCol = col + moveCol[i];
    if (isSafe(newRow, newCol, plot, visited)) {
      visited[newRow][newCol] = true;
      int moveLength =
          shortestLandminesUtil(newRow, newCol, plot, visited, shortestPathMap);
      if (moveLength < min) {
        min = moveLength;
      }
      visited[newRow][newCol] = false;
    }
  }
  if (min == INT_MAX) {
    shortestPathMap[rowColPair] = min;
    return min;
  } else {
    shortestPathMap[rowColPair] = min + 1;
    return min + 1;
  }
}

int shortestLandmines(bool plot[R][C]) {
  int min = INT_MAX;
  bool visited[R][C];
  f(i, 0, R) {
    f(j, 0, C) { visited[i][j] = false; }
  }
  unordered_map<pair<int, int>, int, hash_pair> shortestPathMap;
  f(i, 0, R) {
    if (isSafe(i, 0, plot, visited)) {
      visited[i][0] = true;
      int move = shortestLandminesUtil(i, 0, plot, visited, shortestPathMap);
      if (move < min) {
        min = move;
      }
      visited[i][0] = false;
    }
  }
  return min;
}

int main() {
  bool plot[R][C];
  f(i, 0, R) {
    f(j, 0, C) { cin >> plot[i][j]; }
  }
  cout << shortestLandmines(plot) << endl;
}
