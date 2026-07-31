#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long day = 0, total = 0, save = 1;
    while (total <= n) {
        total += save;
        save *= 2;
        day++;
    }
    cout << day << endl;
    return 0;
}
