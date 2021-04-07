#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long int;

template <typename Iter> auto crossInversion(Iter begin, Iter mid, Iter end) {
  //TODO: how to declare ll here
  std::vector<ll> leftVector;
  auto inserterIter = std::back_inserter(leftVector);
  std::copy(begin, mid, inserterIter);
  std::vector<ll> rightVector;
  inserterIter = std::back_inserter(rightVector);
  std::copy(mid, end, inserterIter);
  auto beginLeft = leftVector.begin();
  auto beginRight = rightVector.begin();
  auto firstLeft = leftVector.begin();
  auto lastLeft = leftVector.end();
  auto firstRight = rightVector.begin();
  auto lastRight = rightVector.end();
  ll numInversions = 0;
  Iter dest = begin;
  for (; firstLeft != lastLeft; dest++) {
    if (firstRight == lastRight) {
      std::copy(firstLeft, lastLeft, dest);
      break;
    }
    if (*firstLeft <= *firstRight) {
      *dest = *firstLeft;
      firstLeft++;
    } else {
      numInversions += lastLeft - firstLeft;
      *dest = *firstRight;
      firstRight++;
    }
  }
  std::copy(firstRight, lastRight, dest);
  return numInversions;
}

template <typename Iter> auto inversionUtil(Iter begin, Iter end) {
  /* std::cout<<end - begin<<std::endl; */
  if (end - begin <= 1) {
    return ll(0);
  }
  auto diff = end - begin;
  Iter mid = begin + diff/2;
  auto firstHalfInversion = inversionUtil(begin, mid);
  auto secondHalfInversion = inversionUtil(mid, end);
  return firstHalfInversion + secondHalfInversion +
         crossInversion(begin, mid, end);
}

ll inversionCount(ll arr[], ll N) {
  return inversionUtil(arr, arr + N);
}

int main()
{
  ll arr[] = {2, 4, 1, 3, 5};
  std::cout<<inversionCount(arr, 5)<<std::endl;
}
