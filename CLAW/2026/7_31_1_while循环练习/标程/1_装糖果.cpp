#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int cnt = 0, total = 0, take = 1;
    while (total + take <= n) {
        total += take;
        cnt++;
        take += 2;
    }
    cout << cnt << " " << total << " " << n - total << endl;
    return 0;
}
