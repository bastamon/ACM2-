#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;

long long getn(long long l) {
	long long r = l / 4;
	long long v = r * r + (r - 1) * (r - 1);
	if (l % 4 == 0) return v;
	if (l % 4 == 1) return v + r - 1; 
	if (l % 4 == 2) return v + 2 * r - 1;
	return v + 3 * r - 1;
}

int main() {
	freopen("dam.in", "r", stdin);
	freopen("dam.out", "w", stdout);
	int tn, l;
	long long n, s;
	for (assert(scanf("%d", &tn) == 1 && tn >= 1 && tn <= 10000); tn--; ) {
		assert(scanf("%d", &l) == 1);
		assert(l > 2 && l <= 2000000000);
		s = l - 2;
		n = getn(l);
		s += 2 * n;
		//printf("%I64d", s / 2);
		cout << s / 2;
		printf(s % 2 ? ".5\n" : ".0\n");
	}
	assert(scanf("%*s") == EOF);
	return 0;
}
