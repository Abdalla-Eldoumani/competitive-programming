class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        int min_price = prices[0], max_price = prices[0];

        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] < min_price) {
                max_price = prices[i];
                min_price = prices[i];
            } else if (max_price < prices[i]) {
                max_price = prices[i];
                int curr_profit = max_price - min_price;

                if (profit < curr_profit) {
                    profit = curr_profit;
                }
            }
        }

        return profit;
    }
};