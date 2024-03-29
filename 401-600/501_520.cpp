﻿#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements_503(vector<int> &nums) {
        int length = nums.size();
        vector<int> result(length, -1);
        stack<int> decreased;
        decreased.push(0);
        for (int i = 1; i < length; ++i) {
            while (!decreased.empty() && nums[i] > nums[decreased.top()]) {
                int target = decreased.top();
                decreased.pop();
                result[target] = nums[i];
            }
            decreased.push(i);
        }
        for (int i = 0; i < length - 1; ++i) {
            while (!decreased.empty() && nums[i] > nums[decreased.top()]) {
                int target = decreased.top();
                decreased.pop();
                result[target] = nums[i];
            }
            decreased.push(i);
        }
        return result;
    }

    bool checkPerfectNumber_507(int num) {
        if (num % 2 != 0)
            return false;
        int sum = 0;
        for (int i = 1; i * i < num; i++) {
            if (num % i == 0) {
                sum += i;

                if (i * i != num) {
                    sum += num / i;
                }
            }
        }
        return sum == 2 * num;
    }

    int change_518(int amount, vector<int>& coins) {
        int length = coins.size();
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int coin : coins)
            for (int i = coin; i <= amount; i++) dp[i] += dp[i - coin];
        return dp.back();
    }
};

int main() {
    Solution s;
    // cout << s.checkPerfectNumber_507(28) << endl;
    vector<int> coins({1, 2, 5});
    s.change_518(2, coins);
    return 0;
}