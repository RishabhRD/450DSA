#include <unordered_set>
struct Node {
  int data;
  Node *next;

  Node(int t) : data(t), next(nullptr) {}
};

void remove(Node *prev, Node *cur) {
  prev->next = cur->next;
  cur->next = nullptr;
}

Node *removeDuplicates(Node *head) {
  std::unordered_set<int> st;
  auto contains = [&](int i){
    return st.find(i) != st.end();
  };
  auto push = [&](int i){
    st.insert(i);
  };
  Node* cur = head;
  Node* prev = nullptr;
  while(cur != nullptr){
    if(prev == nullptr){
      push(cur->data);
      prev = cur;
      cur = cur->next;
    }else if(contains(cur->data)){
      auto next = cur->next;
      remove(prev, cur);
      cur = next;
    }else{
      push(cur->data);
      prev = cur;
      cur = cur->next;
    }
  }
  return head;
}
