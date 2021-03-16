#include <bits/stdc++.h>
using namespace std;

void reverse(vector<int>& vec){
  int size = vec.size();
  for(int i = 0; i < size/2; i++){
    int tmp = vec[i];
    vec[i] = vec[size - i - 1];
    vec[size - i - 1] = tmp;
  }
}

int main(){
  int t;
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    vector<int> vec(n);
    for(int i = 0; i < n; i++){
      cin>>vec[i];
    }
    reverse(vec);
    for(int i = 0; i < n; i++){
      cout<<vec[i]<< " ";
    }
    cout<<endl;
  }
}
