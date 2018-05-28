#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <utility>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 29;
const int M = N / 2;

int dp[1 << M][M][M];
int dis[N][N];
pair <int, int> PD[M];
int nPD, size;
int vtID[1 << M][M], nvtID[1 << M];
int oneBit[1 << 16];

void input() {
	scanf("%d", &size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			scanf("%d", &dis[i][j]);
		}
	}
	// floyd
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
				}
			}
		}
	}

	nPD = 0;
	for (int i = 0; i < size / 2; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		PD[nPD++] = make_pair(x, y);
	}
}

void preprocess() {
  memset(dp, 0, sizeof(dp));
  memset(nvtID, 0, sizeof(nvtID));
  memset(vtID, 0, sizeof(vtID));
  memset(oneBit, 0, sizeof(oneBit));
  
	int i, j, k, n = size / 2;
	for (i = 1; i < (1 << n); ++i) {
		for (j = 0; j < n; ++j) {
			if (i & (1 << j)) {
				vtID[i][nvtID[i]++] = j;
			}
			for (k = 0; k < n; ++k)
				dp[i][j][k] = INF;
		}
	}
	for (i = 1; i < (1 << 16); ++i) {
		for (j = i; j; j >>= 1)
			if (j & 1) ++oneBit[i];
	}
}

inline void calc(int x, int y) {
	int i, j, k, l1, l2, l3, t, z = x | y;
	for (l1 = 0; l1 < nvtID[x]; ++l1) {
		i = vtID[x][l1];
		for (l2 = 0; l2 < nvtID[x]; ++l2) {
			j = vtID[x][l2];
			for (l3 = 0; l3 < nvtID[y]; ++l3) {
				k = vtID[y][l3];
				t = dp[x][i][j] + dp[y][k][k] + dis[PD[k].second][PD[i].first];
				if (dp[z][k][j] > t)
					dp[z][k][j] = t;
				t = dp[x][i][j] + dp[y][k][k] + dis[PD[j].second][PD[k].first];
				if (dp[z][i][k] > t)
					dp[z][i][k] = t;
				if ((y & (y - 1)) == 0) { // 2 ^ k
					t = dp[x][i][j] + dis[PD[k].first][PD[i].first] +dis[PD[j].second][PD[k].second];
					if (dp[z][k][k] > t)
						dp[z][k][k] = t;
				}
			}
		}
	}
}

#define getOne(x) (oneBit[(x) >> 16] + oneBit[(x) & 0xffff])
void solve() {
	int i, j, k, x, y, n = size / 2, t, ans = INF;
	
	preprocess();
	for (x = 1; x < (1 << n); ++x) {
		if ((x & (x - 1)) == 0) { // 2 ^ k
			k = vtID[x][0];
			dp[x][k][k] = dis[PD[k].first][PD[k].second];
		} else {
			for (y = 1; y < x; ++y)
				if (getOne(x) >= getOne(y) * 2)  {
					if (x == (x | y))
						calc(x ^ y, y);
				}
		}
	}
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) {
			t = dp[(1 << n) - 1][i][j] + dis[0][PD[i].first] + dis[PD[j].second][0];
			if (t < ans)
				ans = t;
		}
	printf("%d\n", ans);
}

int main() {
  freopen("stupid.in", "r", stdin);
  freopen("stupid.out", "w", stdout);
  int T;
  scanf("%d", &T);
  while (T--) {
    //printf("%d\n", T);
    input();
    solve();
  }
	return 0;
}
