#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s[50005][55];
char as[111], mark[50005];
int ms[111], p[111], mp[111], ind[50005], m;
int ansm[111];

bool cmp(int a, int b) {
	return strcmp(s[a], s[b]) < 0;
}

int getone() {
	memset(p, -1, sizeof(p));
	memset(mp, -1, sizeof(mp));
	memset(ms, 0, sizeof(ms));	
	int now = 0, best = 0;
	for (int i = 0; i < m; i++) {
		if (mark[i]) continue;
		int j, la;
		for (j = la = 0; j < now && as[j] == s[ind[i]][j]; j++) {			
			if (ms[j + 1]) la = j + 1;
		}
		for (; s[ind[i]][j]; j++) {
			as[j] = s[ind[i]][j];
			ms[j + 1] = 0;
		}
		now = j;
		ms[j] = ms[la] + 1;
		mp[j] = i;
		p[j] = la;
		if (ms[j] > best) {
			best = ms[j];
			int t = 0;
			for (int k = j; k; k = p[k]) {
				ansm[++t] = mp[k];
			}
		}
	}
	return best;
}

int main() {	
	freopen("gold.in", "r", stdin);
	freopen("gold.out", "w", stdout);
	int tn, ans, n, i, k, l;	
	for (assert(scanf("%d", &tn) == 1 && 1 <= tn && tn <= 10); tn--; ) {
		assert(scanf("%d%d%d%d", &m, &k, &l, &n) == 4);
		assert(1 <= m && m <= 50000);
		assert(1 <= k && k <= 26);
		assert(1 <= l && l <= 50);
		assert(1 <= n && n <= 10);
		for (i = 0; i < m; i++) {
			assert(scanf("%s", s[i]) == 1);
			assert(strlen(s[i]) > 0 && strlen(s[i]) <= l);
			for (int j = 0; s[i][j]; j++)
				assert(s[i][j] >= 'A' && s[i][j] <= 'A' + k - 1);
			ind[i] = i;
		}
		sort(ind, ind + m, cmp);
		ans = 0;
		memset(mark, 0, sizeof(char) * m);
		while (n--) {
			int t = getone();
			ans += t;
			for (i = 1; i <= t; i++) {
				mark[ansm[i]] = 1;
			}
		}
		printf("%d\n", ans);
	}
	assert(scanf("%*s") == EOF);
	return 0;
}
