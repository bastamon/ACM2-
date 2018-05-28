#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;

#define maxn 500000

int p[maxn];

int main() {
	freopen("arrange.in", "r", stdin);
	freopen("arrange.out", "w", stdout);
	int t;
	assert(scanf("%d", &t) == 1);
	assert(1 <= t && t <= 20);
	for (int kase = 1; kase <= t; ++kase) {
		int n, r, c;
		assert(scanf("%d%d%d", &n, &r, &c) == 3);
		assert(1 <= r && r <= 10000 &&
				1 <= c && c <= 10000 &&
				r * c <= n && n <= 500000);
		for (int i = 0; i < n; ++i) {
			assert(scanf("%d", &p[i]) == 1);
			assert(0 < p[i] && p[i] <= 1000000000);
		}
		sort(p, p + n);
		int ans;
		int lo = 0, hi = 1000000000;
		while (lo <= hi) {
			int mi = (lo + hi) >> 1;
			int cnt = 0;
			for (int i = 0; i + c - 1 < n;) {
				if (p[i + c - 1] - p[i] <= mi) {
					cnt++;
					i = i + c;
				} else {
					++i;
				}
			}
			if (cnt >= r) {
				hi = mi - 1;
				ans = mi;
			} else {
				lo = mi + 1;
			}
		}
		printf("Case %d: %d\n", kase, ans);
	}
	return 0;
}
