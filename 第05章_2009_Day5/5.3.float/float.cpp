#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
typedef long long ll;

int n, m;
ll pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main() {
    freopen("float.in", "r", stdin);
    freopen("float.out", "w", stdout);
    int T;
    ll a, b, A, B;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        cin >> a >> b;
        A = a * (pow10[m] - 1) + b;
        B = (pow10[m] - 1) * pow10[n];
        cout << A / gcd(A, B) << " " << B / gcd(A, B) << endl;
    }
    return 0;
}
