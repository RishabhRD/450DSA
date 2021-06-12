#include <iostream>
struct Node {
  int data;
  Node *next;

  Node(int t) : data(t), next(nullptr) {}
};

Node* insert(Node* tail, int data){
  if(tail == nullptr){
    Node* nd = new Node(data);
    return nd;
  }else{
    Node* nd = new Node(data);
    tail->next = nd;
    return nd;
  }
}

Node *findIntersection(Node *head1, Node *head2) {
  Node* first = head1;
  Node* second = head2;
  Node* head = nullptr;
  Node* tail = nullptr;
  while(first != nullptr && second != nullptr){
    if(first->data == second->data){
      tail = insert(tail, first->data);
      if(head == nullptr) head = tail;
      first = first->next;
      second = second->next;
    }else if(first->data > second->data){
      second = second->next;
    }else{
      first = first->next;
    }
  }
  return head;
}

auto print(Node* n){
  while(n != nullptr){
    std::cout << n->data << " " ;
    n = n->next;
  }
  std::cout << std::endl;
}

int main(int argc, const char** argv) {
  Node arr1[] = {1, 2, 3, 4, 6};
  Node arr2[] = {2, 4, 6, 8};
  int n1 = sizeof(arr1) / sizeof(Node);
  int n2 = sizeof(arr2) / sizeof(Node);
  for(int i = 0; i < n1 - 1; i++){
    arr1[i].next = arr1 + i + 1;
  }
  for(int i = 0; i < n2 - 1; i++){
    arr2[i].next = arr2 + i + 1;
  }
  Node* n3 = findIntersection(arr1, arr2);
    return 0;
}
