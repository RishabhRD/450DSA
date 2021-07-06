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
