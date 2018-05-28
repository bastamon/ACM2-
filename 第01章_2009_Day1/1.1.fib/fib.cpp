#include <cstdio>
#include <cstring>
#include <cassert>
#define maxn 64 
int x[maxn], y[maxn];
int main() {
    int t;
	freopen("fib.in", "r", stdin);
	freopen("fib.out", "w", stdout);
    assert(scanf("%d", &t) == 1);
    assert(1 <= t && t <= 20);
    for (int kase = 1; kase <= t; ++kase) {
        int n;
        assert(scanf("%d", &n) == 1);
        assert(1 <= n && n <= 40);
        if (n == 1) {
            printf("Case %d: %d %d\n", kase, 1, 1);
            puts("0 0");
            continue;   
        }
        x[0] = y[0] = 0;
        x[1] = 1, y[1] = 0;
        for (int i = 2; i < n; ++i) {
            if (i & 1) {
                x[i] = y[i - 1] + x[i - 2];
                y[i] = 0;
            } else {
                x[i] = 0;
                y[i] = x[i - 1] + y[i - 2];
            }
        }
        int length, width; 
        if (n & 1) {
            length = y[n - 1] + x[n - 2];
            width = length + y[n - 1];
        } else {
            width = x[n - 1] + y[n - 2];
            length = width + x[n - 1];
        }
        printf("Case %d: %d %d\n", kase, length, width);
        for (int i = 0; i < n; ++i) {
            printf("%d %d\n", x[i], y[i]);
        }
    }
    return 0;
}
