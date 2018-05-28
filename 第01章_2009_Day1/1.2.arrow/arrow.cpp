#include <cstdio>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;
#define maxn 2010

int Y[maxn];
int px[maxn], py[maxn];
int yy[maxn];
int f[maxn];
int id[maxn];

bool cmp(int a, int b) {
	if (px[a] != px[b]) return px[a] < px[b];
	return py[a] < py[b];
}

int mylog[maxn];
int rmq[11][maxn];

void prepare(int n) {
	int i, j, k;
	for(i = 0; i <= n; mylog[i++] = k)
		for(k = 0; (1 << (k + 1)) < i; k++);
	for(j = 0; (1 << j) <= n; j++)
		for(i = 0; i + (1<<j) <= n; i++){
			if(j == 0) rmq[j][i] = f[i];
			else rmq[j][i] =
				max(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
		}
}

int query(int i, int j) {
	int k = mylog[j - i + 1];
	return max(rmq[k][i], rmq[k][j - (1 << k) + 1]);
}
set< pair<int, int> >SET;
int main() {
	int t;
	freopen("arrow.in", "r", stdin);
	freopen("arrow.out", "w", stdout);
	assert(scanf("%d", &t) == 1);
	assert(1 <= t && t <= 20);
	for (int kase = 1; kase <= t; ++kase) {
		int n, ycnt = 0;
		assert(scanf("%d", &n) == 1);
		assert(1 <= n && n <= 2000); 
		SET.clear();
		for (int i = 0; i < n; ++i) {
			assert(scanf("%d%d", &px[i], &py[i]) == 2);
			assert(0 <= px[i] && px[i] <= 10000000 && 
					0 <= py[i] && py[i] <= 10000000);
			assert(SET.find(make_pair(px[i], py[i])) == SET.end());
			SET.insert(make_pair(px[i], py[i]));
			Y[ycnt++] = py[i];
			id[i] = i;
		}
		sort(Y, Y + ycnt);
		ycnt = unique(Y, Y + ycnt) - Y;

		for (int i = 0; i < ycnt; ++i) {
			f[i] = 0;
		}

		for (int i = 0; i < n; ++i) {
			int id = lower_bound(Y, Y + ycnt, py[i]) - Y;
			if (f[id] < px[i]) f[id] = px[i];
		}
		prepare(ycnt - 1);
		int ans = -1;

		sort(id, id + n, cmp);
		for (int i = 0; i < n; ++i) {
			yy[i] = lower_bound(Y, Y + ycnt, py[id[i]]) - Y;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (px[id[j]] != px[id[i]]) break;
				int width = py[id[j]] - py[id[i]];
				if (width < 2) continue;
				int length = query(yy[i] + 1, yy[j] - 1) - px[id[i]];
				if (length >= width &&
						width + length > ans) ans = width + length;
			} 
		}
		printf("Case %d: %d\n", kase, ans);
	}
	return 0;
}
