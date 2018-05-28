#include <stdio.h>
#include <string.h>
const int N = 1005;
bool mark[9][256];
bool dp[N][256];
char s[9];
const int num_digit = 4;
const int base = 10000;
const int maxn = 1000;
struct big {
	int size, s[maxn];

	big() { *this = 0; }
	big(int val) { *this = val; }

	void operator =(int v) {
		size = 0;
		while (v > 0) {
			s[size++] = v % base;
			v /= base;
		};
	}
} bign[2][256];

void print(big a) {
	if (a.size == 0) {
		puts("0");
		return ;
	}
	printf("%d", a.s[a.size - 1]);
	for (int i = a.size - 2; i >= 0; i--)
		printf("%04d", a.s[i]);
	puts("");
}

void operator += (big& a, const big& b) {
	int g = 0;
	for (int i = 0; i < a.size || i < b.size; i++) {
		if (i < a.size) g += a.s[i];
		if (i < b.size) g += b.s[i];
		a.s[i] = g >= base ? g - base : g;
		g = g >= base ? 1 : 0;
	}
	if (b.size > a.size) a.size = b.size;
	if (g) a.s[a.size++] = g;
}

int main() {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	int ca;
	scanf("%d", &ca);
	while (ca--) {
		memset(mark,0, sizeof(mark));
		memset(dp, 0, sizeof(dp));
		int n, m; 
		scanf("%d%d", &n, &m);
		int maxh = 0;
		for (int j = 0; j < m; j++) {
			scanf("%s", s);
			int h = strlen(s);
			if (h > maxh) maxh = h;
			int tmp = 0;
			for (int i = 0; i < h; i++) tmp = (tmp << 1) + (s[i] - '0');
			for (int i = h; i <= 8; i++) {
				int base = 1 << (i - h);
				for (int k = 0; k < base; k++) mark[i][(k << h) + tmp] = 1;
			}
		}
		dp[0][0] = true;
		bign[0][0] = 1;
		int base = 1 << maxh;
		int u = 0, v = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < base; k++) if (dp[i - 1][k]) {
					int tmp = ((k << 1) + j) & (base - 1);
					int h = i < maxh ? i : maxh;
					if (!mark[h][tmp]) {
						if (!dp[i][tmp]) {
							dp[i][tmp] = true;
							bign[v][tmp] = 0;
						}
						bign[v][tmp] += bign[u][k];
					}
				}
			}
			u = v;
			v = 1 - v;
		}
		big ans = 0;
		for (int i = 0; i < base; i++) if (dp[n][i]) {
			ans += bign[u][i];
		}
		print(ans);
	}
	return 0;
}
