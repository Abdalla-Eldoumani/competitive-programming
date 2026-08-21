#include <bits/stdc++.h>
using namespace std;

inline void solve() {
    long long firstNumber, secondNumber; cin >> firstNumber >> secondNumber;

    long long smallerValue = min(firstNumber, secondNumber);
    long long result = 1;
    for (long long multiplier = 2; multiplier <= smallerValue; ++multiplier) {
        result *= multiplier;
    }
    cout << result << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}