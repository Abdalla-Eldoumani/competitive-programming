// Hash map approach: O(n) time complexity, O(n) space complexity
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> countMap;
        for (int num : nums) {
            countMap[num]++;
            if (countMap[num] > 1) {
                return true;
            }
        }
        return false;
    }
};

// Hash set approach: O(n) time complexity, O(n) space complexity
// class Solution {
// public:
//     bool containsDuplicate(vector<int>& nums) {
//         unordered_set<int> seen;
//         for (int num : nums) {
//             if (seen.find(num) != seen.end()) {
//                 return true;
//             }
//             seen.insert(num);
//         }
//         return false;
//     }
// };

// Sorting approach: O(n log n) time complexity, O(1) space complexity
// class Solution {
// public:
//     bool containsDuplicate(vector<int>& nums) {
//         sort(nums.begin(), nums.end());
//         for (int i = 0; i < nums.size() - 1; i++) {
//             if (nums[i] == nums[i + 1]) {
//                 return true;
//             }
//         }
//         return false;
//     }
// };

// Brute force approach: O(n^2) time complexity
// class Solution {
// public:
//     bool containsDuplicate(vector<int>& nums) {
//         for (int i = 0; i < nums.size(); i++) {
//             for (int j = i + 1; j < nums.size(); j++) {
//                 if (nums[i] == nums[j]) {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
// };