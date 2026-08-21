#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// The version the problem ships with. num / val == 1 is true for any num below
// 2 * val, so it reports plenty of non-squares as smart.
//
// bool is_smart_number(int num) {
//     int val = (int) sqrt(num);
//     if(num / val == 1)
//         return true;
//     return false;
// }

// Corrected:
bool is_smart_number(int num) {
    int val = (int) sqrt(num);
    if(num / val == val && num % val == 0)
        return true;
    return false;
}

int main() {
    
    int test_cases;
    cin >> test_cases;
    int num;
    for(int i = 0; i < test_cases; i++) {
        cin >> num;
        bool ans = is_smart_number(num);
        if(ans) {
            cout << "YES" << endl;
        }
        else cout << "NO" << endl;
    }
    return 0;
}