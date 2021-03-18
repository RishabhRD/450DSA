#include <bits/stdc++.h>
using namespace std;

#define f(i, k, n) for (int i = k; i < n; i++)
#define fo(i, k, n) for (i = k; i < n; i++)

template <typename T> void print(T ele, string message = "") {
  cout << message << ele << endl;
}

template <typename T> void print(T begin, T end, string message = "") {
  cout << message;
  while (begin != end) {
    cout << *begin << " ";
    begin++;
  }
  cout << endl;
}

template <typename T> T toNumber(const string &s) {
  T answer = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    T num = s[i] - '0';
    answer = (answer * 10) + num;
  }
  return answer;
}

using ll = long long;
#define toInt toNumber<int>
#define toLL toNumber<ll>
#define toLong toLong<long>

void permuteUtil(string &str, int currentIndex, set<string> &answer) {
  int size = str.size();
  if (currentIndex >= size) {
    return;
  }

  f(i, currentIndex, size) {
    swap(str[i], str[currentIndex]);
    answer.insert(str);
    permuteUtil(str, currentIndex + 1, answer);
    swap(str[i], str[currentIndex]);
  }
}

vector<string> find_permutation(string S) {
  vector<string> answer;
  set<string> realAnswer;
  permuteUtil(S, 0, realAnswer);
  for(auto& s : realAnswer){
    answer.push_back(s);
  }
  return answer;
}
