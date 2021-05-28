#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using itr = string::const_iterator;

constexpr int lcs(itr firstCurrent, itr secondCurrent, itr firstEnd,
                  itr secondEnd) {
  if (firstCurrent == firstEnd)
    return 0;
  if (secondCurrent == secondEnd)
    return 0;
  if (*firstCurrent == *secondCurrent) {
    return 1 + lcs(firstCurrent + 1, secondCurrent + 1, firstEnd, secondEnd);
  } else {
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

int lcs(const string &s1, const string &s2, const string &s3, int, int, int) {
  const int sz1 = s1.size();
  const int sz2 = s2.size();
  const int sz3 = s3.size();
  vector<vector<vector<int>>> ans(
      sz1 + 1, vector<vector<int>>(sz2 + 1, vector<int>(sz3 + 1)));
  auto at = [&](int i, int j, int k) -> int & { return ans.at(i).at(j).at(k); };
  for (int i = 1; i <= sz1; i++) {
    for (int j = 1; j <= sz2; j++) {
      for (int k = 1; k <= sz3; k++) {
        if (s1.at(i - 1) == s2.at(j - 1) && s2.at(j - 1) == s3.at(k - 1)) {
          at(i, j, k) = 1 + at(i - 1, j - 1, k - 1);
        } else {
          at(i, j, k) = std::max({at(i - 1, j, k), at(i, j - 1, k), at(i, j, k - 1)});
        }
      }
    }
  }
  return at(sz1, sz2, sz3);
}

int main() {
  std::string s1 = "geeks";
  std::string s2 = "geeksfor";
  std::string s3 = "geeksforgeeks";
  std::cout << lcs(s1, s2, s3, s1.size(), s2.size(), s3.size()) << std::endl;
}
