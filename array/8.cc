
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

int getMinDiff(int arr[], int n, int k) {
  sort(arr, arr + n);
  int max = arr[0];
  int min = arr[0];
  for(int i = 1; i < n; i++){
    if(arr[i] < min){
      min = arr[i];
    }
    if(arr[i] > max){
      max = arr[i];
    }
  }
  if(max - k >= 0){
    max = max - k;
    min = min + k;
    return max - min;
  }else{
    return max - min;
  }
}

int main()
{
  int k, n;
  cin>>k>>n;
  int arr[n];
  f(i, 0, n){
    cin>>arr[i];
  }
  print(getMinDiff(arr, n, k));
}
