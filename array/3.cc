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

void sort(int a[], int n){
  int num;
  int numZero = 0;
  int numOne = 0;
  int numTwo = 0;
  for(int i = 0; i < n; i++){
    if(a[i] == 0){
      numZero++;
    }else if(a[i] == 1){
      numOne ++;
    }else{
      numTwo++;
    }
  }
  for(int i = 0; i < numZero; i++){
    cout<<0<<" ";
  }
  for(int i = 0; i < numOne; i++){
    cout<<1<<" ";
  }
  for(int i = 0; i < numTwo; i++){
    cout<<2<<" ";
  }
  cout<<endl;
}

int main(){
  int num;
  int n;
  cin>>n;
  int numZero = 0;
  int numOne = 0;
  int numTwo = 0;
  int arr[n];
  for(int i = 0; i < n; i++){
    cin>>arr[i];
  }
  sort(arr, n);
}
