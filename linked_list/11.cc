#include <algorithm>
using namespace std;
struct Node {
  int data;
  Node *next;

  Node(int t) : data(t), next(nullptr) {}
};

int size(Node* head){
  if(head == nullptr) return 0;
  int size = 0;
  while(head != nullptr){
    size++;
    head = head->next;
  }
  return size;
};

int intersectPoint(Node* head1, Node* head2, int n1, int n2){
  if(n1 > n2){
    return intersectPoint(head2, head1, n2, n1);
  }
  int diff = n2 - n1;
  for(int i = 0; i < diff; i++){
    head2 = head2->next;
  }
  while(head1 && head2){
    if(head1 == head2){
      return head1->data;
    }
    head1 = head1->next;
    head2 = head2->next;
  }
  return -1;
}

int intersectPoint(Node *head1, Node *head2) {
  int n1 = size(head1);
  int n2 = size(head2);
  return intersectPoint(head1, head2, n1, n2);
}

