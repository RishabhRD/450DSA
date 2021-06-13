struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* middleNode(ListNode* head) {
  auto slow = head;
  auto fast = head;
  while(slow != nullptr && fast != nullptr && fast->next != nullptr){
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}
