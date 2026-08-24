#define sz(x)  (int)(x).size()
#define all(x) (x).begin(), (x).end()

// Hash map approach: O(n) time complexity, O(n) space complexity
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> res;
        unordered_map<int, int> mp;
        for (int i = 0; i < sz(nums); i++) {
            mp[nums[i]]++;
        }

        priority_queue<pair<int, int>> pq; 
        for (auto it : mp) {
            pq.push({it.second, it.first});
        }

        while (k--) {
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;
    }
};

// Bucket sort approach: O(n) time complexity, O(n) space complexity
// class Solution {
// public:
//     vector<int> topKFrequent(vector<int>& nums, int k) {
//         vector<int> res;
//         unordered_map<int, int> mp;
//         for (int i = 0; i < sz(nums); i++) {
//             mp[nums[i]]++;
//         }

//         vector<vector<int>> bucket(sz(nums) + 1);
//         for (auto it : mp) {
//             bucket[it.second].push_back(it.first);
//         }

//         for (int i = sz(bucket) - 1; i >= 0 && k > 0; i--) {
//             if (!bucket[i].empty()) {
//                 for (int j = 0; j < sz(bucket[i]) && k > 0; j++) {
//                     res.push_back(bucket[i][j]);
//                     k--;
//                 }
//             }
//         }

//         return res;
//     }
// };

// Sorting approach: O(n log n) time complexity, O(n) space complexity
// class Solution {
// public:
//     vector<int> topKFrequent(vector<int>& nums, int k) {
//         vector<int> res;
//         unordered_map<int, int> mp;
//         for (int i = 0; i < sz(nums); i++) {
//             mp[nums[i]]++;
//         }

//         vector<pair<int, int>> freq(mp.begin(), mp.end());
//         sort(all(freq), [](const pair<int, int>& a, const pair<int, int>& b) {
//             return a.second > b.second;
//         });

//         for (int i = 0; i < k; i++) {
//             res.push_back(freq[i].first);
//         }

//         return res;
//     }
// };