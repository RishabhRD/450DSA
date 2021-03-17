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

