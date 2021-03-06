﻿#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>
#include <ListNode.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum_1(vector<int> &nums, int target) {
        unordered_map<int, int> remainAndIndex;
        int length = nums.size();
        for (int i = 0; i < length; i++) {
            auto iter = remainAndIndex.find(nums[i]);
            if (iter != remainAndIndex.end()) {
                return {iter->second, i};
            } else {
                remainAndIndex[target - nums[i]] = i;
            }
        }
        return {};
    }

    ListNode *addTwoNumbers_2(ListNode *l1, ListNode *l2) {
        auto *newList = new ListNode();
        ListNode *pointer = newList;
        int val1, val2, carry = 0;
        while (l1 || l2) {
            if (l1 != nullptr) {
                val1 = l1->val;
                l1 = l1->next;
            } else {
                val1 = 0;
            }

            if (l2 != nullptr) {
                val2 = l2->val;
                l2 = l2->next;
            } else {
                val2 = 0;
            }
            int sum = val1 + val2 + carry;
            carry = sum / 10;
            pointer->next = new ListNode(sum % 10);
            pointer = pointer->next;
        }
        if (carry > 0) {
            pointer->next = new ListNode(0);
        }
        return newList->next;
    }

    int lengthOfLongestSubstring_3(string s) {
        vector<int> contain(128, -1);
        int length = s.length();
        int maxCount = 0;
        int left = 0;
        for (int i = 0; i < length; ++i) {
            int &value = contain[s[i]];
            if (value != -1 && value >= left) {
                maxCount = max(maxCount, i - left);
                //将左边的s[i]移出
                left = value + 1;
            }
            value = i;
        }
        return max(maxCount, length - left);
    }

    double findMedianSortedArrays_4(vector<int> &nums1, vector<int> &nums2) {
        //时间复杂度O(m+n)，空间O(1)

        int left1 = -1, right1 = nums1.size(), left2 = -1, right2 = nums2.size();
        if (right1 == 0) {
            int median = right2 / 2;
            return right2 % 2 ? nums2[median] : (nums2[median] + nums2[median - 1]) / 2.0;
        } else if (right2 == 0) {
            int median = right1 / 2;
            return right1 % 2 ? nums1[median] : (nums1[median] + nums1[median - 1]) / 2.0;
        }
        int target = (right1 + right2) / 2;
        bool oneNum = (right1 + right2) % 2;
        for (int i = 0; i < target; ++i) {
            if (nums1[left1 + 1] < nums2[left2 + 1]) {
                left1++;
                if (left1 + 1 == right1) {
                    int median = left2 + target - i;
                    int previous = median ? max(nums2[median - 1],nums1[left1]) : nums1[left1];
                    return oneNum ? nums2[median] : (nums2[median] + previous) / 2.0;
                }
            } else {
                left2++;
                if (left2 + 1 == right2) {
                    int median = left1 + target - i;
                    int previous = median ? max(nums1[median - 1],nums2[left2]) : nums2[left2];
                    return oneNum ? nums1[median] : (nums1[median] + previous) / 2.0;
                }
            }
        }
        if (oneNum) {
            return min(nums1[left1 + 1], nums2[left2 + 1]);
        } else {
            int previous;
            if (left1 == -1)
                previous = nums2[left2];
            else if (left2 == -1)
                previous = nums1[left1];
            else
                previous = max(nums1[left1], nums2[left2]);
            return (min(nums1[left1 + 1], nums2[left2 + 1]) + previous) / 2.0;
        }

        //二分查找，O(log(m+n))
        //https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/
    }

    string longestPalindrome_5(string s) {
        //中心扩散
        int length = s.length();
        if (length < 2) {
            return s;
        }
        int previous = 0, next = 0, longest = 0, position = 0;
        //是否判断过回文长度为偶数，true=未判断
        bool flag = true;
        for (int i = 0; i < length - 1; i++) {
            while (previous >= 0 && next < length && s[previous] == s[next]) {
                previous--;
                next++;
            }
            int len = next - previous - 1;
            if (len > longest) {
                longest = len;
                position = previous + 1;
            }

            previous = next = i + 1;
            // 对每个中心位置，先检查以自身为中心的回文字串，再检查以自身和下一个（若可能）为中心的回文字串
            if (flag && s[i] == s[i + 1]) {
                previous--;
                i--;
                flag = false;
            } else {
                flag = true;
            }
        }
        return s.substr(position, longest);
    }

    string convert_6(string s, int numRows) {
        /*
         * 0                2n-2 => i +2n-2 +0
         * 1          2n-3  2n-1 => i +2n-4 +2
         * .       .        .    => i +2n-2i-2 +2i
         * n-2  n           3n-4 => i +2 +2n-4
         * n-1              3n-3 => i +0 +2n-2
         */
        if (numRows == 1) return s;
        int length = s.length();
        string result;
        for (int i = 0; i < numRows; ++i) {
            int secondInterval = 2 * i;
            int firstInterval = 2 * numRows - 2 - secondInterval;
            if (firstInterval == 0)
                firstInterval = secondInterval;
            else if (secondInterval == 0)
                secondInterval = firstInterval;
            int j = i;
            while (j < length) {
                result += s[j];
                if ((j += firstInterval) < length) {
                    result += s[j];
                    j += secondInterval;
                }
            }
        }
        return result;
    }

    int reverse_7(int x) {
        /*int sign = x > 0 ? 1 : -1;
        if (x == 0)
            return 0;
        string original = to_string(x);
        string reversed;
        int count = (int) original.length() - 1;
        while (original[count] == '0')
            count--;
        while (count >= 0) {
            reversed += original[count];
            count--;
        }
        try {
            return stoi(reversed) * sign;
        } catch (exception &) {
            return 0;
        }*/

        // Official Solution (Better)
        int rev = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;
            if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
            if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
            rev = rev * 10 + pop;
        }
        return rev;
    }

    int myAtoi_8(string s) {
        long result = 0;
        int length = s.length();
        if (length == 0) return result;

        //去掉前面的空格
        int count = 0;
        while (count < length && isspace(s[count])) ++count;
        if (count == length) return result;
        //判断符号
        int sign = 1;
        if (s[count] == '-') {
            sign = -1;
            count++;
        } else if (s[count] == '+')
            count++;
        //去掉前面的0
        while (count < length && s[count] == '0') count++;
        //大于等于11位时一定溢出
        int digits = 0;
        while (count < length && isdigit(s[count]) && digits < 11) {
            result = result * 10 + (s[count] - '0');
            digits++;
            count++;
        }

        result *= sign;
        if (result > INT32_MAX) return INT32_MAX;
        else if (result < INT32_MIN) return INT32_MIN;
        else return static_cast<int>(result);
    }

    bool isPalindrome_9(int x) {
        if (x < 0)
            return false;
        long reversed = 0;
        int original = x;
        while (original > 0) {
            reversed *= 10;
            reversed += original % 10;
            original /= 10;
        }
        return reversed == x;

        //可以只将x反转一半 循环条件为reversed < x
        //return x == reversed || x == reversed / 10;
    }

    //并不好的解法，代码臃肿复杂
    bool isMatch_10(string s, string p) {
        //aaa*, aa*a => at least 2 'a'
        //aa*aaa*a => at least 4 'a'
        //aa*.*a*a => 从尽可能少地匹配给'.'，剩余部分递归调用 isMatch
        //a*.???的情况下，aaa???中前三个a任意一个都有可能匹配给'.'
        int sLength = s.length();
        int pLength = p.length();
        int sPointer = 0;
        int pPointer = 0;
        while (pPointer < pLength) {
            int number = 1;
            bool unlimited = false;
            char currentChar = p[pPointer];
            if (currentChar == '.') {
                if (pPointer + 1 < pLength && p[pPointer + 1] == '*') {
                    if (pPointer + 2 == pLength) return true;
                    for (int j = sPointer; j <= sLength; ++j)
                        if (isMatch_10(s.substr(j), p.substr(pPointer + 2)))
                            return true;
                    return false;
                } else {
                    if (sPointer == sLength)return false;
                    sPointer++;
                    pPointer++;
                }
            } else {
                while (++pPointer < pLength) {
                    if (p[pPointer] == currentChar)
                        number++;
                    else if (p[pPointer] == '*') {
                        number--;
                        unlimited = true;
                    } else if (p[pPointer] != currentChar && unlimited) {
                        if (p[pPointer] == '.' && pPointer + 1 < pLength && p[pPointer + 1] == '*') {
                            //将最少要求匹配完 aa*.* == a.*
                            unlimited = false;
                            break;
                        } else {
                            //从最少要求开始尝试 aa*.
                            int next = s.find_first_not_of(currentChar, sPointer);
                            if (next == UINT32_MAX) next = sLength;
                            for (int j = number + sPointer; j <= next; ++j)
                                if (isMatch_10(s.substr(j), p.substr(pPointer)))
                                    return true;
                            return false;
                        }
                    } else break;
                }
                //确定数量后，且不存在’.'带来的二义性，进行匹配
                int next = s.find_first_not_of(currentChar, sPointer);
                if (next == UINT32_MAX) next = sLength;
                if (next - sPointer >= number) sPointer = unlimited ? next : sPointer + number;
                else return false;
            }
        }
        return sPointer == sLength;
    }

    //第十题动态规划的解法
    bool isMatch_10DP(string s, string p){
        int sLength = s.size();
        int pLength = p.size();

        auto matches = [&](int i, int j) {
            return i != 0 && (p[j - 1] == '.' || s[i - 1] == p[j - 1]);
        };

        vector<vector<bool>> dp(sLength + 1, vector<bool>(pLength + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= sLength; ++i) {
            for (int j = 1; j <= pLength; ++j) {
                if (p[j - 1] == '*') {
                    if (matches(i, j - 1))
                        dp[i][j] = dp[i][j - 2] || dp[i - 1][j];
                    else
                        dp[i][j] = dp[i][j - 2];
                } else {
                    dp[i][j] = matches(i, j) && dp[i - 1][j - 1];
                }
            }
        }

        return dp[sLength][pLength];
    }

    int maxArea_11(vector<int>& height) {
        int length = height.size(), left = 0, right = length - 1, maxSize = 0;
        while (left<right){
            int h, w = right - left;
            if(height[left]>height[right]){
                h = height[right];
                right--;
            } else{
                h = height[left];
                left++;
            }
            maxSize = max(maxSize, h*w);
        }
        return maxSize;
    }

    vector<pair<int, string>> I2R = {{1000, "M"},
                                     {900,  "CM"},
                                     {500,  "D"},
                                     {400,  "CD"},
                                     {100,  "C"},
                                     {90,   "XC"},
                                     {50,   "L"},
                                     {40,   "XL"},
                                     {10,   "X"},
                                     {9,    "IX"},
                                     {5,    "V"},
                                     {4,    "IV"},
                                     {1,    "I"}};

    string intToRoman_12(int num) {
        string result;
        int i = 0;
        while (num > 0) {
            if (num >= I2R[i].first) {
                num -= I2R[i].first;
                result += I2R[i].second;
            } else
                i++;
        }
        return result;
    }

    int romanToInt_13(string s) {
        /*
        Symbol       Value
        I             1
        V             5
        X             10
        L             50
        C             100
        D             500
        M             1000
        */
        unordered_map<char, int> symbolToValue(
                {
                        pair<char, int>('M', 1000),
                        pair<char, int>('D', 500),
                        pair<char, int>('C', 100),
                        pair<char, int>('L', 50),
                        pair<char, int>('X', 10),
                        pair<char, int>('V', 5),
                        pair<char, int>('I', 1),

                });
        int length = s.length();
        int result = 0;
        for (int i = 0; i < length;) {
            int current = symbolToValue[s[i]];
            int next = ++i < length ? symbolToValue[s[i]] : 0;
            if (current < next) {
                result -= current;
            } else {
                result += current;
            }
        }
        return result;
    }

    string longestCommonPrefix_14(vector<string>& strs) {
        int length = strs.size();
        if (length == 0) return "";
        else if (length == 1) return strs[0];
        vector<int> strsLen(length);
        int minLen = INT32_MAX;
        for (int i = 0; i < length; ++i) {
            minLen = min(minLen, strsLen[i] = strs[i].length());
        }
        string result;
        int i = 0;
        while (i < minLen) {
            char current = strs[0][i];
            for (int j = 1; j < length; ++j) {
                if (strs[j][i] != current) return result;
            }
            result += current;
            i++;
        }
        return result;
    }

    vector<vector<int>> threeSum_15(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        const int length = nums.size();
        //当前的数不与上一个相同
        int previous = INT32_MIN;
        for (int i = 0; i < length - 2 && nums[i] <= 0; ++i) {
            if (nums[i] == previous) continue;
            previous = nums[i];
            int target = -previous;
            int j = i + 1, k = length - 1;
            while (j < k) {
                int twoSum = nums[j] + nums[k];
                if (twoSum > target) {
                    k--;    //此处可以与j一样，寻找到下一个不同的nums[k]
                    continue;
                } else if (twoSum == target) {
                    result.emplace_back(vector<int>({nums[i], nums[j], nums[k]}));
                }
                //找到和当前不同的下一个nums[j]
                while (j < k - 1 && nums[j] == nums[j + 1]) j++;
                j++;
            }
        }
        return result;
    }

    int threeSumClosest_16(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        const int length = nums.size();
        int previous = INT32_MIN;
        int closest, distance = INT32_MAX;
        for (int i = 0; i < length - 2; ++i) {
            if (nums[i] == previous) continue;
            previous = nums[i];
            int twoTarget = target - previous;
            int j = i + 1, k = length - 1;
            while (j < k) {
                int twoSum = nums[j] + nums[k];
                if (abs(twoSum-twoTarget) < distance) {
                    distance = abs(twoSum-twoTarget);
                    closest = nums[i] + twoSum;
                }
                if (twoSum > twoTarget) {
                    k--;
                } else if (twoSum < twoTarget) {
                    j++;
                } else
                    return target;
            }
        }
        return closest;
    }

    //用树的解法更好
    vector<string> letterCombinations_17(string digits) {
        int length = digits.length();
        if (length == 0) return vector<string>();

        const vector<vector<char>> numberToLetter({
                                                          {},
                                                          {},
                                                          {'a', 'b', 'c'},
                                                          {'d', 'e', 'f'},
                                                          {'g', 'h', 'i'},
                                                          {'j', 'k', 'l'},
                                                          {'m', 'n', 'o'},
                                                          {'p', 'q', 'r', 's'},
                                                          {'t', 'u', 'v'},
                                                          {'w', 'x', 'y', 'z'}
                                                  });
        const int counts[]{0, 0, 3, 3, 3, 3, 3, 4, 3, 4};

        vector<int> max(length);
        vector<int> current(length, 0);
        vector<vector<char>> letters(length);
        for (int i = 0; i < length; ++i) {
            letters[i] = numberToLetter[digits[i] - '0'];
            max[i] = counts[digits[i] - '0'];
        }
        vector<string> result = vector<string>();
        while (true) {
            while (current[0] < max[0]) {
                string s;
                for (int j = 0; j < length; ++j) {
                    s += letters[j][current[j]];
                }
                result.emplace_back(s);
                current[0]++;
            }
            current[0] = 0;
            if (length > 1 && current[1] < max[1] - 1) {
                current[1]++;
            } else if (length > 2 && current[2] < max[2] - 1) {
                current[1] = 0;
                current[2]++;
            } else if (length > 3 && current[3] < max[3] - 1) {
                current[1] = 0;
                current[2] = 0;
                current[3]++;
            } else
                return result;
        }
    }

    vector<vector<int>> fourSum_18(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int length = nums.size();
        int previous1 = INT32_MAX;
        vector<vector<int>> result;

        int maxNum1 = target / 4;
        for (int i = 0; i < length - 3 && nums[i] <= maxNum1; ++i) {
            if (nums[i] == previous1) continue;
            previous1 = nums[i];
            int target2 = target - previous1, maxNum2 = target2 / 3, previous2 = INT32_MAX;
            for (int j = i + 1; j < length - 2 && nums[j] <= maxNum2; ++j) {
                if (nums[j] == previous2) continue;
                previous2 = nums[j];
                int m = j + 1, n = length - 1, target3 = target2 - previous2;
                while (m < n) {
                    int sum = nums[m] + nums[n];
                    if (sum > target3) {
                        while (m < n && nums[n - 1] == nums[n]) n--;
                        n--;
                        continue;
                    } else if (sum == target3) {
                        result.emplace_back(vector<int>({previous1, previous2, nums[m], nums[n]}));
                    }
                    while (m < n && nums[m] == nums[m + 1]) m++;
                    m++;
                }
            }
        }
        return result;
    }

    //空间O(L)
    ListNode* removeNthFromEnd_19(ListNode* head, int n) {
        vector<ListNode *> arr;
        auto ptr = head;
        while (ptr != nullptr) {
            arr.push_back(ptr);
            ptr = ptr->next;
        }
        int index = arr.size() - n;
        if (index == 0) return head->next;
        arr[index - 1]->next = arr[index]->next;
        return head;
    }

    //时间O(L) 空间O(1)
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        vector<ListNode *> arr;
        auto pre = new ListNode(0, head), ptr1 = head, ptr2 = pre;
        for (int i = 0; i < n; ++i) {
            ptr1 = ptr1->next;
        }
        while (ptr1 != nullptr) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        ptr2->next = ptr2->next->next;
        return pre->next;
    }

    bool isValid_20(string s) {
        stack<char> st({'#'});
        int length = s.length(), stSize = 0;
        if (length % 2 == 1) return false;
        for (int i = 0; i < length && length - i >= stSize; ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                st.push(s[i]);
                stSize++;
            } else {
                switch (s[i]) {
                    case '(':
                        if (st.top() != ')') return false;
                        break;
                    case '[':
                        if (st.top() != ']') return false;
                        break;
                    case '{':
                        if (st.top() != '}') return false;
                        break;
                }
                st.pop();
                stSize--;
            }
        }
        return stSize == 0;
    }
};

int main() {
    Solution s;
//    s.addTwoNumbers_2(new ListNode(2), new ListNode(5, new ListNode(1)));
//    cout << s.longestPalindrome_5("ababa") << endl;
//    cout << s.reverse_7(1534236469) << endl;
//    cout << s.isPalindrome_9(121) << endl;
//    cout << s.lengthOfLongestSubstring_3("abba") << endl;
//    vector<int> first({1,2});
//    vector<int> second({3,4});
//    cout<<s.findMedianSortedArrays_4(first,second);
//    string ss = "aaaa";
//    cout<<s.isMatch_10DP("aaa",
//                         "ab*a*c*a")<<endl;
//    vector<int> a({1,8,6,2,5,4,8,3,7});
//    cout << s.maxArea_11(a) << endl;
}