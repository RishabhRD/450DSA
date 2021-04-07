
#include <bits/stdc++.h>
using namespace std;

#define f(i, k, n) for (int i = 0; i < n; i++)
#define fo(i, k, n) for (i = 0; i < n; i++)

template <typename T> void print(T ele, string message = "") {
  cout << message << ele << endl;
}

template <typename T> void print(T begin, T end, string message = "") {
  cout << message;
  while (begin < end) {
    cout << *begin << " ";
    begin++;
  }
  cout << endl;
}

template <typename Iter> Iter minInInterator(Iter i1, Iter i2) {
  if (*i1 < *i2) {
    return i1;
  } else {
    return i2;
  }
}

template <typename Iter> Iter other(Iter i1, Iter i2, Iter given) {
  if (given == i1) {
    return i2;
  } else {
    return i1;
  }
}

template <typename Iter> auto valueDiff(Iter i1, Iter i2) {
  auto smaller = minInInterator(i1, i2);
  auto greater = other(i1, i2, smaller);
  return *greater - *smaller;
}

template <typename Iter>
bool isSame(Iter i1, Iter i2, Iter begin1, Iter begin2) {
  return begin1 - i1 == begin2 - i2;
}

template <typename Iter>
void updateMinValueIfNotEqual(Iter i1, Iter i2, Iter begin1, Iter begin2,
                              bool multipleI1, bool multipleI2,
                              int &currentMinimum) {
  if (isSame(i1, i2, begin1, begin2) || multipleI1 || multipleI2) {
    currentMinimum = std::min(currentMinimum, valueDiff(i1, i2));
    cout << "Value: "<<*i1 << " " << *i2 << endl;
    cout << "Index: "<<i1 - begin1 << " " << i2 - begin2 << endl;
  }
}

template <typename Iter> bool multipleSame(Iter given, Iter begin, Iter end) {
  for (auto itr = begin; itr != end; itr = std::next(itr)) {
    if (itr != given && *itr == *given) {
      return true;
    }
  }
  return false;
}

int getMinDiff(int arr[], int n, int k) {
  std::vector<int> notChanged;
  std::vector<int> increasedByK;
  std::vector<int> decreasedByK;
  auto pushElementOfArray = [arr, &notChanged](auto ele) {
    notChanged.push_back(ele);
  };
  auto pushWithIncrease = [arr, &increasedByK, k](auto ele) {
    increasedByK.push_back(ele + k);
  };
  auto pushWithDecrease = [arr, &decreasedByK, k](auto ele) {
    if (ele >= k) {
      decreasedByK.push_back(ele - k);
    } else {
      decreasedByK.push_back(ele + k);
    }
  };
  std::for_each(arr, arr + n, pushElementOfArray);
  std::for_each(arr, arr + n, pushWithIncrease);
  std::for_each(arr, arr + n, pushWithDecrease);
  auto minNotChanged = std::min_element(notChanged.begin(), notChanged.end());
  auto maxNotChanged = std::max_element(notChanged.begin(), notChanged.end());
  auto minIncreased =
      std::min_element(increasedByK.begin(), increasedByK.end());
  auto maxIncreased =
      std::max_element(increasedByK.begin(), increasedByK.end());
  auto minDecreased =
      std::min_element(decreasedByK.begin(), decreasedByK.end());
  auto maxDecreased =
      std::max_element(decreasedByK.begin(), decreasedByK.end());
  auto minAnswer = *maxNotChanged - *minNotChanged;
  minAnswer = std::min(minAnswer, *maxIncreased - *minIncreased);
  minAnswer = std::min(minAnswer, *maxDecreased - *minDecreased);
  bool multipleMinNotChanged =
      multipleSame(minNotChanged, notChanged.begin(), notChanged.end());
  bool multipleMaxNotChanged =
      multipleSame(maxNotChanged, notChanged.begin(), notChanged.end());
  bool multipleMinDecreased =
      multipleSame(minIncreased, increasedByK.begin(), increasedByK.end());
  bool multipleMaxDecreased =
      multipleSame(maxIncreased, increasedByK.begin(), increasedByK.end());
  bool multipleMinIncreased =
      multipleSame(minDecreased, decreasedByK.begin(), decreasedByK.end());
  bool multipleMaxIncreased =
      multipleSame(maxDecreased, decreasedByK.begin(), decreasedByK.end());
  print(increasedByK.begin(), increasedByK.end());
  print(decreasedByK.begin(), decreasedByK.end());
  updateMinValueIfNotEqual(minIncreased, minDecreased, increasedByK.begin(),
                           decreasedByK.begin(), multipleMinIncreased,
                           multipleMinDecreased, minAnswer);
  updateMinValueIfNotEqual(minIncreased, maxDecreased, increasedByK.begin(),
                           decreasedByK.begin(), multipleMinIncreased,
                           multipleMaxDecreased, minAnswer);
  updateMinValueIfNotEqual(maxIncreased, minDecreased, increasedByK.begin(),
                           decreasedByK.begin(), multipleMaxIncreased,
                           multipleMinDecreased, minAnswer);
  updateMinValueIfNotEqual(maxIncreased, maxDecreased, increasedByK.begin(),
                           decreasedByK.begin(), multipleMaxIncreased,
                           multipleMaxDecreased, minAnswer);
  return minAnswer;
}

int main() {
  int n, k;
  cin >> k >> n;
  int arr[n];
  f(i, 0, n) { cin >> arr[i]; }
  print(getMinDiff(arr, n, k));
}
