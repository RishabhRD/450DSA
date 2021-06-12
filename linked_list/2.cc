struct Node {
  const int data;
  Node* next;
};

bool detectLoop(Node* head) {
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
