#include <iostream>

using namespace std;

struct Node{
  int data;
  Node* next;

  Node(int t) : data(t) , next(nullptr){}
};

void remove(Node* prev, Node* cur){
  prev->next = cur->next;
  cur->next = nullptr;
}

Node* removeDuplicates(struct Node *head) {
  if(head == nullptr) return head;
  Node* cur = head;
  Node* prev = nullptr;
  while(cur != nullptr){
    if(prev == nullptr){
      prev = cur;
      cur = cur->next;
    } else if(prev->data == cur->data){
      Node* next = cur->next;
      remove(prev, cur);
      cur = next;
    }else{
      prev = cur;
      cur = cur->next;
    }
  }
  return head;
}

void print(Node* head){
  while(head != nullptr){
    cout << head->data << " " ;
    head = head->next;
  }
  cout << endl;
}

int main(int argc, const char** argv) {
  Node arr[] = {6, 3, 71, 74, 82, 97};
  int size = sizeof(arr) / sizeof(Node);
  for(int i = 0; i < size - 1; i++){
    arr[i].next = arr + i + 1;
  }
  removeDuplicates(arr);
  print(arr);
  return 0;
}
