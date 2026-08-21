// HackerRank starter. The editor already supplies main() and the parsing, and
// you fill in one named function. The scaffold is reproduced here so a solution
// saved outside the site still builds.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(x) (x).begin(), (x).end()
#define sz(x)  (int)(x).size()

// HackerRank's generated stubs pass containers by value, copying the whole
// input on every call. Your own helpers should take const&.
int solveIt(const vector<int>& a) {
    return sz(a);
}

int main() {
    ios_base::sync_with_stdio(false);   // absent from the stub, worth adding
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // The real scaffold writes to ofstream(getenv("OUTPUT_PATH")). getenv
    // returns null off-site, which is why copied HackerRank files crash locally.
    cout << solveIt(a) << '\n';
    return 0;
}
