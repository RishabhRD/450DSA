#include <bits/stdc++.h>
using namespace std;

bool lessThan(int a, int b){
  return a > b;
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

template<typename T>
void print(T ele, string message = ""){
  cout<<message<<ele<<endl;
}

// O(k log n)
int ksmallestUsingHeap(int* arr, int l, int r, int k){
  make_heap(arr + l, arr + r, lessThan);
  print(arr + l, arr + r);
  for(int i = 0; i < k - 1; i++){
    pop_heap(arr + l, arr + r, lessThan);
    r--;
  }
  return arr[0];
}

int partition(int* arr, int l, int r){
  int x = arr[r - 1];
  int i = l;
  for(int j = l; j < r - 1; j++){
    if(arr[j] <= x){
      swap(arr[j], arr[i]);
      i++;
      print(arr + l, arr + r, "Array: ");
    }
    swap(arr[i], arr[r - 1]);
  }
  return i;
}

// If all elements are distinct then O(n) using quick select
int ksmallestUsingQuickSelect(int* arr, int l, int r, int k){
  print(k, "K: ");
  if( k > 0 && k <= r - l){
    int pos = partition(arr, l, r);
    /* print(arr + l, arr +r); */
    /* print(arr[pos], "Array element: "); */
    if(pos - l == k - 1){
      return arr[pos];
    }
    if(pos - l > k - 1){
      return ksmallestUsingQuickSelect(arr, l, pos - 1, k);
    }
    return ksmallestUsingQuickSelect(arr, pos + 1, r, (k - 1) - (pos - l));
  }
  return INT32_MAX;
}

int main(){
  int n;
  cin>>n;
  int k;
  cin>>k;
  int arr[n];
  for(int i = 0; i < n; i++){
    cin>>arr[i];
  }
    print(arr + 0, arr +n);
  cout<<ksmallestUsingQuickSelect(arr, 0, n , k)<<endl;
}
