#include <iostream>
#include <vector>
using namespace std;

// use DP
// Start from last - 1, check what is max profit you can get and based on that
// calculate the max profit you can get for prev element. You need to have
// max values till last for this calculation.
//
// Formula:
// for(i = last - 2 to 0):
// maxValues[i] = max(maxValues[i+1], arr[i+1])
// profit[i] = max(maxValues[i] - arr[i], profit[i+1])
//
// where
// maxValues[last] = 0 and profit[last] = 0

int maxProfit(vector<int>& prices) {
  if(prices.size() <= 1){
    return 0;
  }
  vector<int> maxValues(prices.size());
  vector<int> profit(prices.size());
  for(int i = prices.size() - 2; i >= 0; i--){
    maxValues[i] = std::max(maxValues[i+1], prices[i+1]);
    profit[i] = std::max(maxValues[i] - prices[i], profit[i+1]);
  }
  return profit[0];
}

int main(){
  vector<int> vec{7, 1, 5, 3, 6, 4};
  std::cout<<maxProfit(vec)<<std::endl;
}
