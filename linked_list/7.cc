struct Node {
  int data;
  Node *next;

  Node(int t) : data(t), next(nullptr) {}
};

Node* move_last(Node* head){
  if(head == nullptr) return head;
  Node* prev = nullptr;
  Node* cur = head;
  while(cur->next != nullptr){
    prev = cur;
    cur = cur->next;
  }
  if(prev != nullptr){
    prev->next = nullptr;
    cur->next = head;
  }
  return cur->next;
}
