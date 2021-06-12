struct node{
  int data;
  struct node* next;
};

struct node *reverse (struct node *head, int k) {
  if(head == nullptr){
    return head;
  }
  node* prev = nullptr;
  node* cur = head;
  node* next = nullptr;
  int count = 0;
  while(count < k && cur != nullptr){
    next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
    count++;
  }
  if(next != nullptr)
    head->next = reverse(next, k);
  return prev;
}
