#include <stdio.h>
#include <assert.h>
const int MAXN = 10000;
const int MAXK = 10000;

int main() {
	freopen("yuji.in", "r", stdin);
	freopen("yuji.out", "w", stdout);
	int tn, n, k;
	for (assert(scanf("%d", &tn) == 1 && 1 <= tn && tn <= 100); tn--; ) {
		assert(scanf("%d%d", &n, &k) == 2 &&
			   1 <= n && n <= MAXN &&
			   1 <= k && k <= MAXK);
		printf("%d\n", n + 2 * (k - 1));
	}
	return 0;
}

