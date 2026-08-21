// Codeforces starter. Judge runs g++ -O2 -std=c++23 with a 256 MB stack.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <class T> using minheap = priority_queue<T, vector<T>, greater<T>>;

#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (int)(x).size()

// Codeforces passes -DONLINE_JUDGE, so a stray dbg() in a submission is free.
#ifdef ONLINE_JUDGE
#define dbg(x) ((void)0)
#else
#define dbg(x) cerr << #x " = " << (x) << '\n'
#endif

void solve() {

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;               // drop for a single-test problem
    while (t--) solve();
    return 0;
}
