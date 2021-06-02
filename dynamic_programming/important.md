# Important

## 15.cc : Longest Increasing subsequence

We do O(n log n) solution instead of O(n^2) with replacing big elements by
smaller elements in sorted order.

## 18.cc : Maximum sum increasing subsequence

It is important to note that sum should be set to current element if greater
sum is not possible to reset the sum.

## 22.cc : Egg dropping problem

We minimze attempt in this problem. Here we break problem for the worst  case
if egg breaks and if it doesn't. Then we take minimum of it.

## 23.cc : Max chain length

It is like LIS but we need to sort first basis on first element of pair because
subsequence is not given in question.

## 24.cc : Maximum size square problem

Thinking of logic that we should put 0 if 1 is not there and min of all 3
plus one was not thought by me. That is bad. But this logic is being used
by many questions and I was not able to think of putting 0 thing. I should
remember it.

## 27.cc : Maximum difference between 0 and 1

Here realizing that it's can be solved with DP if we replace 1 with -1 and 0
with 1. Then it's just like largest contiguous sum problem. We can use DP
or kadane algorithm

## 28.cc : Minimum number of jumps

Here DP is not the best solution. Best solution is O(n) and O(1) space, where
we maintain steps we can make, maximum index we can reach and total jumps.

## 30.cc : Minimum removals to make max - min <= k

Here (i, j) DP is not sufficient as it is n^2. Instead We sort but if we get
sorted sequence then we can do better. In O(nlogn) we can do binary search for
required element. It takes O(1) space. In O(n) we can use dp to store where the
required element was and start from next (as we assume range is sorted). It
takes O(n) space.

## 31.cc : Longest common substring

Here substring is asked so we need to look at suffix instead of maintaining
subsequence. Then we take maximum of all.
