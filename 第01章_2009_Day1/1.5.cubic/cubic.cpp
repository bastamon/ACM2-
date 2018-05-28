#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define min(a,b) ((a) < (b) ? (a) : (b))
#define maxn (1000 + 1)
#define maxm (4 * maxn)
#define inf 5000

int x[2 * maxn];
int y[2 * maxn];
int xCnt;
int yCnt;

struct SegmentTree1D {
	struct Node1D {
		int delta;
		int minimal;
		Node1D() {
			delta = minimal = 0;
		}
	}node[maxm];
	void clear() {
		memset(node, 0, sizeof(Node1D) * 4 * yCnt);
	}
	int query() {
		return node[0].delta + node[0].minimal;
	}
	void modify(int root, int left, int right, int l, int r, int d) {
		if (l > right || r < left) return; 
		if (l <= left && right <= r) {
			node[root].delta += d;
			return;
		} 
		int mid = (left + right) >> 1;
		int lc = root * 2 + 1, rc = lc + 1;
		modify(lc, left, mid, l, r, d);
		modify(rc, mid + 1, right, l, r, d);
		node[root].minimal = min(node[lc].minimal + node[lc].delta, 
				node[rc].minimal + node[rc].delta);
	}
};

struct Tree {
	SegmentTree1D node[2 * maxn]; 
	int query() {
		int ret = inf;
		for (int i = 0; i < xCnt; ++i) {
			int cur = node[i].query();
			if (cur < ret) ret = cur;
		}        
		return ret;
	}
	void modify(int x1, int x2, int y1, int y2, int d) {
		for (int i = x1; i <= x2; ++i) {
			node[i].modify(0, 0, yCnt - 1, y1, y2, d);
		} 
	}
	void clear() {
		for (int i = 0; i < xCnt; ++i) {
			node[i].clear();
		}
	}
}tree;

struct Box {
	int x1, y1, z1, x2, y2, z2;
	void init() {
		scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
	}
	Box() {}
	Box(int xx1, int yy1, int zz1, int xx2, int yy2, int zz2) {
		x1 = xx1, y1 = yy1, z1 = zz1;
		x2 = xx2, y2 = yy2, z2 = zz2;
	}
}boxes[maxn];

struct Event {
	int boxId;
	int z;
	bool isBottom; 
	Event() {}
	Event(int id, int zz, bool flag) : boxId(id), z(zz), isBottom(flag) {
	}
}event[2 * maxn];
int eCnt;

bool eventCmp(const Event &a, const Event &b) {
	if (a.z != b.z) return a.z < b.z;
	return a.isBottom < b.isBottom;
}

bool canPack(int length, int width, int height, Box *boxes, int n, int l) {
	xCnt = 0, yCnt = 0;
	eCnt = 0;
	int i;
	for (i = 0; i < n; ++i) {
		boxes[i].x1 -= l;
		boxes[i].y1 -= l;
		boxes[i].z1 -= l;
		if (boxes[i].x1 >= 0) x[xCnt++] = boxes[i].x1;
		x[xCnt++] = boxes[i].x2;
		if (boxes[i].y1 >= 0) y[yCnt++] = boxes[i].y1;
		y[yCnt++] = boxes[i].y2;
		event[eCnt++] = Event(i, boxes[i].z1, true);
		event[eCnt++] = Event(i, boxes[i].z2, false);
	}
	boxes[n] = Box(-l, -l, -inf, length + 1, width + 1, 0);
	x[xCnt++] = 0;
	y[yCnt++] = 0;

	event[eCnt++] = Event(n, boxes[n].z1, true);
	event[eCnt++] = Event(n, boxes[n].z2, false);

	sort(x, x + xCnt);
	xCnt = unique(x, x + xCnt) - x;
	sort(y, y + yCnt);
	yCnt = unique(y, y + yCnt) - y;

	sort(event, event + eCnt, eventCmp);
	tree.clear();
	bool ok = false;
	for (i = 0; i < eCnt; ++i) {
		Event &e = event[i];      
		Box &b = boxes[e.boxId];

		if (e.z + l > height) break;

		int x1, x2, y1, y2;
		if (b.x1 < 0) x1 = 0;
		else x1 = lower_bound(x, x + xCnt, b.x1) - x + 1;

		if (b.y1 < 0) y1 = 0;
		else y1 = lower_bound(y, y + yCnt, b.y1) - y + 1;

		if (b.x2 + l > length) x2 = xCnt - 1;
		else x2 = lower_bound(x, x + xCnt, b.x2) - x - 1;

		if (b.y2 + l > width) y2 = yCnt - 1;
		else y2 = lower_bound(y, y + yCnt, b.y2) - y - 1;

		if (e.isBottom) {
			tree.modify(x1, x2, y1, y2, +1);
		} else {
			tree.modify(x1, x2, y1, y2, -1);
			if (tree.query() == 0) {
				ok = true;
				break;
			}
		}
	}
	for (i = 0; i < n; ++i) {
		boxes[i].x1 += l;
		boxes[i].y1 += l;
		boxes[i].z1 += l;
	}
	return ok;
}

int main() {
	freopen("cubic.in", "r", stdin);
	freopen("cubic.out", "w", stdout);
	int t;
	scanf("%d", &t);
	for (int kase = 1; kase <= t; ++kase) {
		int n, length, width, height;
		scanf("%d%d%d%d", &n, &length, &width, &height);
		for (int i = 0; i < n; ++i) {
			boxes[i].init();
		}
		int ans = 0;

		int lo = 0, hi = length;
		if (width < hi) hi = width;
		if (height < hi) hi = height;

		while (lo <= hi) {
			int mi = (lo + hi) >> 1;
			if (canPack(length, width, height, boxes, n, mi)) {
				lo = mi + 1; 
				ans = mi;
			} else {
				hi = mi - 1; 
			}
		}

		printf("Case %d: %d\n", kase, ans);
	}
	return 0;
}
