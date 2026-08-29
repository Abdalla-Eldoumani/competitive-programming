#define sz(x)  (int)(x).size()

class Solution {
public:
    bool isPalindrome(string s) {
        for (int i = 0; i < sz(s); i++) {
            if (!isalnum(s[i])) {
                s.erase(i, 1);
                i--;
            } else {
                s[i] = tolower(s[i]);
            }
        }

        int left = 0, right = sz(s) - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};