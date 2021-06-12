# Important questions

## 3.cc : Remove loop in linked list

Very important with floyd cycle detection algorithm with slow and fast ptr.
To remove link, we count number of ele in loop. From start we take two pointers
head and head + k (k is #ele in loop). We move them in same pace. And where
they meet is where the loop start. And them we move second ptr again till
next is first to get last of loop. And then we set it to nullptr.
