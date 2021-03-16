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

void printBoard(vector<vector<int>>& board, int n){
  for(auto& row : board){
    for(int col : row){
      cout<<col<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}

bool isSafe(vector<vector<int>>& board, int row, int col, int n)
{
  int i, j;

  /* Check this row on left side */
  for (i = 0; i < col; i++)
    if (board[row][i])
      return false;

  /* Check upper diagonal on left side */
  for (i=row, j=col; i>=0 && j>=0; i--, j--)
    if (board[i][j])
      return false;

  /* Check lower diagonal on left side */
  for (i=row, j=col; j>=0 && i<n; i++, j--)
    if (board[i][j])
      return false;

  return true;
}

void placeQueen(vector<vector<int>>& board, int currentPlacingCol, int n){
  if(currentPlacingCol == n){
    printBoard(board, n);
    return;
  }
  f(i, 0, n){
    if(isSafe(board, i, currentPlacingCol, n)){
      board[i][currentPlacingCol] = 1;
      placeQueen(board, currentPlacingCol + 1, n);
      board[i][currentPlacingCol] = 0;
    }
  }
}

void solveNQueen(int n){
  vector<vector<int>> board;
  f(i, 0, n){
    vector<int> internalVector(n);
    board.push_back(internalVector);
  }
  placeQueen(board, 0, n);
}

int main()
{
  int n;
  cin>>n;
  solveNQueen(n);
}
