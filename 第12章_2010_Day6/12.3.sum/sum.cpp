#include <stdio.h>
#include <string.h>
#include <algorithm>
const int M = 1005;
const int N = 1 << 12;

struct node{
	int op;
	int x1, y1, x2, y2;
} qu[M];

int opcount[N], clearcount[N], clear[N], count;
bool op[N], mark[N];

void init() {
	memset(op, 0, sizeof(op));
	memset(clear, -1, sizeof(clear));
	memset(opcount, -1, sizeof(opcount));
	memset(clearcount, -1, sizeof(clearcount));
	memset(mark, 0, sizeof(mark));
}

void mod2(int id, int st, int en, int u, int v, int clearct) {
	if (clear[id] != -1) {
		if (clearcount[id] > clearct) clearct = clearcount[id];
	} 
		if (opcount[id] < clearct) {
			op[id] = false;
			opcount[id] = count;
		}

	mark[id] = true;
	if (u == st && v == en) {
		op[id] ^= true;
		opcount[id] = count;
		return;
	}

	int mid = (st + en) >> 1, id1 = (id << 1) + 1, id2 = id1 + 1;

		if (v <= mid) {
			mod2(id1, st, mid, u, v, clearct);
		} else if (u > mid) {
			mod2(id2, mid + 1, en, u, v, clearct);
		} else {
			mod2(id1, st, mid, u, mid, clearct);
			mod2(id2, mid + 1, en, mid + 1, v, clearct);
		}
}

void mod(int id, int st, int en, int u, int v, int k, int clearct, bool b) {
	if (u == st && v == en) {
		op[id] = false;
		opcount[id] = count;
		if (k == 0) {
			clear[id] = 0;
		} else if (k == 1) {
			clear[id] = 1;
		}
		clearcount[id] = count;
		return ;
	}

	mark[id] = true;
	int mid = (st + en) >> 1, id1 = (id << 1) + 1, id2 = id1 + 1;
	if (clear[id] != -1) {
		if (clearcount[id] > clearct) clearct = clearcount[id];
	}
		if (opcount[id] < clearct) {
			op[id] = false;
		}
		if (op[id]) b ^= true;
		op[id] = false;
		opcount[id] = count;

		if (v <= mid) {
			mod(id1, st, mid, u, v, k, clearct, b);
			if (b) {
				mod2(id2, mid + 1, en, mid + 1, en, clearct);
				op[id] = false;
			}
		} else if (u > mid) {
			mod(id2, mid + 1, en, u, v, k, clearct, b);
			if (b) {
				mod2(id1, st, mid, st, mid, clearct);
				op[id] = false;
			}
		} else {
			mod(id1, st, mid, u, mid, k, clearct, b);
			mod(id2, mid + 1, en, mid + 1, v, k, clearct, b);
		}
}

int check(int id, int st, int en, int cleark, int clearct, int b) {
	if (clear[id] != -1) {
		if (clearcount[id] > clearct) {
			cleark = clear[id];
			clearct = clearcount[id];
		}
	}
	if (op[id] && opcount[id] > clearct) b ^= true;
	if (!mark[id]) {
		if (cleark < 1) return b ? en - st + 1 : 0;
		return b ? 0 : en - st + 1;
	}
	int mid = (st + en) >> 1, id1 = (id << 1) + 1, id2 = id1 + 1;
	if (st == en) {
		if (cleark < 1) return b ? 1 : 0;
		return b ? 0 : 1;
	}
	int tmp = check(id1, st, mid, cleark, clearct, b) + check(id2, mid + 1, en, cleark, clearct, b);
	return tmp;
}

void solve(int n, int m) {
	for (int i = 0; i < n; i++) {
		if (i > 0) printf(" ");
		count = 0;
		init();
		for (int j = 0; j < m; j++) {
			if (qu[j].x1 <= i && qu[j].x2 >= i) {
				if (qu[j].op < 2) mod(0, 0, n - 1, qu[j].y1, qu[j].y2, qu[j].op, -1, false);
				else mod2(0, 0, n - 1, qu[j].y1, qu[j].y2, -1); 
			}
			count++;
		}
		printf("%d", check(0, 0, n - 1, -1, -1, false));
	}
	puts("");
}

int main() {
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	int ca;
	scanf("%d", &ca);
	while (ca--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++)
			scanf("%d%d%d%d%d", &qu[i].op, &qu[i].x1, &qu[i].y1, &qu[i].x2, &qu[i].y2);
		solve(n, m);
		for (int i = 0; i < m; i++) {
			int tmp = qu[i].x1; qu[i].x1 = qu[i].y1; qu[i].y1 = tmp;
			tmp = qu[i].x2; qu[i].x2 = qu[i].y2; qu[i].y2 = tmp;
		}
		solve(n, m);
	}
	return 0;
}
