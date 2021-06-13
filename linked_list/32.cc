#include <iostream>
using namespace std;
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = nullptr;
  }
};

void print(Node* head){
  while(head){
    cout << head->data << " ";
    head = head->next;
  }
  cout << endl;
}

void delete_node(Node* prev, Node* cur){
  if(prev)
    prev->next = cur->next;
}

Node* reverse(Node* head){
  Node* prev = nullptr;
  Node* cur = head;
  while(cur){
    Node* next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  return prev;
}

Node *compute(Node *head) {
  head = reverse(head);
  int max_till_now = head->data;
  auto head_copy = head;
  while(head && head->next){
    if(head->next->data < max_till_now){
      delete_node(head, head->next);
    }else{
      max_till_now = head->next->data;
      head = head->next;
    }
  }
  head = reverse(head_copy);
  return head;
}


int main(int argc, const char** argv) {
  Node arr[] = {32, 433, 636, 121, 831, 102, 695, 509, 104, 776, 905, 876, 219, 202, 326, 393, 141, 752, 504, 109, 640, 765, 537, 759, 971, 857, 147, 716, 897, 484, 60, 928, 268, 47, 48, 98, 500, 94, 607, 603, 221, 863, 831, 439, 416, 156, 183, 556, 259, 686, 16, 250, 450, 552, 9, 772, 409, 155, 487, 305, 990, 898, 232, 258, 945, 631, 707, 444, 724, 313, 47, 296, 527, 229, 734, 942, 736, 268, 849, 995, 953, 865, 244, 754, 416, 604, 526, 176, 110, 364, 832, 100, 262};
  int size = sizeof(arr) / sizeof(Node);
  for(int i = 0; i < size - 1; i++){
    arr[i].next = arr + i + 1;
  }
  Node* head = compute(arr);
  print(head);
    return 0;
}
