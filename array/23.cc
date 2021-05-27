#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

int findLongestConseqSubseq(int *arr, int n) {
  std::unordered_set<int> presentSet;
  std::for_each(arr, arr + n, [&presentSet](int c) { presentSet.insert(c); });
  auto isPresent = [&presentSet](int n) {
    return presentSet.find(n) != presentSet.end();
  };
  std::unordered_map<int, int> visitedMap;
  auto isVisited = [&visitedMap](int n) {
    return visitedMap.find(n) != visitedMap.end();
  };
  std::function<int(int)> visit = [&visit, &visitedMap, &isVisited,
                                   &isPresent](int num) {
    if(!isPresent(num)){
      return 0;
    }
    if (isVisited(num)) {
      return visitedMap[num];
    }
    if (!isPresent(num + 1)) {
      visitedMap[num] = 1;
      return visitedMap[num];
    }
    visitedMap[num] = 1 + visit(num + 1);
    return visitedMap[num];
  };
  std::for_each(arr, arr + n, visit);
  int max = 0;
  auto findMaxValue = [&max](auto val) {
    if (val.second > max) {
      max = val.second;
    }
  };
  for_each(visitedMap.begin(), visitedMap.end(), findMaxValue);
  return max;
}

int main(){
  int arr[] = {5, 11, 9, 16, 15, 8, 12, 10};
  std::cout<<findLongestConseqSubseq(arr, 8)<<std::endl;
}
