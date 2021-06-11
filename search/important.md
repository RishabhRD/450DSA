# Important Questions

2.cc : Search in a rotated sorted array

Here finding the peak is important by binary search. Practice the binary search.

7.cc : Majority element

Here moore's voting algorithm is used for getting solution in O(1). Main idea
is this: If element is majority, then there must be any element whose count
of occurance - count of non-occurance return > 0. Also a check needs to be done
if the element returned is really majority because last index is not checked in
case of no majority.

9.cc : find pair with given distance

Here realizing that finding difference in sorted array can be done in O(n)
is important. We start from 0 and 1 and then proceed on basis of difference.

12.cc : Count triplets with sum smaller than X

Here learning that for finding sum in sorted array can be done in O(n) is
important.

13.cc : Merge in O(1) space

Gap method is important here. Just learn it.

14.cc : 0 sum subarray

Here use of hashmap is important. We need to realize if 0 to i sum is k
and 0 to j sum is k then i to j sum is also k.

16.cc : sort by bitcount

Here we can use stable\_sort and bitset<32>::count(). However that is
O(n log(n)). However, we can see that bit count can be between 0 to 31.
So, we did better. That is counting sort.

22.cc : kth ele of 2 sorted array

Here binary search over k is awesome and it should be done in very robust
fashion. It is not only about binary search of k. But also about writing
code in better way. Realize that we need to bsearch over how many elements
we can pick from first array.

24.cc : Allocate minimum number of pages

Here realizing that binary search would be solution is very important.
Here binary search is on number of pages we can allocate to m students.
So, famous question and can come in varieties.
