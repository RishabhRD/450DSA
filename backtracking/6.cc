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
  while(begin != end){
    cout<<*begin<<" ";
    begin++;
  }
  cout << endl;
}

bool isPalindrome(string& str){
  int n = str.size();
  f(i, 0, n){
    if(str[i] != str[n - i -1]){
      return false;
    }
  }
  return true;
}

list<list<string>> palindromicPartition(string currentString){
  int n = currentString.size();
  list<list<string>> returningList;
  if(n == 0){
    return returningList;
  }
  if(isPalindrome(currentString)){
    list<string> lst {currentString};
    returningList.push_back(lst);
  }
  f(i, 0, n){
    string firstString = currentString.substr(0, i+1);
    string secondString = currentString.substr(i+1);
    if(isPalindrome(firstString)){
      list<list<string>> fromOther = palindromicPartition(secondString);
      for(auto& lst : fromOther){
        lst.push_front(firstString);
        returningList.push_back(lst);
      }
    }
  }
  return returningList;
}


int main(){
  string str;
  cin>>str;
  list<list<string>> lst = palindromicPartition(str);
  for(auto& l : lst){
    print(l.begin(), l.end());
  }
}
