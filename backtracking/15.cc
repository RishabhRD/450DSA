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

static const int R = 3;
static const int C = 10;

int moveRow[4] = {0, 0, -1, 1};
int moveCol[4] = {1, -1, 0, 0};

bool isSafe(int matrix[R][C], int row, int col, bool visited[R][C]) {
  return row >= 0 && col >= 0 && row < R && col < C &&
         visited[row][col] == false && matrix[row][col] == 1;
}

pair<int, bool> findMaximumPathLengthUtil(int matrix[R][C], int srcRow,
                                          int srcCol, int destRow, int destCol,
                                          bool visited[R][C]) {
  if (srcRow == destRow && srcCol == destCol) {
    return {0, true};
  }
  int maxPathSum = INT_MIN;
  visited[srcRow][srcCol] = true;
  f(i, 0, 4) {
    int newRow = srcRow + moveRow[i];
    int newCol = srcCol + moveCol[i];
    if (isSafe(matrix, newRow, newCol, visited)) {
      auto newPath = findMaximumPathLengthUtil(matrix, newRow, newCol, destRow,
                                               destCol, visited);
      if (newPath.second) {
        if (maxPathSum < newPath.first) {
          maxPathSum = newPath.first;
        }
      }
    }
  }
  visited[srcRow][srcCol] = false;
  if (maxPathSum == INT_MIN) {
    return {maxPathSum, false};
  } else {
    return {1 + maxPathSum, true};
  }
}

void findMaximumPathLength(int matrix[R][C], int srcRow, int srcCol,
                           int destRow, int destCol) {
  bool visited[R][C];
  f(i, 0, R) {
    f(j, 0, C) { visited[i][j] = 0; }
  }
  auto path = findMaximumPathLengthUtil(matrix, srcRow, srcCol, destRow,
                                        destCol, visited);
  if (path.second) {
    cout << "Max Path length: " << path.first << endl;
  } else {
    cout << "No path found" << endl;
  }
}

int main()
{
  int mat[R][C] = 
  { 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } 
  }; 

  // find longest path with source (0, 0) and 
  // destination (1, 7) 
  findMaximumPathLength(mat, 0, 0, 1, 7); 
}
