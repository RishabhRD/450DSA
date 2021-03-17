#include <bits/stdc++.h>
using namespace std;

#define f(i,k,n) for(int i = 0; i < n; i++)
#define fo(i,k,n) for(i = 0; i < n; i++)

template<typename T>
void print(T ele, string message = ""){
  cout<<message<<ele<<endl;
}

template<typename T>
void print(T begin, T end, string message = ""){
  cout<<message;
  while(begin < end){
    cout<<*begin<<" ";
    begin++;
  }
  cout << endl;
}

bool isValid(const string& s){
  int count = 0;
  for(char c : s){
    if(c == '('){
      count ++;
    }else if(c == ')'){
      count --;
    }
    if(count < 0){
      return false;
    }
  }
  if(count == 0){
    return true;
  }
  return false;
}

string removeI(string& str, int index){
  return str.substr(0, index) + str.substr(index + 1);
}

bool isParenthesis(char c){
  if( c == '(' || c == ')'){
    return true;
  }
  return false;
}

vector<string> removeInvalidParentheses(string s) {
  vector<string> returningVector;
  if(s.empty()){
    return returningVector;
  }
  unordered_set<string> visitedStrings;
  queue<string> traversalQueue;
  bool level;
  traversalQueue.push(s);
  visitedStrings.insert(s);
  while(!traversalQueue.empty()){
    string str = traversalQueue.front();
    traversalQueue.pop();
    if(isValid(str)){
      level = true;
      returningVector.push_back(str);
    }
    if(level){
      continue;
    }
    int n = str.size();
    f(i, 0, n){
      if(!isParenthesis(str[i])){
        continue;
      }
      string temp = removeI(str, i);
      if(visitedStrings.find(temp) == visitedStrings.end()){
        traversalQueue.push(temp);
        visitedStrings.insert(temp);
      }
    }
  }
  return returningVector;
}

int main()
{
  string str;
  cin>>str;
  vector<string> vec = removeInvalidParentheses(str);
  print(vec.begin(), vec.end());
}
