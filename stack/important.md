# Important

## 8.cc : Next greater element

We use stack and always stack maintain the property that element in it
are in decreasing order. For every element, pop all the elements which are
smaller than it and print them.

## 9.cc : Celebrity problem

We push everybody to stack. Then we take 2 out of it check who can't be
a candidate and eliminate it and push other one again. So at last one would
be remaining. For that we check if it is actually a celibrity in O(n).

## 13.cc : Reverse stack using recursion

We take the first element, reverse the rest of stack and put the element
to bottom of stack.

## 14.cc : Sort a stack using recursion

We take the first element, sort the rest of stack and put the element in front
of element just smaller than it.


## 15.cc : Largest histogram area

Use of stack to find left area and right area for every element in O(n) is
awesome.

## 17.cc : Longest valid substring

Pushing index to stack is very important. These are very important way to think
in questions that needs to remember ordering.

## 18.cc : Check for redundant bracket

We push everything in stack except ) and check if we encountered it in right
way or not.

## 25.cc : LRU cache implementation

In hash map we store the iterator of list element to reach there easily.

## 28.cc : Interleave first half and second half of queue

Question only allows to use a stack as data structure. So we need to somehow
take the first half element in right order to stack and then interleave both.

## 29.cc : Circular tour

Here we enqueue the petrol pump as we visit. If fuel is low, then we remove the
petrol pumps from queue.

## 30.cc : Rotten oranges

Here we do BFS and rot every orange in nearby. But we need to do parallel BFS
because to reach a place there can be other path that is minimal. For that we
put all the path from where we can start in queue and bfs on same queue.  Now,
one level processing will happen to all starting element and then go to
next level. Hence it would be like parallel only.
