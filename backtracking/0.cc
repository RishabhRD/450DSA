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

void recursivePath(vector<vector<int>>& vec, int n, vector<string>& resultVector, vector<vector<bool>> visitedVector, int i, int j, string currentString){
  if(i >= n || j >= n || i < 0 || j < 0){
    return;
  }else if(vec[i][j] == 0){
    return;
  }else if(visitedVector[i][j] == true){
    return;
  }else if(i == n - 1 && j == n - 1){
    resultVector.push_back(currentString);
    return;
  }
  visitedVector[i][j] = true;
  recursivePath(vec, n, resultVector, visitedVector, i + 1, j, currentString + "D");
  recursivePath(vec, n, resultVector, visitedVector, i - 1, j, currentString + "U");
  recursivePath(vec, n, resultVector, visitedVector, i, j - 1, currentString + "L");
  recursivePath(vec, n, resultVector, visitedVector, i, j + 1, currentString + "R");
}

vector<string> findPath(vector<vector<int>> &m, int n) {
  vector<vector<bool>> visited;
  if(n == 0){
    vector<string> vec;
    return vec;
  }
  for(auto& v : m){
    vector<bool> vec(n);
    visited.push_back(vec);
  }
  vector<string> returnVector;
  recursivePath(m, n, returnVector, visited, 0, 0, "");
  return returnVector;
}

int main()
{
  int n;
  cin>>n;
  vector<vector<int>> vec;
  for(int i = 0; i < n; i++){
    vector<int> innerVector(n);
    for(int j = 0; j < n; j++){
      cin>>innerVector[j];
    }
    vec.push_back(innerVector);
  }
  vector<string> resultVector = findPath(vec, n);
  print(resultVector.begin(), resultVector.end());
}
