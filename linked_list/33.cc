#include <unistd.h>
#include <iostream>
using namespace std;
struct Node
{
    int data;
    struct Node* next;
    
    Node(int x){
        data = x;
        next = nullptr;
    }
};

void add(Node*& new_head, Node*& new_tail, Node* nd){
  if(new_head == nullptr){
    new_head = nd;
    new_tail = nd;
  }else{
    new_tail->next = nd;
    nd->next = nullptr;
    new_tail = nd;
  }
}

Node* del_node(Node* prev, Node* cur){
  if(prev)
    prev->next = cur->next;
  return cur;
}

Node *divide(int N, Node *head) {
  Node* prev = nullptr;
  auto begin = head;
  Node* new_head = nullptr;
  Node* new_tail = nullptr;
  while(begin){
    if(begin->data % 2 == 0){
      auto next = begin->next;
      Node* even_node = del_node(prev, begin);
      if(prev == nullptr) head = next;
      add(new_head, new_tail, even_node);
      begin = next;
    }else{
      prev = begin;
      begin = begin->next;
    }
  }
  if(new_head){
    new_tail->next = head;
    return new_head;
  }else{
    return head;
  }
}

void print(Node* head){
  while(head){
    cout << head->data << endl;
    head = head->next;
    sleep(1);
  }
  cout << endl;
}

int main(int argc, const char** argv) {
  Node arr[] = {12, 9, 4, 8, 7, 3, 2};
  int size = sizeof(arr) / sizeof(Node);
  for(int i = 0; i < size - 1; i++){
    arr[i].next = arr + i + 1;
  }
  Node* head = divide(size, arr);
  print(head);
    return 0;
}
