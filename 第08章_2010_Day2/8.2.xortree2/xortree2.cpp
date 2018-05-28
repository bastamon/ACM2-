#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long LL;
const int MAXN = 150007;

struct Edge {
	int to, w;
	Edge* next;
};

Edge edges[MAXN * 2], * g[MAXN];
int nEdge;

struct TrieNode {
	int next[2];
	int count;
};

TrieNode tries[MAXN * 32];
int nTrie;
int open[MAXN];
bool vst[MAXN];
int a[MAXN];
int N, K;

void initNet() {
	memset(g, 0, sizeof(g));
	nEdge = 0;
	nTrie = 0;
	tries[0].next[0] = tries[0].next[1] = tries[0].count = 0;
}

inline void addEdge(int x, int y, int w) {
	Edge* p = &edges[nEdge++];
	p->to = y;
	p->w = w;
	p->next = g[x];
	g[x] = p;
}

#define l_rank(x) (tries[(x)].next[0] ? tries[tries[(x)].next[0]].count : 0)
#define r_rank(x) (tries[(x)].next[1] ? tries[tries[(x)].next[1]].count : 0)

void insert(int x, int c, int depth) {
	if (depth >= 31) {
		++tries[x].count;
		return;
	}
	int v = ((c >> (30 - depth)) & 1);
	if (tries[x].next[v]) {
		insert(tries[x].next[v], c, depth + 1);
	} else {
		tries[x].next[v] = ++nTrie;
		tries[nTrie].next[0] = tries[nTrie].next[1] = 0;
		tries[nTrie].count = 0;
		insert(nTrie, c, depth + 1);
	}
	tries[x].count = l_rank(x) + r_rank(x);
}

void bfs() {
	int i, j, x, m = 0;
	Edge* p;

	memset(vst, false, sizeof(vst));
	open[m++] = 0;
	vst[0] = true;
	for (i = 0; i < m; ++i) {
		x = open[i];
		for (p = g[x]; p; p = p->next) {
			if (!vst[p->to]) {
				a[p->to] = (a[x] ^ p->w);
				vst[p->to] = true;
				open[m++] = p->to;
			}
		}
	}
	for (i = 0; i < N; ++i) {
		insert(0, a[i], 0);
		assert(vst[i] == true);
	}
}

void input() {
	int i, x, y, w;

	initNet();
	scanf("%d%d", &N, &K);
	assert(2 <= N && N <= 150000);
	assert(0 <= K);
	for (i = 0; i < N - 1; ++i) {
		scanf("%d%d%d", &x, &y, &w);
		assert(0 <= x && x <= N - 1);
		assert(0 <= y && y <= N - 1);
		assert(0 < w);
		addEdge(x, y, w);
		addEdge(y, x, w);
	}
}

void solve() {
	int i, j, c, v, x, t, bit;
	LL ans = 0;

	if (K == 0) {
		printf("0\n");
		return;
	}
	bfs();
	for (i = 0; i < N; ++i) {
		c = (a[i] ^ K);
		v = 0;
		x = 0;
		for (j = 30; j >= 0; --j) {
			bit = ((c >> j) & 1);
			t = (v | ((!bit) << j));
			v |= (bit << j);
			if ((t ^ a[i]) < K) {
				if (bit == 0) {
					ans += r_rank(x);
				} else {
					ans += l_rank(x);
				}
			}
			if (tries[x].next[bit] == 0) break;
			x = tries[x].next[bit];
		}
	}
	ans = (ans - N) / 2;
	//printf("%I64d\n", ans);
	cout << ans << endl;
}


int main() {
	freopen("xortree2.in", "r", stdin);
	freopen("xortree2.out", "w", stdout);
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
5 3
0 1 3
1 2 3
2 3 3
3 4 3
*/
