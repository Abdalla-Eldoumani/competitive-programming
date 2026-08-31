#define sz(x)  (int)(x).size()

// Two pointer approach, since the array is sorted. We can start with two pointers, one at the beginning and one at the end of the array. We calculate the sum of the two numbers at these pointers. If the sum is equal to the target, we return the indices. If the sum is less than the target, we move the left pointer to the right to increase the sum. If the sum is greater than the target, we move the right pointer to the left to decrease the sum. We continue this process until we find a pair that sums up to the target or until the pointers cross each other. O(n) time complexity, O(1) space complexity.
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 1, right = sz(numbers);
        while (left < right) {
            int sum = numbers[left - 1] + numbers[right - 1];
            if (sum == target) {
                return {left, right};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {};
    }
};