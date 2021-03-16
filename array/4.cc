#include <bits/stdc++.h>
using namespace std;

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

#define fo(i,k,n) for(i = 0; i < n; i++)
#define f(i,k,n) for(int i = 0; i < n; i++)

int main()
{
  int n;
  cin>>n;
  int arr[n];
  for(int i = 0; i < n; i++){
    cin>>arr[i];
  }
  int j = 0;
  f(i,0,n){
    if(arr[i] < 0){
      if(i != j){
        swap(arr[i], arr[j]);
        j++;
      }
    }
  }
  print(arr, arr + n);
}
