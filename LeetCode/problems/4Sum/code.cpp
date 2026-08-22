using ll = long long;
#define all(x) (x).begin(), (x).end()
#define sz(x)  (int)(x).size()

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;

        sort(all(nums));

        for (int i = 0; i < sz(nums); ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            for (int j = i + 1; j < sz(nums); ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                
                int left = j + 1, right = sz(nums) - 1;

                while (left < right) {
                    ll sum = (ll)nums[i] + nums[j] + nums[left] + nums[right];
                    
                    if (sum < target) {
                        ++left;
                    } else if (sum > target) {
                        --right;
                    } else {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        ++left;
                        --right;

                        while (left < right && nums[left] == nums[left - 1]) {
                            ++left;
                        }
                        while (left < right && nums[right] == nums[right + 1]) {
                            --right;
                        }
                    }
                } 
            }
        }
        return res;
    }
};