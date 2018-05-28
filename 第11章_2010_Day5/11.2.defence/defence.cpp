#include <stdio.h>
#include <string.h>
#include <time.h>
#define maxn 100
#define maxm 1000

int map[maxn][maxn];
int n, m, r, money, attack;

struct plant
{
	int col;
	int cost;
} plants[maxn][2];
int pn[maxn];

struct monster
{
	int hp, row, cost;
} monsters[maxm];
int mn;

int maxHP[maxn], maxAtt[maxn];

void statMonster(int num)
{
	int i, j;
	memset(maxHP, 0, sizeof(maxHP));
	for (i=0;i<=num;++i)
	{
		if (monsters[i].hp > maxHP[monsters[i].row]) maxHP[monsters[i].row] = monsters[i].hp;
	}
	// for (i=0;i<n;++i) printf("row[%d]:%d\n", i, maxHP[i]);
	// puts("----------");

}

int check() 
{
	int i, j;
	for (i=0;i<n;++i)
	{
		if (maxAtt[i] * attack < maxHP[i]) return false;
	}
	return true;
}

int startClock, totalTick;

void startTime()
{
	startClock = clock();
}

void stopTime()
{
	totalTick += clock() - startClock;
}

int findMinCost() 
{
	int i, j, k, l, x, y;
	int now[1<<14], last[1<<14];
	int cover[maxn];
	int R;
	
	if (!check()) return 0x3fffffff;

	// initialize row[0..r]
	memset(now, -1, sizeof(now));
	R = r + 1; // affected rows num
	if (R > n) R = n;
	for (i=0; i < 1 <<2*R; ++i)
	{
		
		now[i << 2*r] = 0;
		for (j=0; j< 2*R;++j)
		{
			if (!(i & 1 << j)) continue;
			if (j%2+1 > pn[j/2]) break;
			now[i << 2 * r] += plants[j/2][j%2].cost;
		}
		//printf("$%d: break on %d, now[i]=%d\n", i, j, now[i]);
		if (j < 2 * R) now[i << 2 * r] = -1;
	}
		
	R = 2 * r + 1; // affected rows num
	// int totalState = 0;
	for (i=0;i<n;++i)
	{
		// printf("State %d\n", i);
		memcpy(last, now, sizeof(now));
		memset(now, -1, sizeof(now));
		memset(cover, -1, sizeof(cover));
		for (j = 0; j < 1<<2*R; ++j) 
		{
			if (last[j] == -1) continue;
			// ++totalState;
			// printf("cost:%d,  %d(", last[j], j);
			int attackCount = 0;
					// startTime();
			for (k=0;k<2*R;++k)
			{
				if (!(j & 1<<k)) continue;
				// if (i - r + k / 2 >= n || i - r + k/2 < 0) puts("error1");
				// if (pn[i-r+k/2] - 1 < k%2) puts("error2");
				// printf("%d:%d,", i-r+k/2, k%2);
				int col = plants[i-r+k/2][k%2].col;
				for (l = col - r; l <= col + r; ++l)
				{
					if (l < 0 || l >= m) continue;
					if (cover[l] != j)
					{
						++attackCount;
						cover[l] = j;
					}
				}
			}
			// stopTime();
			// puts(")");
			// printf("attackCount=%d\n", attackCount);
			if (attackCount * attack < maxHP[i]) continue;
			int en = 0;
			if (i + r + 1 < n) en = pn[i + r + 1] * 2;
			if (en == 0) en = 1;
			for (x = 0; x < en; ++x)
			{
				int totalCost = 0;
				for (k = 0; k < 2; ++k)
				{
					if (!(x & (1<<k))) continue;
					totalCost += plants[i+r+1][k].cost;
				}
				int nextState = (j >> 2) + (x << 2*R - 2);
				// printf("nextState = %d, totalCost =%d\n", nextState, totalCost);
				if (now[nextState] == -1 || now[nextState] > last[j] + totalCost)
				{
					if (last[j] + totalCost <= money) now[nextState] = last[j] + totalCost;
				}
				// recover the "cover" array
				for (k = 0; k < 2; ++k)
				{
					if (!(x & (1<<k))) continue;
					totalCost -= plants[i+r+1][k].cost;
				}
			}
		}
	}
	int minn = 0x3fffffff;
	for (i = 0; i < 1<<2*R; ++i)
	{
		if (now[i] != -1 && now[i] < minn) 
		{
			minn = now[i];
			// printf("i:%d\n", i);
		}
	}
	// printf("avg state = %d\n", totalState / n);
	return minn;
}

void solve()
{
	int l = 0, r = mn-1;
	int ans = -1, anum;
	while (l <= r) 
	{
		int mid = (l+r)/2, tmp;
		statMonster(mid);
		if ((tmp = findMinCost()) <= money)
		{
			// printf("success %d\n", tmp);
			ans = tmp;
			anum = mid;
			l = mid + 1;
		} else r = mid - 1;
		// printf("Mid = %d, tmp = %d\n", mid, tmp);
	}
	if (ans == -1) puts("0 0");
	else printf("%d %d\n", anum+1, ans);
}

int mrk[maxn][maxn];
void initAtt()
{
	int i, j, x, y;
	memset(maxAtt, 0, sizeof(maxAtt));
	memset(mrk, 0, sizeof(mrk));
	for (i=0;i<n;++i)
	{
		for (j=0;j<pn[i];++j)
		{	
			for (x=i - r; x <= i + r; ++x)
			for (y=plants[i][j].col - r; y <= plants[i][j].col + r; ++y)
			{
				if ( x < 0 || x >= n || y < 0 || y >= m) continue;
				if (!mrk[x][y])
				{
					mrk[x][y] = 1;
					maxAtt[x]++;
				}				
			}
		}
	}
}

int main() 
{
	freopen("defence.in", "r", stdin);
	freopen("defence.out", "w", stdout);
	totalTick = 0;

	int t, i, j;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d%d", &n, &m, &r);
		scanf("%d%d", &money, &attack);
		memset(pn, 0, sizeof(pn));
		for (i=0;i<n;++i)
		{
			for (j=0;j<m;++j)
			{
				scanf("%d", &map[i][j]);
				if (map[i][j])
				{
					plants[i][pn[i]].col = j;
					plants[i][pn[i]].cost = map[i][j];
					++pn[i];
				}				
			}
		}
		scanf("%d", &mn);
		for (i=0;i<mn;++i) 
			scanf("%d%d", &monsters[i].row, &monsters[i].hp);
		initAtt();
		solve();
	}

	// printf("%d\n", totalTick);
	return 0;
}
