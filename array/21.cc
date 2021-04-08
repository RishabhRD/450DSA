#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

unordered_map<int, string> mp;

string operator*(const string &num1, const string &num2) {
  int len1 = num1.size();
  int len2 = num2.size();
  if (len1 == 0 || len2 == 0)
    return "0";

  vector<int> result(len1 + len2, 0);

  int i_n1 = 0;
  int i_n2 = 0;

  for (int i = len1 - 1; i >= 0; i--) {
    int carry = 0;
    int n1 = num1[i] - '0';
    i_n2 = 0;

    for (int j = len2 - 1; j >= 0; j--) {
      int n2 = num2[j] - '0';

      int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

      carry = sum / 10;

      result[i_n1 + i_n2] = sum % 10;

      i_n2++;
    }

    if (carry > 0)
      result[i_n1 + i_n2] += carry;
    i_n1++;
  }

  int i = result.size() - 1;
  while (i >= 0 && result[i] == 0)
    i--;
  if (i == -1)
    return "0";

  string s = "";

  while (i >= 0)
    s += std::to_string(result[i--]);

  return s;
}

string factorialUtil(int n){
  if(n == 0 || n == 1){
    return "1";
  }
  if(mp.find(n) != mp.end()){
    return mp[n];
  }
  auto answer = to_string(n) * factorialUtil(n - 1);
  mp[n] = answer;
  return answer;
}

vector<int> factorial(int n){
  const auto answer = factorialUtil(n);
  vector<int> answerVector;
  for(char c : answer){
    answerVector.push_back(c);
  }
  return answerVector;
}





int main()
{
  auto answer = factorialUtil(3);
  print(answer.begin(), answer.end());
}
