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

list<list<string>> palindromicPartitionUtil(string currentString, unordered_map<string, list<list<string>>>& stringMapping){
  if(stringMapping.find(currentString) != stringMapping.end()){
    return stringMapping[currentString];
  }
  int n = currentString.size();
  list<list<string>> returningList;
  f(i, 0, n){
    string firstString = currentString.substr(0, i);
    string secondString = currentString.substr(i);
    if(isPalindrome(firstString)){
      list<list<string>> fromOther = palindromicPartitionUtil(secondString, stringMapping);
      for(auto& lst : fromOther){
        lst.push_front(firstString);
      }
      for(auto& lst : fromOther){
        returningList.push_back(lst);
      }
    }
  }
  stringMapping[currentString] = returningList;
  return returningList;
}

list<list<string>> palindromicPartition(string currentString){
  unordered_map<string, list<list<string>>> stringMapping;
  return palindromicPartitionUtil(currentString, stringMapping);
}

int main(){
  string str;
  cin>>str;
  auto returningList = palindromicPartition(str);
  for(auto& lst : returningList){
    print(lst.begin(), lst.end());
  }
}
