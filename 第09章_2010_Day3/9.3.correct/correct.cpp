#include <cstdio>

int i, j, k, l, m, n;

int x, y, a, b;

int ok(long long a, long long b, long long  x, long long y){
	long long s, t, p, q;
	long long i, j, k, n;
	n = x + y;
	//printf("%I64d %I64d %I64d %I64d\n", a, b, x, y);
	//printf("%d %d %d %d\n", a, b, x, y);
	if((a * x + b * y) % 2 == 1) return 0;
	if(x!= 0 && a >= n) return 0;
	if(y!= 0 && b >= n) return 0;
	if(x == 0){
		if(b < y) return 1;
		return 0;
	}
	if(y == 0 || b == 0){
		if(a < x) return 1;
		return 0;
	}
	if(a == 0) return 1;	
	if(a == b || a == b + 1) return 1;
	if (b > x){
		return ok(n - 1 - b, n - 1- a, y, x);
	} else {
		p = b;
		s = (a - b - 1) * x;
		t = p * y;
	//	printf("%I64d %I64d %I64d, s, t, k\n", s, t, (s - 1) / p + 1);
		if (t >= s) {
			k = (s - 1) / p + 1;
			if(b + 1 < x + y - k) return 1;
			else return 0;
		}
		else {
			if (a * x - t <= x * (x - 1)) return 1;
			return 0;
		}
	}
}


int main(){
	freopen("correct.in", "r", stdin);
	freopen("correct.out", "w", stdout);
	int tt;
	scanf("%d", &tt);
	while(tt--){
		scanf("%d%d%d%d", &n, &k, &a, &b);
		x = k;
		y = n - k;
		if (ok(a, b, x, y)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
