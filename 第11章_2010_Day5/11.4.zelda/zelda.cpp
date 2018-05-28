#include <stdio.h>
#include <string.h>
#include <set>
#include <vector>
using namespace std;

const int MAXN = 101;

struct status {
	int lx, ly, ax, ay, bx, by, hp;
	int step;
	int operator < (const status & rhs) const {
		if (lx != rhs.lx) return lx < rhs.lx;
		if (ly != rhs.ly) return ly < rhs.ly;
		if (ax != rhs.ax) return ax < rhs.ax;
		if (ay != rhs.ay) return ay < rhs.ay;
		if (bx != rhs.bx) return bx < rhs.bx;
		if (by != rhs.by) return by < rhs.by;
		return false;
		// return hp < rhs.hp;
	}
} org, tar;
int n, m;
char map[MAXN][MAXN];
set<status> hash;
vector<status> list;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int goal(status & st) {
	return st.ax == tar.ax && st.bx == tar.bx && st.ay == tar.ay && st.by == tar.by;
}

void readdata() {
	int i, j;
	for (i=0;i<n;++i) {
		scanf("%s", map[i]);
		for (j=0;j<m;++j) {
			if (map[i][j] == 'L') org.lx = i, org.ly = j;
			if (map[i][j] == 'a') org.ax = i, org.ay = j;
			if (map[i][j] == 'b') org.bx = i, org.by = j;
			if (map[i][j] == 'A') tar.ax = i, tar.ay = j;
			if (map[i][j] == 'B') tar.bx = i, tar.by = j;
		}
	}	
}

void bfs() {
	int head, i, j, ok, hurt;
	status cur, nxt, ans;
	org.step = 0;
	list.clear();
	list.push_back(org);
	hash.clear();
	head = 0;
	ok = false;
	while (!ok && head<list.size()) {
		cur = list[head++];
		for (i=0;i<4;++i) {
			nxt = cur;
			nxt.step = cur.step + 1;
			nxt.lx += dx[i];
			nxt.ly += dy[i];
			nxt.ax += dx[i];
			nxt.ay += dy[i];
			nxt.bx += dx[(i+2)%4];
			nxt.by += dy[(i+2)%4];
			hurt = 0;
			if (nxt.lx < 0 || nxt.lx >= n || nxt.ly < 0 || nxt.ly >= m) continue;
			if (map[nxt.lx][nxt.ly] == 'X') continue;
			if (nxt.ax < 0 || nxt.ax >= n || nxt.ay < 0 || nxt.ay >= m || map[nxt.ax][nxt.ay] == 'X') {
				nxt.ax -= dx[i];
				nxt.ay -= dy[i];
				hurt = 1;
			}
			if (nxt.bx < 0 || nxt.bx >= n || nxt.by < 0 || nxt.by >= m || map[nxt.bx][nxt.by] == 'X') {
				nxt.bx -= dx[(i+2)%4];
				nxt.by -= dy[(i+2)%4];
				hurt = 1;
			}
			if (nxt.ax == nxt.bx && nxt.ay == nxt.by) continue;
			if (nxt.ax == nxt.lx && nxt.ay == nxt.ly) continue;
			if (nxt.lx == nxt.bx && nxt.ly == nxt.by) continue;
			if (nxt.ax == cur.lx && nxt.ay == cur.ly && nxt.lx == cur.ax && nxt.ly == cur.ay) continue;
			if (nxt.bx == cur.lx && nxt.by == cur.ly && nxt.lx == cur.bx && nxt.ly == cur.by) continue;
			if (nxt.ax == cur.bx && nxt.ay == cur.by && nxt.bx == cur.ax && nxt.by == cur.ay) continue;
			nxt.hp = cur.hp - hurt;
			if (nxt.hp <= 0) continue;
			if (hash.count(nxt)) continue;
			list.push_back(nxt);
			hash.insert(nxt);
			if (goal(nxt)) {
				ans = nxt;
				ok = true;
				break;
			}
		}
	}
	if (!ok) {
		puts("impossible");
	} else {
		printf("%d\n", ans.step);
		//printf("queue size %d\n", list.size());
	}
}

int main() {
	freopen("zelda.in", "r", stdin);
	freopen("zelda.out", "w", stdout);
	int i, j;
	while (scanf("%d%d%d", &n, &m, &org.hp)!=EOF) {
		readdata();
		bfs();
	}
	// while (scanf("%d%d", &n, &m) != EOF) {
		// org.hp = 100;
		// readdata();
		// bfs();
	// }
	return 0;
}
