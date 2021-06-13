struct Node
{
    int data;
    struct Node* next;
    
    Node(int x){
        data = x;
        next = nullptr;
    }
};

int getNthFromLast(struct Node *head, int n) {
  if(head == nullptr) return -1;
  auto slow = head;
  auto fast = head;
  for(int i = 0; i < n ; i++){
    if(!fast){
      return -1;
    }
    fast = fast->next;
  }
  while(slow && fast){
    slow = slow->next;
    fast = fast->next;
  }
  if(slow)
    return slow->data;
  else
    return -1;
}
