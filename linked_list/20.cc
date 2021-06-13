struct Node
{
    int data;
    struct Node *next, *prev;
};

bool pairSum(struct Node *head, int x){
  auto tail = head;
  while(tail->next){
    tail = tail->next;
  }
  while(head != tail){
    if(head->data + tail->data == x){
      return true;
    }else if(head->data + tail->data > x){
      tail = tail->prev;
    }else{
      head = head->prev;
    }
  }
  return false;
}
