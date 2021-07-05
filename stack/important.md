# Important

## 8.cc : Next greater element

We use stack and always stack maintain the property that element in it
are in decreasing order. For every element, pop all the elements which are
smaller than it and print them.

## 9.cc : Celebrity problem

We push everybody to stack. Then we take 2 out of it check who can't be
a candidate and eliminate it and push other one again. So at last one would
be remaining. For that we check if it is actually a celibrity in O(n).
