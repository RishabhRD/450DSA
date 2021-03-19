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

int moveRow[] = {1, 0};
int moveCol[] = {0, 1};

int getValue(int row, int col, int R, int C) { return C * row + col + 1; }

bool isSafe(vector<vector<bool>> visited, int row, int col, int R, int C) {
  bool cond =  row >= 0 && row < R && col >= 0 && col < C &&
         visited[row][col] == false;
  return cond;
}

void allPossibleRoutesUtil(vector<vector<int>> &matrix, int srcRow, int srcCol,
                           int R, int C, vector<int> &currentPath,
                           vector<vector<bool>>& visited, vector<vector<int>>& solution) {
  if (srcRow == R - 1 && srcCol == C - 1) {
    currentPath.push_back(getValue(srcRow, srcCol, R, C));
    solution.push_back(currentPath);
    currentPath.pop_back();
    return;
  }
  visited[srcRow][srcCol] = 1;
  f(i, 0, 2) {
    int newRow = srcRow + moveRow[i];
    int newCol = srcCol + moveCol[i];
    if (isSafe(visited, newRow, newCol, R, C)) {
      currentPath.push_back(getValue(srcRow, srcCol, R, C));
      allPossibleRoutesUtil(matrix, newRow, newCol, R, C, currentPath, visited, solution);
      currentPath.pop_back();
    }
  }
  visited[srcRow][srcCol] = false;
}

void allPossibleRoutes(vector<vector<int>> matrix, int R, int C){
  vector<vector<bool>> visited;
  f(i, 0, R){
    vector<bool> vec;
    f(j, 0, C){
      vec.push_back(0);
    }
    visited.push_back(vec);
  }
  vector<int> currentPath;
  vector<vector<int>> paths;
  allPossibleRoutesUtil(matrix, 0, 0, R, C, currentPath, visited, paths);
  for(auto& vec : paths){
    print(vec.begin(), vec.end());
  }
}

int main()
{
  vector<vector<int>> matrix;
  matrix.push_back({1, 2, 3});
  matrix.push_back({4, 5, 6});
  allPossibleRoutes(matrix, 2, 3);
}
