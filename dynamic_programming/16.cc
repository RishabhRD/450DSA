#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using itr = string::const_iterator;

constexpr int lcs(itr firstCurrent, itr secondCurrent, itr firstEnd, itr secondEnd){
  if(firstCurrent == firstEnd) return 0;
  if(secondCurrent == secondEnd) return 0;
  if(*firstCurrent == *secondCurrent){
    return 1 + lcs(firstCurrent + 1, secondCurrent + 1, firstEnd, secondEnd);
  }else{
    return max(lcs(firstCurrent, secondCurrent + 1, firstEnd, secondEnd),
        lcs(firstCurrent + 1, secondCurrent, firstEnd, secondEnd));
  }
}

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

void printMatrix(const is_container auto &cont) {
  for (const auto &x : cont) {
    cout << x;
    cout << "\n";
  }
}

int lcs(int x, int y, const string& s1, const string& s2) {
  const int sz1 = s1.size();
  const int sz2 = s2.size();
  vector<vector<int>> ans(2, vector<int>(sz2 + 1));
  auto at =[&](int i, int j) -> int&{
    return ans.at(i).at(j);
  };
  int current = 0;
  for(int i = 1; i <= sz1; i++){
    current = 1 - current;
    for(int j = 1; j <= sz2; j++){
      if(s1.at(i-1) == s2.at(j-1)){
        at(current, j) = 1 + at(1 - current, j - 1);
      }else{
        at(current, j) = max(at(1 - current, j), at(current, j - 1));
      }
    }
  }
  return at(current, sz2);
}

int main(){
  std::string s1 = "ABCDGH";
  std::string s2 = "AEDFHR";
  std::cout<<lcs(s1.size(), s2.size(), s1, s2)<<std::endl;
}
