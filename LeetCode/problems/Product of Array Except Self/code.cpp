using ll = long long;

#define all(x) (x).begin(), (x).end()
#define sz(x)  (int)(x).size()

// Prefix sum and suffix sum approach: O(n) time and O(1) space (excluding the output array)
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = sz(nums);
        vector<int> ans(n, 1);

        ll left = 1;
        for (int i = 0; i < n; i++) {
            ans[i] *= left;
            left *= nums[i];
        }

        ll right = 1;
        for (int i = n - 1; i >= 0; i--) {
            ans[i] *= right;
            right *= nums[i];
        }

        return ans;
    }
};