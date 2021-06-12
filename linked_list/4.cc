#include <iostream>
using namespace std;
struct node{
  int data;
  node* next;

  node(int t) : data(t) , next(nullptr){}
};


node* first_loop_node(node* const head){
  if(head == nullptr) return head;

  node* slow = head;
  node* fast = head;

  node* loop_node = nullptr;

  while(slow != nullptr && fast != nullptr && fast->next != nullptr){
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast){
      loop_node = slow;
      break;
    }
  }

  if(loop_node == nullptr){
    return nullptr;
  }

  int loop_count = 1;
  auto cur_node = loop_node;
  while(true){
    cur_node = cur_node->next;
    if(cur_node != loop_node){
      loop_count++;
    }else{
      break;
    }
  }

  auto second = head;
  for(int i = 0; i < loop_count; i++){
    cur_node = cur_node->next;
  }
  auto first = head;
  while(first != second){
    first = first->next;
    second = second->next;
  }
  return first;
}

int main(int argc, const char** argv) {
  node arr[] = {15, 20, 15, 4, 10};
  int size = sizeof(arr) / sizeof(node);
  for(int i = 0; i < size - 1; i++){
    arr[i].next = arr + i + 1;
  }
  arr[size - 1].next = arr + 2;
  cout << first_loop_node(arr)->data << endl;
    return 0;
}
