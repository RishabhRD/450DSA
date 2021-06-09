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

14.cc : 0 sum subarray

Here use of hashmap is important. We need to realize if 0 to i sum is k
and 0 to j sum is k then i to j sum is also k.
