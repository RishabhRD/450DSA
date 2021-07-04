# Important

## 1.cc : Job sequencing problem

Classic problem. Hard to get the intution.

## 2.cc : Activity selection problem


## 7.cc : Minimum platform problem

Here we sort the arrival and departure time individually. And then consider
both of them in sorted order (using merge technique) and then count who has
arrived but not departed till now.

## 10.cc : Minimum cash flow

Here we make transactions of between max\_debitor and max\_creditor.
We make the minimum transaction between 2. Print it an make amount settled.
And then we recur for same till we get debitor and creditor of amount 0. That
means all amounts are settled.

## 11.cc : Minimum cost to cut the board

We cut the more costy edge first so that number of pieces doesn't increase
