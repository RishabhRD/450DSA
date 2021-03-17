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
  while(begin != end){
    cout<<*begin<<" ";
    begin++;
  }
  cout << endl;
}

static const int N = 8;
const int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

bool isSafe(int x, int y, int board[N][N]){
  return x>=0 && x < N && y>=0 && y < N && board[x][y] == -1;
}


bool knightTourUtil(int x, int y, int currentMove, int board[N][N]){
  if(currentMove == N*N){
    board[x][y] = currentMove;
    return true;
  }
  for(int i = 0; i < N; i++){
    if(isSafe(x + xMove[i], y + yMove[i], board)){
      board[x][y] = currentMove;
      if(knightTourUtil(x + xMove[i], y + yMove[i], currentMove + 1, board)){
        return true;
      }
      board[x][y] = -1;
    }
  }
  return false;
}

void knightTour(){
  int board[N][N];
  f(i, 0, N){
    f(j, 0, N){
      board[i][j] = -1;
    }
  }
  bool knightTourResult = knightTourUtil(0, 0, 1, board);
  if(knightTourResult){
    f(i, 0, N){
      f(j, 0, N){
        cout<<board[i][j]<<" ";
      }
      cout<<endl;
    }
  }else{
    cout<<"No result found"<<endl;
  }
}

int main()
{
  knightTour();
}
