#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int lcs(const string& s1) {
  const int sz1 = s1.size();
  const std::string s2 = s1;
  const int sz2 = s2.size();
  vector<vector<int>> ans(sz1 + 1, vector<int>(sz2 + 1));
  auto at =[&](int i, int j) -> int&{
    return ans.at(i).at(j);
  };
  for(int i = 1; i <= sz1; i++){
    for(int j = 1; j <= sz2; j++){
      if(s1.at(i-1) == s2.at(j-1) && i != j){
        at(i, j) = 1 + at(i - 1, j - 1);
      }else{
        at(i, j) = max(at(i - 1, j), at(i, j - 1));
      }
    }
  }
  return at(sz1, sz2);
}

int main(){
  std::cout<<lcs("axxxy")<<std::endl;
}
