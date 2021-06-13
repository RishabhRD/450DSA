#include <iostream>
using namespace std;
struct Node
{
  int data;
  struct Node *next;
  
  Node(int x){
      data = x;
      next = nullptr;
  }
};
void splitList(Node *head, Node **head1_ref, Node **head2_ref) {
  if(head->next == head){
    *head1_ref = head;
    *head2_ref = nullptr;
    return;
  }
  auto slow = head;
  auto fast = head;
  while(fast->next->next != head && fast->next != head){
    slow = slow->next;
    fast = fast->next->next;
  }
  auto first_head = head;
  auto first_tail = slow;
  auto second_head = slow->next;
  auto second_tail = (fast->next == head) ? fast : fast->next;
  first_tail->next = first_head;
  second_tail->next = second_head;
  *head1_ref = first_head;
  *head2_ref = second_head;
}

int main(int argc, const char** argv) {
  Node arr[] = {1, 2, 3, 4, 5};
  int size = sizeof(arr) / sizeof(Node);
  for(int i = 0; i < size - 1; i++){
    arr[i].next = arr + i + 1;
  }
  arr[size - 1].next = arr;
  Node* head1 = nullptr;
  Node* head2 = nullptr;
  splitList(arr, &head1, &head2);
    return 0;
}
