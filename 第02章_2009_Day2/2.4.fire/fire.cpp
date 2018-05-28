#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>
using namespace std;
const int MAXN = 500000;
struct Seg {
	int a, b, w;
	//线段按右端点顺序排序
	bool operator < (Seg other) const {
		if (b == other.b) return a < other.a;
		return b < other.b;
	}
}s[MAXN];

int n, top;
//dis[i] 线段i对应的子问题的最优值,dis为-1表示无穷大
//p[i] 若p[i]是负数则表示以i为根的集合有-p[i]个元素
//否则表示i的父亲是p[i]结点
//st 维护未删除点的栈
//prev[i] 预处理被线段i包含的最接近线段i的左端点的点
int dis[MAXN], p[MAXN], st[MAXN], prev[MAXN];
int b[MAXN], id[MAXN];

void preprocess() {
	int i, j;
	for (i = 0; i < n; i++) b[i] = s[i].b;
	prev[0] = 0;
	//预处理prev
	for (i = 1; i < n; i++) {
		j = lower_bound(b, b + i + 1, s[i].a) - b;
		prev[i] = j;
	}
}

//查找并查集的根
int usfind(int x) {
	int y = x, t;
	while (p[x] >= 0) x = p[x];
	//路径压缩
	while (y != x) t = p[y], p[y] = x, y = t;
	return x;
}

//并查集合并
void usjoin(int a, int b) {
	int r1 = usfind(a), r2 = usfind(b);		
	if (r1 == r2) return;
	p[r2] += p[r1], p[r1] = r2;	
}

void solve() {
	int i, j, m;
	preprocess();	
	memset(dis, -1, sizeof(int) * n);	
	memset(p, -1, sizeof(int) * n);	
	//初始值
	dis[0] = s[0].w, st[top = 1] = 0;

	for (i = 1; i < n; i++) {
		//通过并查集取得最优值对应的点
		j = usfind(prev[i]);

		//未能覆盖左端点
		if (j == i || j == i - 1 && dis[j] < 0) {
			dis[i] = -1;
			if (dis[i - 1] < 0) usjoin(i - 1, i);
		}
		if (j < i && dis[j] >= 0) {
			//计算当前线段的最优值
			dis[i] = dis[j] + s[i].w;

			//把前面最优值比现在最优值差的线段"删除"
			if (dis[i - 1] < 0) usjoin(i - 1, i);
			while (top && dis[st[top]] > dis[i]) {
				dis[st[top]] = -1;
				usjoin(st[top], i);
				top--;
			}
			st[++top] = i;
		}
	}	

}

int main() {
	freopen("fire.in", "r", stdin);
	freopen("fire.out", "w", stdout);
	int i, tn, t;
	int cn = 0;
	//对每一个test case
	for (assert(scanf("%d", &tn) == 1 && 1 <= tn && tn <= 20); tn--; ) {
		assert(scanf("%d%d", &n, &t) == 2 && 1 <= n && n <= 100000 && 1 <= t && t <= 1000000000);
		for (i = 1; i <= n; i++) {
			assert(scanf("%d%d%d", &s[i].a, &s[i].b, &s[i].w) == 3);
			assert(0 <= s[i].a && s[i].a < s[i].b && s[i].b <= t && 1 <= s[i].w && s[i].w <= 1000);
		}
		//排序
		sort(s + 1, s + n + 1);
		//加入一个左右端点为0的特殊线段
		//以方便处理
		s[0].a = s[0].b = s[0].w = 0;
		n++;

		solve();
		int ans = -1;
		//最后扫描一下取得答案
		for (i = 1; i < n; i++) {
			if (s[i].b == t && dis[i] != -1 && (ans == -1 || ans > dis[i])) {
				ans = dis[i];
			}
		}
		printf("%d\n", ans);
	}
	assert(scanf("%*s") == EOF);
	return 0;
}
