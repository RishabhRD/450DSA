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

int doUnion(int a[], int n, int b[], int m){
  sort(a, a + n);
  sort(b, b + m);
  int i = 0;
  int j = 0;
  int size = 0;
  int lastElementEntered = INT_MIN;
  while(true){
    if(i >= n){
      while(j < m){
        if(b[j] > lastElementEntered){
          size++;
          lastElementEntered = b[j];
        }
        j++;
      }
      break;
    }
    if(j >= m){
      while(i < n){
        if(a[i] > lastElementEntered){
          size++;
          lastElementEntered = a[i];
        }
        i++;
      }
      break;
    }
    if(a[i] == b[j]){
      if(a[i] > lastElementEntered){
        lastElementEntered = a[i];
        size++;
      }
      i++;
      j++;
    }else if(a[i] < b[j]){
      if(a[i] > lastElementEntered){
        lastElementEntered = a[i];
        size++;
      }
      i++;
    }else{
      if(b[j] > lastElementEntered){
        lastElementEntered = b[j];
        size++;
      }
      j++;
    }
  }
  return size;
}

int main()
{
  int n;
  cin>>n;
  int arr[n];
  for(int i = 0; i < n; i++){
    cin>>arr[i];
  }
  int m;
  cin>>m;
  int brr[m];
  for(int i = 0; i < m ;i++){
    cin>>brr[i];
  }
  print(doUnion(arr, n, brr , m));
}
