#include <stdio.h>
#include <string.h>
const int N = 2005;

char s[N], t[N];
int diff[N], total[N];

int main() {
	freopen("sub.in", "r", stdin);
	freopen("sub.out", "w", stdout);
	int ca;
	scanf("%d", &ca);
	while (ca--) {
		int d;
		scanf("%d%s", &d, s);
		int h = strlen(s), hh = h / 2;
		bool found = false;
		for (int i = hh; i > 0; i--) {
			for (int j = i; j < h; j++) {
				diff[j] = s[j] != s[j - i] ? 1 : 0;
			}
			total[i] = diff[i];
			int ii = i + i;
			for (int j = i + 1; j < ii; j++) total[j] = total[j - 1] + diff[j];
			for (int j = ii; j < h; j++) total[j] = total[j - 1] + diff[j] - diff[j - i];
			for (int j = i + i - 1; j < h; j++) if (total[j] <= d) {
				found = true;
				int u = 0;
				for (int k = j - i - i + 1; k <= j; k++) {
					t[u++] = s[k];
				}
				t[i + i] = 0;
				printf("%d %s\n", i + i, t);
				break;
			}
			if (found) break;
		}
		if (!found) puts("Not found");
	}
	return 0;
}
