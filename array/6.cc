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

void swap(int& a, int& b){
  int temp = a;
  a = b;
  b = temp;
}

void rotate(int* arr, int n){
  int temp;
  for(int i = 1; i < n; i++){
    swap(arr[i], arr[0]);
  }
}

int main()
{
  
}
