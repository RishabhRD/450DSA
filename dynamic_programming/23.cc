#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct val {
  int first;
  int second;
};

bool operator<(const val &v1, const val &v2) { return v1.second < v2.first; }

int mcl(vector<val> &vec) {
  // sort because subsequence is not given in problem
  std::sort(vec.begin(), vec.end(), [](const auto &first, const auto &second) {
    /* if (first.first == second.first) { */
    /*   return first.second >= second.first; */
    /* } */
    return first.first < second.first;
  });
  const int size = vec.size();
  vector<int> nums(size);
  nums.at(0) = 1;
  for (int i = 1; i < size; i++) {
    nums.at(i) = 1;
    for (int j = 0; j < i; j++) {
      if (vec.at(j) < vec.at(i)) {
        if (nums.at(i) < 1 + nums.at(j)) {
          nums.at(i) = 1 + nums.at(j);
        }
      }
    }
  }
  return *max_element(nums.begin(), nums.end());
}

int maxChainLen(val p[], int n) {
  vector<val> vec(n);
  std::copy(p, p + n, std::back_inserter(vec));
  return mcl(vec);
}

int main() {
  int n;
  vector<val> vec;
  cin >> n;
  for(int i = 0; i < n; i++){
    val v;
    cin>>v.first;
    cin >> v.second;
    vec.push_back(v);
  }
  std::cout<<mcl(vec)<<std::endl;
}
