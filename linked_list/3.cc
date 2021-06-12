#include <iostream>
using namespace std;
struct Node {
  const int data;
  Node* next;
  Node(int x) : data(x), next(nullptr){
  }
};
void removeLoop(Node* head) {
  if(head == nullptr){
    return;
  }
  auto slow = head;
  auto fast = head;
  Node* loop_ptr = nullptr;
  while(slow != nullptr && fast != nullptr && fast->next != nullptr){
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast){
      loop_ptr = slow;
      break;
    }
  }
  if(loop_ptr == nullptr){
    return;
  }
  int loop_count = 0;
  auto next_ptr = loop_ptr;
  while(true){
    next_ptr = next_ptr->next;
    if(next_ptr == loop_ptr){
      break;
    }
    loop_count++;
  }

  auto start = head;
  for(int i = 0; i <= loop_count; i++){
    start = start->next;
  }

  auto first = head;
  auto second = start;
  while(first != second){
    first = first->next;
    second = second->next;
  }
  while(second->next != first){
    second = second->next;
  }
  second->next = nullptr;
}

int main(int argc, const char** argv) {
  Node arr[] = {15, 20, 15, 4, 10};
  int size = sizeof(arr) / sizeof(Node);
  for(int i = 0; i < size - 1; i++){
    arr[i].next = arr + i + 1;
  }
  arr[size - 1].next = arr + 2;
  removeLoop(arr);
    return 0;
}
