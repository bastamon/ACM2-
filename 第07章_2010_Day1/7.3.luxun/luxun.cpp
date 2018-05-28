#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
const int MAXN = 501;
const double INF = 1e-8;
double a[MAXN][MAXN], b[MAXN], x[MAXN];

bool gauss_eimination(int n) {
	int i, j, k, p, q[MAXN];
	double max, l;
	memset (q, 0, sizeof(q));
	for (k = 1; k <= n; k++) {
		p = 0; max = 0;
		for (i = 1; i <= n; i ++) {
			if (!q[i] && max + INF < fabs(a[i][k])) {
				max = fabs(a[i][k]);
				p = i;
			}
		}
		if (!p) {
			return false;
		} else {
			q[p] = 1;
		}
		for (i = 1; i <= n; i++) {
			if (i != p) {
				l = a[i][k] / a[p][k];
				for (j = 1; j <= n; j++) {
					a[i][j] = a[i][j] - l * a[p][j];
				}
				b[i] = b[i] - l * b[p];
			}
		}
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (fabs(a[i][j]) > INF) {
				x[j] = b[i] / a[i][j];
			}
		}
	}
	return true;
}

int main() {
	freopen("luxun.in", "r", stdin);
	freopen("luxun.out", "w", stdout);
	int tn, hp, i, j;
	double psha, pshan, ptao, pjinnang, pwuqi, pzhuangbei, pliannu;
	for (assert(scanf("%d", &tn) == 1 && 1 <= tn && tn <= 50); tn--; ) {
		int max_hp;
		assert(scanf("%d%d", &hp, &max_hp) == 2 &&
			   1 <= hp && hp <= max_hp && max_hp <= 50);
		hp = max_hp - hp + 1;
		assert(scanf("%lf%lf%lf", &psha, &pshan, &ptao) == 3);		
		assert(scanf("%lf%lf%lf%lf", &pjinnang, &pliannu, &pwuqi, &pzhuangbei)
			   == 4);
		assert(fabs(psha + pshan + ptao + pjinnang + pliannu + pwuqi +
					pzhuangbei - 1.0) < INF);

		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		a[4 * hp + 1][4 * hp + 1] = 1.0;
		for (i = 0; i < hp; i++) {
			// 4 * i + 1: no liannu, never sha
			// 4 * i + 2: no liannu, sha
			// 4 * i + 3: liannu, never sha
			// 4 * i + 4: liannu, sha
			for (j = 1; j <= 4; j++) {
				a[4 * i + j][4 * i + j] -= 1.0;
				b[4 * i + j] -= 1.0;
			}

			// jin nang, zhuang bei
			for (j = 1; j <= 4; j++) {
				a[4 * i + j][4 * i + j] += pjinnang + pzhuangbei;				
			}

			// tao
			if (i < hp - 1) {
				for (j = 1; j <= 4; j++) {
					a[4 * i + j][4 * (i + 1) + j] += ptao;					
				}
			} else {
				for (j = 1; j <= 4; j++) {
					a[4 * i + j][4 * hp + 1] += ptao;					
				}
			}

			// shan
			for (j = 1; j <= 4; j++) {
				a[4 * i + j][4 * hp + 1] += pshan;				
			}
			
			// sha
			a[4 * i + 1][4 * i + 2] += psha;			
			a[4 * i + 2][4 * hp + 1] += psha;			
			a[4 * i + 3][4 * i + 4] += psha;			
			a[4 * i + 4][4 * i + 4] += psha;
			
			// liannu
			a[4 * i + 1][4 * i + 3] += pliannu;
			a[4 * i + 2][4 * i + 4] += pliannu;
			a[4 * i + 3][4 * i + 3] += pliannu;
			a[4 * i + 4][4 * i + 4] += pliannu;
			
			// wuqi
			a[4 * i + 1][4 * i + 1] += pwuqi;
			a[4 * i + 2][4 * i + 2] += pwuqi;
			a[4 * i + 3][4 * i + 1] += pwuqi;
			a[4 * i + 4][4 * i + 2] += pwuqi;			
		}

		if (fabs(pliannu) < INF) {
			for (i = 0; i < hp; i++) {
				memset(a[4 * i + 3], 0, sizeof(a[4 * i + 3]));
				memset(a[4 * i + 4], 0, sizeof(a[4 * i + 4]));
				b[4 * i + 3] = 0;
				a[4 * i + 3][4 * i + 3] = a[4 * i + 4][4 * i + 4] = 1.0;
			}			
		}

		if (gauss_eimination(4 * hp + 1)) {
			printf("%.4lf\n", x[1] - 1);
		} else {
			printf("Lian Mian Bu Jue\n");
		}
	}
	return 0;
}
