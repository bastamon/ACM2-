//(x,y)-> (y,x-y) ->(x-y,2y-x) ->(2y-x, 2x-3y)
#include <stdio.h>
#include <string.h>
int mrk[1000][1000], step[1000][1000], len[2000], ln;
void init()
{
	int i, j, x, y, m;
	memset(mrk, 0, sizeof(mrk));
	memset(step, 0, sizeof(step));
	memset(len, 0, sizeof(len));
	ln = 0;
	for (i=0;i<1000;++i)
	{
		for (j=0;j<1000;++j)
		{
			if (mrk[i][j]) continue;
			++ln;
			m = 0;
			x = i;
			y = j;
			while (!mrk[x][y])
			{
				mrk[x][y] = ln;
				step[x][y] = m++;
				int t = x;
				x = y;
				y = (t - y + 1000) % 1000;
			}
			len[ln] = m;
		}
	}
}
int main()
{
	freopen("teleportation.in", "r", stdin);
	freopen("teleportation.out", "w", stdout);
	int t, x1, y1, x2, y2;
	init();
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (mrk[x1][y1] != mrk[x2][y2]) puts("-1"); else
		{
			int loop = (step[x2][y2] - step[x1][y1] + len[mrk[x1][y1]]) % len[mrk[x1][y1]];
			if (loop == 1) loop = len[mrk[x1][y1]] + 1;
			printf("%d\n", loop % 3 ? loop / 3 + 1 : loop / 3);
		}		
	}
	return 0;
}
