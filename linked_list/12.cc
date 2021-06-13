#include <cmath>
#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *next;

  Node(int t) : data(t), next(nullptr) {}
};

auto print(Node* n,  Node* end = nullptr){
  while(n != end){
    std::cout << n->data << " " ;
    n = n->next;
  }
  std::cout << endl;
}

auto print(Node* n,  int size){
  for(int i = 0; i < size && n != nullptr; i++){
    std::cout << n->data << " " ;
    n = n->next;
  }
  std::cout << endl;
}


Node* advance(Node* head, int k){
  for(int i = 0; i < k && head != nullptr; i++){
    head = head->next;
  }
  return head;
}

void add(Node*& head, Node*& tail, int data){
  Node* nd = new Node(data);
  if(head == nullptr){
    head = nd;
    tail = nd;
  }else{
    tail->next = nd;
    tail = nd;
  }
}

void merge(Node* first, Node* second, int first_size, int second_size){
  Node* first_head = nullptr;
  Node* first_tail = nullptr;
  Node* first_copy = first;
  for(int i = 0; i < first_size && first_copy != nullptr; i++){
    add(first_head, first_tail, first_copy->data);
    first_copy = first_copy->next;
  }
  Node* second_copy = second;
  Node* second_head = nullptr;
  Node* second_tail = nullptr;
  for(int i = 0; i < second_size && second_copy != nullptr; i++){
    add(second_head, second_tail, second_copy->data);
    second_copy = second_copy->next;
  }
  while(first_head != nullptr && second_head != nullptr){
    if(first_head->data < second_head->data){
      first->data = first_head->data;
      first_head = first_head->next;
    }else{
      first->data = second_head->data;
      second_head = second_head->next;
    }
    first = first->next;
  }
  while(first_head != nullptr){
    first->data = first_head->data;
    first_head = first_head->next;
    first = first->next;
  }
  while(second_head != nullptr){
    first->data = second_head->data;
    second_head = second_head->next;
    first = first->next;
  }
}

void merge_sort(Node* head, int size){
  if(size == 0 || size == 1) return;
  int first_size = ceil((double)size / 2);
  int second_size = size - first_size;
  Node* first_head = head;
  Node* second_head = advance(head, first_size);
  merge_sort(first_head, first_size);
  merge_sort(second_head, second_size);
  merge(first_head, second_head, first_size, second_size);
}

Node *mergeSort(Node *head) {
  int size = 0;
  Node* head_copy = head;
  while(head_copy != nullptr){
    size++;
    head_copy = head_copy->next;
  }
  merge_sort(head, size);
  return head;
}

int main(int argc, const char** argv) {
  Node arr[] = {8, 9, 5, 7, 2};
  int size = sizeof(arr) / sizeof(Node);
  for(int i = 0; i < size - 1; i++){
    arr[i].next = arr + i + 1;
  }
  print(arr);
  mergeSort(arr);
  print(arr);
    return 0;
}
