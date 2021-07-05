void twoStacks :: push1(int x) {
  if(top1 + 1 == top2){
    return;
  }
  arr[top1 + 1] = x;
  top1++;
}
   
//Function to push an integer into the stack2.
void twoStacks ::push2(int x)
{
  if(top2 - 1 == top1){
    return;
  }
  arr[top2 - 1] = x;
  top2--;
}
   
//Function to remove an element from top of the stack1.
int twoStacks ::pop1()
{
  if(top1 == -1){
    return -1;
  }
  int ele = arr[top1];
  top1--;
  return ele;
}

//Function to remove an element from top of the stack2.
int twoStacks :: pop2()
{
  if(top2 == size)
    return -1;
  int ele = arr[top2];
  top2++;
  return ele;
}
