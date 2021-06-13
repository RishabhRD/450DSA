#include <iostream>
#include <utility>
struct Node {
  int data;
  Node *next;
  Node *prev;
  Node(int x) {
    data = x;
    next = nullptr;
    prev = nullptr;
  }
};

Node* reverseDLL(Node * head) {
  Node* new_head = nullptr;
  while(head != nullptr){
    new_head = head;
    auto next = head->next;
    std::swap(head->next, head->prev);
    head = next;
  }
  return new_head;
}

void print(Node* head){
  while(head){
    std::cout << head->data << " ";
    head = head->next;
  }
  std::cout << std::endl;
}

int main(int argc, const char** argv) {
  Node arr[] = {1, 2, 3, 4, 5};
  int size = sizeof(arr) / sizeof(Node);
  arr[0].prev = nullptr;
  arr[size - 1].next = nullptr;
  for(int i = 0; i < size - 1; i++){
    arr[i].next = arr + i + 1;
  }
  for(int i = 1; i < size; i++){
    arr[i].prev = arr + i - 1;
  }
  print(arr);
  Node* some = reverseDLL(arr);
  print(some);
    return 0;
}
