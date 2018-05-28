#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
using namespace std;

typedef long long LL;
const int MAXN = 150007;
const int MAXK = 20;
const LL INF = (LL) 1 << 60;

struct Edge {
	int to, w;
	Edge* next;
};

Edge edges[MAXN * 2], * g[MAXN];
int nEdge;
LL up[MAXN][MAXK], down[MAXN][MAXK * 2], w[MAXK * 2];
int pos[MAXN][MAXK * 2], tPos[MAXK * 2];
int open[MAXN], pn, father[MAXN], pw[MAXN];
int N, K;

void initNet() {
	memset(g, 0, sizeof(g));
	nEdge = 0;
}

inline void addEdge(int x, int y, int w) {
	Edge* p = &edges[nEdge++];
	p->to = y;
	p->w = w;
	p->next = g[x];
	g[x] = p;
}

void bfs() {
	int i, j, x;
	Edge* p;

	pn = 0;
	open[pn++] = 0;
	father[0] = -1;
	for (i = 0; i < pn; ++i) {
		x = open[i];
		for (p = g[x]; p; p = p->next) {
			if (p->to != father[x]) {
				father[p->to] = x;
				pw[p->to] = p->w;
				open[pn++] = p->to;
			}
		}
	}
}

void dpDown() {
	Edge* p;
	int c, i, j, k, x;

	for (c = pn - 1; c >= 0; --c) {
		x = open[c];
		down[x][0] = 0;
		pos[x][0] = -1;
		for (i = 1; i < K + K; ++i) {
			down[x][i] = -INF;
			pos[x][i] = -1;
		}
		for (i = 0; i < K; ++i) {
			up[x][i] = -INF;
		}
		for (p = g[x]; p; p = p->next) {
			if (p->to != father[x]) {
				j = k = 0;
				for (i = 0; i < K + K; ++i) {
					if (k < K && down[p->to][k] + p->w > down[x][j]) {
						w[i] = down[p->to][k] + p->w;
						tPos[i] = p->to;
						++k;
					} else {
						w[i] = down[x][j];
						tPos[i] = pos[x][j];
						++j;
					}
				}
				for (i = 0; i < K + K; ++i) {
					down[x][i] = w[i];
					pos[x][i] = tPos[i];
				}
			}
		}
	}
}

void dpUp() {
	int c, i, j, k, x, pre, w;

	for (c = 1; c < pn; ++c) {
		x = open[c];
		pre = father[x];
		w = pw[x];
		j = k = 0;
		for (i = 0; i < K; ++i) {
			while (pos[pre][k] == x) ++k;
			if (down[pre][k] > up[pre][j]) {
				up[x][i] = down[pre][k] + w;
				++k;
			} else {
				up[x][i] = up[pre][j] + w;
				++j;
			}
		}
	}
}

void input() {
	int i, j, x, y, w;
	initNet();
	scanf("%d%d", &N, &K);
	assert(2 <= N && N <= 150000);
	assert(1 <= K && K <= N - 1);
	for (i = 0; i < N - 1; ++i) {
		scanf("%d%d%d", &x, &y, &w);
		assert(0 <= x && x <= N - 1);
		assert(0 <= y && y <= N - 1);
		assert(1 <= w && w <= 1000000);
		addEdge(x, y, w);
		addEdge(y, x, w);
	}
}

void solve() {
	int i, j, k, c;
	LL value;

	bfs();
	assert(pn == N);
	dpDown();
	dpUp();
	for (i = 0; i < N; ++i) {
		j = k = 0;
		for (c = 0; c < K; ++c) {
			if (up[i][j] > down[i][k]) {
				if (c == K - 1) value = up[i][j];
				++j;
			} else {
				if (c == K - 1) value = down[i][k];
				++k;
			}
		}
		if (i > 0) printf(" ");
		//printf("%I64d", value);
		cout << value;
	}
	printf("\n");
}

int main() {
	freopen("kth.in", "r", stdin);
	freopen("kth.out", "w", stdout);
	int T;
	scanf("%d", &T);
	assert(T <= 50);
	while (T--) {
		input();
		solve();
	}
	return 0;
}

/*
2
5 4
4 0 1
1 4 5
2 3 1
4 2 3
*/
