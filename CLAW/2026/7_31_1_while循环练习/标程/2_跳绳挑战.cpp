#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long day = 1, jump = 1;
    while (jump <= n) {
        jump *= 2;
        day++;
    }
    cout << day << endl;
    return 0;
}
