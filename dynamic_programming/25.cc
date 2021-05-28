#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

template <typename T> concept is_container = requires(T a) {
  a.begin();
  a.end();
};

std::ostream &operator<<(std::ostream &os, const is_container auto &cont) {
  os << '{';
  for (const auto &x : cont) {
    os << x;
    os << " ";
  }
  os << '}';
  return os;
}

int ms(vector<int>& vec, int k){
  std::sort(vec.begin(), vec.end());
  const int size = vec.size();
  vector<int> sums(size);

  auto diff = [&](int i, int j){
    return std::abs(vec.at(i) - vec.at(j));
  };

  auto at = [&](int i){
    return vec.at(i);
  };

  auto sol = [&](int i) -> int&{
    return sums.at(i);
  };

  sol(0) = 0;

  if(diff(0, 1) >= k){
    sol(1) = sol(0);
  }else{
    sol(1) = max(sol(0), at(0) + at(1));
  }

  for(int i = 2; i < size; i++){
    if(diff(i, i - 1) < k){
      sol(i) = max({sol(i - 1), sol(i - 2) + at(i - 1) + at(i)});
    }else{
      sol(i) = sol(i - 1);
    }
  }


  return sol(size - 1);
}


int maxSumPairWithDifferenceLessThanK(int arr[], int N, int K) {
  if(N == 0 || N == 1){
    return 0;
  }
  vector<int> vec;
  std::copy(arr, arr + N, std::back_inserter(vec));
  return ms(vec, K);
}

int main(){
  int n;
  cin>>n;
  vector<int> vec(n);
  for(int i = 0; i < n; i++){
    cin >> vec.at(i);
  }
  int k;
  cin>>k;
  std::cout<<ms(vec, k)<<std::endl;
}
