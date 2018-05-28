#include <stdio.h>
#include <assert.h>

int main() {
	freopen("degree.in", "r", stdin);
	freopen("degree.out", "w", stdout);
	int tn, n, sum, t, i;
	char flag;
	for (assert(scanf("%d", &tn) == 1), assert(1 <= tn && tn <= 20); tn--; ) {
		assert(scanf("%d", &n) == 1 && n >= 1 && n <= 100);
		//sum用来统计度数和,除以2就是边数
		//flag用来标记是否存在孤点
		sum = 0, flag = 0;
		for (i = 1; i <= n; i++) {
			assert(scanf("%d", &t) == 1 && t >= 0 && t <= 100);
			if (!t && n > 1) flag = 1;
			sum += t;
		}
		if (!flag && sum == 2 * (n - 1)) printf("Possible\n");
		else printf("Impossible\n");
	}
	assert(scanf("%*s") == EOF);
	return 0;
}
