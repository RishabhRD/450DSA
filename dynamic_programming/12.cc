#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maximum(int l, int p, int q, int r) {
  std::vector<int> vec(l + 1, -1);
  vec.front() = 0;
  for (int i = 0; i <= l; i++) {
    if (vec[i] == -1)
      continue;
    if (i + p <= l)
      vec[i + p] = max(vec[i + p], vec[i] + 1);
    if (i + q <= l)
      vec[i + q] = max(vec[i + q], vec[i] + 1);
    if (i + r <= l)
      vec[i + r] = max(vec[i + r], vec[i] + 1);
  }
  if (vec[l] == -1)
    vec[l] = 0;
  return vec[l];
}
