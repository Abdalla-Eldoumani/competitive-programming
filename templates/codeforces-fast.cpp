// Codeforces toolkit. Copy, keep the sections you need, delete the rest.
// Every structure here is O(n log n) or better and drops in unmodified.

// Pragmas must precede every #include, or libstdc++ compiles for a different
// target than your code and you get "inlining failed in call to always_inline"
// out of allocator.h. O3 not Ofast: Ofast implies -ffast-math, which fails to
// compile with avx2 on GCC 13/14 and silently changes sqrt results. avx2 is a
// bet on judge hardware; Codeforces has it, some judges crash on it.
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <class T> using minheap = priority_queue<T, vector<T>, greater<T>>;

#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (int)(x).size()

#ifdef ONLINE_JUDGE
#define dbg(x) ((void)0)
#else
#define dbg(x) cerr << #x " = " << (x) << '\n'
#endif

// ---- hashing ---------------------------------------------------------------
// std::hash on integers is the identity function, which makes unordered_map
// trivially hackable. The clock seed is unknowable when the hack is written.
struct custom_hash {
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(ull x) const {
        static const ull SEED = chrono::steady_clock::now().time_since_epoch().count();
        return (size_t)splitmix64(x + SEED);
    }
};
template <class K, class V> using hmap = unordered_map<K, V, custom_hash>;
template <class K> using hset = unordered_set<K, custom_hash>;

// gp_hash_table: open addressed, several times faster to insert and clear,
// ~10% slower to read, degrades under heavy erasing.
template <class K, class V> using fast_map = gp_hash_table<K, V, custom_hash>;

// order_of_key(k): elements strictly below k. find_by_order(i): i-th element.
// Both O(log n). For a multiset store pair<value, unique_id>.
template <class T> using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ---- disjoint set ----------------------------------------------------------
// Member is siz, not sz: a member named sz would be eaten by the sz(x) macro.
struct DSU {
    vector<int> p, siz;
    explicit DSU(int n) : p(n), siz(n, 1) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (siz[a] < siz[b]) swap(a, b);
        p[b] = a, siz[a] += siz[b];
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
};

// ---- fenwick tree ----------------------------------------------------------
// Point add, prefix sum. Half the constant of a segment tree when that is all
// you need. Indices are 0-based on the outside.
struct Fenwick {
    vector<ll> t;
    explicit Fenwick(int n) : t(n + 1, 0) {}
    void add(int i, ll v) { for (++i; i < sz(t); i += i & -i) t[i] += v; }
    ll sum(int i) { ll s = 0; for (++i; i > 0; i -= i & -i) s += t[i]; return s; }
    ll sum(int l, int r) { return sum(r) - (l ? sum(l - 1) : 0); }
};

// ---- segment tree ----------------------------------------------------------
// Iterative, point assign, range query on [l, r). Change merge and ID together.
struct SegTree {
    static ll merge(ll a, ll b) { return a + b; }
    static ll id() { return 0; }  // must be the identity of merge

    int n;
    vector<ll> t;
    explicit SegTree(int n) : n(n), t(2 * n, id()) {}
    void set(int i, ll v) { for (t[i += n] = v; i >>= 1;) t[i] = merge(t[2*i], t[2*i+1]); }
    ll query(int l, int r) {
        ll a = id(), b = id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) a = merge(a, t[l++]);
            if (r & 1) b = merge(t[--r], b);
        }
        return merge(a, b);
    }
};

// ---- sparse table ----------------------------------------------------------
// O(1) query on a static array, [l, r] inclusive. Only for idempotent merges
// (min, max, gcd, and, or) because ranges overlap.
struct SparseTable {
    static ll merge(ll a, ll b) { return min(a, b); }

    vector<vector<ll>> j;
    explicit SparseTable(const vector<ll>& a) : j(1, a) {
        for (int p = 1; (1 << p) <= sz(a); ++p) {
            j.emplace_back(sz(a) - (1 << p) + 1);
            for (int i = 0; i < sz(j[p]); ++i)
                j[p][i] = merge(j[p-1][i], j[p-1][i + (1 << (p-1))]);
        }
    }
    ll query(int l, int r) {
        int p = 31 - __builtin_clz(r - l + 1);
        return merge(j[p][l], j[p][r - (1 << p) + 1]);
    }
};

// ---- number theory ---------------------------------------------------------
constexpr ll MOD = 1'000'000'007;

ll mpow(ll b, ll e, ll m = MOD) {
    ll r = 1;
    for (b %= m; e; e >>= 1, b = b * b % m)
        if (e & 1) r = r * b % m;
    return r;
}
ll minv(ll a, ll m = MOD) { return mpow(a, m - 2, m); }  // m must be prime

// spf[x] is the smallest prime factor of x, so factorising is O(log x).
vector<int> sieve(int n) {
    vector<int> spf(n + 1);
    iota(all(spf), 0);
    for (int i = 2; (ll)i * i <= n; ++i)
        if (spf[i] == i)
            for (int j = i * i; j <= n; j += i)
                if (spf[j] == j) spf[j] = i;
    return spf;
}

// ---- strings ---------------------------------------------------------------
// z[i] is the longest common prefix of s and s.substr(i). Substring search:
// run it on pattern + '\0' + text and look for z[i] == pattern.size().
vector<int> zfunc(const string& s) {
    int n = sz(s);
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// ---- graphs ----------------------------------------------------------------
using Graph = vector<vector<pii>>;  // g[v] = {neighbour, weight}

vector<ll> dijkstra(const Graph& g, int src) {
    vector<ll> d(g.size(), LLONG_MAX);
    minheap<pll> pq;
    d[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        pll top = pq.top();
        pq.pop();
        int v = (int)top.second;
        if (top.first > d[v]) continue;
        for (size_t i = 0; i < g[v].size(); ++i) {
            int u = g[v][i].first, w = g[v][i].second;
            if (d[v] + w < d[u]) d[u] = d[v] + w, pq.push({d[u], u});
        }
    }
    return d;
}

// ---- buffered input --------------------------------------------------------
// Only worth it past a few million integers. Buffer must exceed the whole input.
namespace fast_in {
char buf[1 << 24];
size_t pos = 0, len = 0;

void init() { len = fread(buf, 1, sizeof(buf), stdin); pos = 0; }

int read_int() {
    while (pos < len && buf[pos] != '-' && (buf[pos] < '0' || buf[pos] > '9')) ++pos;
    bool neg = pos < len && buf[pos] == '-';
    if (neg) ++pos;
    int x = 0;
    while (pos < len && buf[pos] >= '0' && buf[pos] <= '9') x = x * 10 + (buf[pos++] - '0');
    return neg ? -x : x;
}
}  // namespace fast_in

// ---- solution --------------------------------------------------------------
// Answers accumulate into out and are written once. Per-line cout is fine until
// the output runs to hundreds of thousands of lines. Never endl in a loop.
void solve(string& out) {
    (void)out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    string out;
    while (t--) solve(out);
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
