using ll = long long;

#define all(x) (x).begin(), (x).end()
#define sz(x)  (int)(x).size()

// Hashing approach: O(n) time, O(n) space
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        unordered_set<int> numSet(all(nums));
        int longest = 0;
        for (int num : numSet) {
            if (!numSet.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (numSet.count(currentNum + 1)) {
                    ++currentNum;
                    ++currentStreak;
                }

                longest = max(longest, currentStreak);
            }
        }
        return longest;
    }
};

// Sort approach: O(nlogn) time, O(1) space
// class Solution {
// public:
//     int longestConsecutive(vector<int>& nums) {
//         if (nums.empty()) return 0;
//         sort(all(nums));
//         int longest = 1, current = 1;
//         for (int i = 1; i < sz(nums); ++i) {
//             if (nums[i] == nums[i - 1]) continue;
//             if (nums[i] == nums[i - 1] + 1) {
//                 ++current;
//             } else {
//                 longest = max(longest, current);
//                 current = 1;
//             }
//         }
//         return max(longest, current);
//     }
// };