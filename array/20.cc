#include <unordered_set>
#include <iostream>
using namespace std;

bool subArrayExists(int arr[], int n) {
  std::unordered_set<int> st;
  int sum = 0;
  for(int i = 0; i < n ;i++){
    sum+= arr[i];
    if(sum == 0){
      return true;
    }else if(st.find(sum) != st.end()){
      return true;
    }
    st.insert(sum);
  }
  return false;
}
