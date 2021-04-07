#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
bool isMergeable(const vector<int> &v1, const vector<int> &v2) {
  return v2[0] <= v1[1];
};
vector<int> mergeVector(const vector<int> &v1, const vector<int> &v2) {
  vector<int> result = {v1[0], v2[1]};
  return result;
};

bool cmp(const vector<int>& v1, const vector<int>& v2){
  if(v1[0] < v2[0]){
    return true;
  }else if((v1[0] == v2[0]) && (v1[1] < v2[1])){
    return true;
  }
  return false;
}

void print(const vector<vector<int>>& resultVector){
  for(const auto& vec : resultVector){
    for(const int x : vec){
      cout<<x<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}

vector<vector<int>> merge(vector<vector<int>> &intervals) {
  std::sort(intervals.begin(), intervals.end(), cmp);
  vector<vector<int>> resultVector;
  int firstIndex = 0;
  int secondIndex = 1;
  bool merged = false;
  vector<int> mergedVector = intervals[0];
  for(const auto& it : intervals){
    if(it.at(0) <= mergedVector.at(1)){
      mergedVector[1] = std::max(it.at(1), mergedVector.at(1));
    }else{
      resultVector.push_back(mergedVector);
      mergedVector = it;
    }
  }
  resultVector.push_back(mergedVector);
  return resultVector;
}

int main()
{
  vector<vector<int>> vec;
  int a, b;
  int n;
  cin>>n;
  while(n -- ){
    cin>>a>>b;
    vector<int> inner{a, b};
    vec.push_back(inner);
  }
  auto result = merge(vec);
  print(result);
}
