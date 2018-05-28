#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAXN = 2009;
const int MAXS = 100009;

struct Point {
	int x, y, w;
	bool operator <(const Point& b) const {
		return x < b.x;
	}
};

struct SegNode {
	int b, e, sum, maxSum;
};

Point po[MAXN];
SegNode tree[MAXS];
int N, K;

inline int maxi(int a, int b) {
	return a > b ? a : b;
}

void buildSegTree(int x, int b, int e) {
	tree[x].b = b;
	tree[x].e = e;
	tree[x].sum = tree[x].maxSum = 0;
	if (b == e) return;
	int mid = (b + e) >> 1;
	buildSegTree(x * 2 + 1, b, mid);
	buildSegTree(x * 2 + 2, mid + 1, e);
}

void insert(int x, int ps, int value) {
	if (tree[x].b == tree[x].e) {
		tree[x].sum += value;
		tree[x].maxSum = tree[x].sum;
		return;
	}
	int mid = (tree[x].b + tree[x].e) >> 1;
	if (ps <= mid)
		insert(x * 2 + 1, ps, value);
	else
		insert(x * 2 + 2, ps, value);
	tree[x].sum += value;
	tree[x].maxSum = maxi(tree[x * 2 + 1].maxSum,
						  tree[x * 2 + 1].sum + tree[x * 2 + 2].maxSum);
}

bool check(int W, int H) {
	static Point p[MAXN * 2];
	int i, j, k, n2 = N / 2;
	for (i = 0; i < n2; i++) {
		p[i] = po[i];
		p[i].w = 1;
		p[i + n2].y = p[i].y + H;
		p[i + n2].x = p[i].x;
		p[i + n2].w = -1;
	}
	sort(p, p + N);
	buildSegTree(0, 1, N);
	for (i = j = 0; i < N;) {
		for (;j < N && p[j].x - p[i].x < W; j++)
			insert(0, p[j].y, p[j].w);
		if (tree[0].maxSum >= K)
			return true;
		//insert(0, p[i].y, -p[i].w);
		for (k = i; k < N && p[i].x == p[k].x; k++)
			insert(0, p[k].y, -p[k].w);
		i = k;
	}
	return false;
}

void input() {
	int i;
	scanf("%d%d", &N, &K);
	for (i = 0; i < N; i++)
		scanf("%d%d", &po[i].x, &po[i].y);
}

void solve() {
	int i, low, high, mid, ans = N * N, H;

	N *= 2;
	for (i = 1; i <= N / 2; ++i) {
        low = 1; high = ans / i;
        H = -1;
        while (low <= high) {
            mid = (low + high) >> 1;
            if (check(i, mid)) {
                H = mid;
                high = mid - 1;
            }
            else
            low = mid + 1;
        }
        if (H == -1) continue;
        if (i * H < ans)
            ans = i * H;
    }
	printf("%d\n", ans);
}

int main() {
    freopen("stars.in", "r", stdin);
    freopen("stars.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
	   input();
	   solve();
    }

	return 0;
}
