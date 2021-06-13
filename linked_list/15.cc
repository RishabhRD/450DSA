struct Node
{
    int data;
    struct Node* next;
    
    Node(int x){
        data = x;
        next = nullptr;
    }
    
}; 

bool isCircular(Node *head) {
  auto slow = head;
  auto fast = head;
  while(slow != nullptr && fast != nullptr && fast->next != nullptr){
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast){
      return true;
    }
  }
  return false;
}
