#include <iostream>
#include <vector>

using namespace std;

vector <int> commonElements (int A[], int B[], int C[], int n1, int n2, int n3) {
  int i = 0, j = 0, k = 0;
  vector<int> result;
  while(i < n1 && j < n2 && k < n3){
    if(A[i] == B[j] && B[j] == C[k]){
      if(result.size() == 0){
        result.push_back(A[i]);
      }else{
        if(result.back() != A[i]){
          result.push_back(A[i]);
        }
      }
      i++;
      j++;
      k++;
    }else if(A[i] < B[j]){
      i++;
    }else if(B[j] < C[k]){
      j++;
    }else{
      k++;
    }
  }
  return result;
}

int main(){
  int n1, n2, n3;
  cin>>n1>>n2>>n3;
  int arr[n1], brr[n2], crr[n3];
  for(int i = 0; i < n1; i++){
    cin>>arr[i];
  }
  for(int i = 0; i < n2; i++){
    cin>>brr[i];
  }
  for(int i = 0; i < n3; i++){
    cin>>crr[i];
  }
  auto vec = commonElements(arr, brr, crr, n1, n2, n3);
  for(int x : vec){
    cout<<x<<" ";
  }
  cout<<endl;
}
