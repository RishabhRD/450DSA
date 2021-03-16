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

int max(int* arr, int n){
  int maxSoFar = 0;
  int maxEndingHere = 0;
  f(i, 0, n){
    maxEndingHere = maxEndingHere + arr[i];
    if(maxEndingHere > maxSoFar){
      maxSoFar = maxEndingHere;
    }
    if(maxEndingHere < 0){
      maxEndingHere = 0;
    }
  }
  return maxSoFar;
}
