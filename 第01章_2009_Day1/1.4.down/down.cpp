#include <cstdio>
#include <cassert>
#include <ctime>
#define maxn 500000

int f[maxn][3];
int d[maxn][5];

int max(int a, int b, int c) {
	int ret = a > b ? a : b;
	return c > ret ? c : ret;
}

int main() {
	int t;
	freopen("down.in", "r", stdin);
	freopen("down.out", "w", stdout);
	assert(scanf("%d", &t) == 1);
	assert(0 < t && t <= 20);
	for (int kase = 1; kase <= t; ++kase) {
		int n;
		assert(scanf("%d", &n) == 1);
		assert(1 <= n && n <= maxn);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 5; ++j) {
				assert(scanf("%d", &d[i][j]) == 1);
				assert(0 <= d[i][j] && d[i][j] <= 1000);
				if (i == 0) {
					assert(d[i][2] == 0 && d[i][3] == 0 && d[i][4] == 0);
				}
			}
		}
		f[n - 1][0] = 0;
		f[n - 1][1] = f[n - 1][0] + d[n - 1][0];
		f[n - 1][2] = f[n - 1][1] + d[n - 1][1];
		for (int i = n - 2; i >= 0; --i) {
			f[i][0] = max(f[i + 1][0] + d[i + 1][2] + d[i][0] + d[i][1],
					f[i + 1][1] + d[i + 1][3] + d[i][0],
					f[i + 1][2] + d[i + 1][4]); 
			f[i][1] = max(f[i + 1][0] + d[i + 1][2] + d[i][1],
					f[i + 1][1] + d[i + 1][3],
					f[i + 1][2] + d[i + 1][4] + d[i][0]);
			f[i][2] = max(f[i + 1][0] + d[i + 1][2],
					f[i + 1][1] + d[i + 1][3] + d[i][1],
					f[i + 1][2] + d[i + 1][4] + d[i][0] + d[i][1]);
		}
		int ans = max(f[0][0], f[0][1], f[0][2]);
		printf("Case %d: %d\n", kase, ans);
	}
	return 0;
}
