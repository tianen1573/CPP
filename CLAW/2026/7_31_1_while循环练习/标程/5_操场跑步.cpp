#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int day = 0, total = 0;
    while (total < n) {
        day++;
        total += day;
    }
    cout << day << endl;
    return 0;
}
