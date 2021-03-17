#include <bits/stdc++.h>
using namespace std;

#define f(i,k,n) for(int i = 0; i < n; i++)
#define fo(i,k,n) for(i = 0; i < n; i++)

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

static const int N = 9;

bool UsedInRow(int grid[N][N], int row, int num)
{
  for (int col = 0; col < N; col++)
    if (grid[row][col] == num)
      return true;
  return false;
}

bool UsedInCol(int grid[N][N], int col, int num)
{
  for (int row = 0; row < N; row++)
    if (grid[row][col] == num)
      return true;
  return false;
}

bool UsedInBox(int grid[N][N], int boxStartRow,
    int boxStartCol, int num)
{
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      if (grid[row + boxStartRow]
          [col + boxStartCol] ==
          num)
        return true;
  return false;
}

bool isSafe(int grid[N][N], int row,
    int col, int num)
{
  return !UsedInRow(grid, row, num)
    && !UsedInCol(grid, col, num)
    && !UsedInBox(grid, row - row % 3,
        col - col % 3, num)
    && grid[row][col] == 0;
}

pair<int, int> getNext(int i, int j){
  if (j == N - 1){
    return {i + 1, 0};
  }
  return {i, j + 1};
}


void printGrid (int grid[N][N]) {
  f(i, 0, N){
    f(j, 0, N){
      cout<<grid[i][j]<< " ";
    }
    cout<<endl;
  }
}

bool solveSudokuUtil(int grid[N][N], int i, int j){
  if(i >= N && j>= N){
    return false;
  }
  if(grid[i][j] != 0){
    auto next = getNext(i, j);
    return solveSudokuUtil(grid, next.first, next.second);
  }
  for(int k = 1; k <= 9; k++){
    if(isSafe(grid, i, j, k)){
      grid[i][j] = k;
      if(i == N-1 && j == N-1){
        return true;
      }
      auto next = getNext(i, j);
      bool result = solveSudokuUtil(grid, next.first, next.second);
      if(result){
        return true;
      }else{
        grid[i][j] = 0;
      }
    }
  }
  return false;
}


bool SolveSudoku(int grid[N][N])  { 
  return solveSudokuUtil(grid, 0, 0);
}

int main()
{
  int grid[N][N];
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      cin>>grid[i][j];
    }
  }
  bool solved = SolveSudoku(grid);
  if(solved){
    printGrid(grid);
  }else{
    print("No solution found");
    printGrid(grid);
  }
}
