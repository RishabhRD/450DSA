#include <tuple>
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = nullptr;
  }
};

Node *segregate(Node *head) {
  std::array<int, 3> arr = {0, 0, 0};
  Node* begin = head;
  while(begin){
    arr[begin->data]++;
    begin = begin->next;
  }
  begin = head;
  int cur = 0;
  while(begin){
    if(arr[cur] == 0){ 
      cur++;
      continue;
    }
    begin->data = cur;
    arr[cur]--;
    begin = begin->next;
  }
  return head;
}
