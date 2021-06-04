# Important

Concepts:

- if subset is asked then you can think about sort and then you don't have to
go for j: 1 to i - 1, just i - 1 or some specific condition value can be used.

- if talking about subarray or substring, then think of maintaining suffix
in dp

- if subsequence is there in same sequence then think of maintaining subseq
max and j from 1 to i - 1 can be used.

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

## 32.cc : reach a given score

it is just like coin change problem. DP is like make j with 0 to ith index coins
In these kinds of problems, we need do something like dp[i][j] has
some relation with dp[i - 1][j] and dp[i][j - something].
Here space can be optimized. Instead of O(n^2) space we can have O(n) space
if we optimize the loop we can use old values of dp[i - 1] in dp[i].

## 34.cc : kadane's algorithm

solution shows how kadane is just space optimized dp and because subarray is
there so we use dp of largest suffix

## 37.cc : word break problem

this is asked in google, microsoft, etc. The DP here is like prefix that is
fine. Recursion goes like for(i : 1, n - 1) contains(0, i) && breakble(i + 1, end)

## 39.cc : Partition equal problem

Similar to coin change problem. Just take care that we need to find if any
subset can make sum/2 (if sum is even). If sum is odd then not possible.

## 40.cc : longest palindromic subsequence

because it is not guaranteed that (i + 1, j) and (i, j - 1) would always be
defined when computing (i,j) so we instead went for filling table with
length from 2 to size. (length 1 means answer 1). Inside we iterate i and based
on length we take j. With this approach it is always guranteed those two will
be defined.

## 43.cc : longest alternative subsequence

Here DP is not the best solution. DP can be done as LIS just we need to track
both increasing and decreasing subseq in arr[2][j].
Instead this question is more of couting number of peaks. Because if we leave
any of the peak we don't get the maximum solution.

## 45.cc : coin win the game

This is very important question to know how to use DP for two players game.
We don't store other player move, instead we think what other player should
get. If he doesn't get it then we loose. Based on it we make DP.

## 46.cc : number of derangment

realizing that dr(n) = (n - 1)(dr(n - 1) + dr(n - 2)) is important.
Why so? if we want derangement of 4. 4 would be at 0 to 3 and i would be at 4.
if 4 is at i then it is like dr(2) otherwise it is like dr(3)

## 47.cc : max profit

here first we need to think of bruteforce. That is for every i, solution is
max of (profit from 0 to i and i + 1 to n - 1). Then realizing that if one of
them would be sotred already we can use it. Instead of calculating it at point.
That is DP here. But that is not the best solution. Solution is sum of diff of
all increasing pair
