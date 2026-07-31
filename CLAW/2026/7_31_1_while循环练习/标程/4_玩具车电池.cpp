#include <bits/stdc++.h>
using namespace std;

int main() {
    double n;
    cin >> n;
    int hour = 0;
    while (n >= 50) {
        n *= 0.9;
        hour++;
    }
    cout << hour << endl;
    return 0;
}
