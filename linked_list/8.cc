struct Node {
  int data;
  Node *next;

  Node(int t) : data(t), next(nullptr) {}
};

Node *addOne(Node *head) {
  if(head == nullptr) return nullptr;
  Node* cur = head;
  auto incr = [](Node* nd){
    if(nd->data == 9)
      nd->data = 0;
    else
      nd->data = nd->data + 1;
  };

  auto decr = [](Node* nd){
    if(nd->data == 0){
      nd->data = 9;
    }else
      nd->data = nd->data -1;
  };
  Node* last_non_zero = nullptr;
  while(cur != nullptr){
    incr(cur);
    if(cur->data != 0){
      last_non_zero = cur;
    }
    cur = cur->next;
  }
  if(last_non_zero == nullptr){
    Node* nd = new Node(1);
    nd->next = head;
    return nd;
  }
  cur = head;
  while(cur != last_non_zero){
    decr(cur);
    cur = cur->next;
  }
  return head;
}
