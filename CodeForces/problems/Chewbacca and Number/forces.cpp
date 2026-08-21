#include <bits/stdc++.h>
using namespace std;

inline void solve() {
    string s; cin >> s;

    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] > '4') {
            if (i == 0 && s[i] == '9') {
                continue;
            }
            s[i] = '9' - s[i] + '0';
        }
    }

    cout << s << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}