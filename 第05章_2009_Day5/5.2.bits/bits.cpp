#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>
using namespace std;

const int maxn=1009;
const int inf=0x3ffffff;


struct Point{
	int x, y;
};

Point p[maxn];

bool operator < (const Point &a,const Point &b)
{
	return a.y<b.y||(a.y==b.y&&a.x<b.x);
}

int N, K, B;
int a[maxn], vst[2][maxn];
int dp[maxn][maxn][4];

void input()
{
	int i, j, b, n = 0;
	scanf("%d%d%d",&B, &N, &K);
	assert(1 <= B && B <= 1000);
	assert(1 <= N && N <= 1000);
	assert(1 <= K && K <= N);
	for (i = 1; i <= 2; ++i)
        for (j = 1; j <= B; ++j) {
            scanf("%d", &b);
            assert(b == 1 || b == 0);
            if (b == 1) {
                p[n].x = i;
                p[n++].y = j;
            }
        }
    assert(n == N);
}

inline int mini(int a,int b) { return a<b?a:b; }

void calc(int x, int y)
{
	int i, j;
	for(i=0; i<4; i++)
	{
		int c, t;
		if(i<=1) c=a[x]-a[x-1];
		else c=2*(a[x]-a[x-1]);
		t=dp[x-1][y][i]+c;
		if(dp[x][y][i]>t) dp[x][y][i]=t;
		if(i<=1)
		{
			t=dp[x-1][y][3]+a[x]-a[x-1];
			if(dp[x][y][i]>t) dp[x][y][i]=t;
		}
		if(i==3)
		{
			t=dp[x-1][y-1][0]+a[x]-a[x-1]+1;
			if(dp[x][y][i]>t) dp[x][y][i]=t;
			t=dp[x-1][y-1][1]+a[x]-a[x-1]+1;
			if(dp[x][y][i]>t) dp[x][y][i]=t;
		}
	}
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			int c, t=inf;
			if(i<=1) c=1;
			else c=2;
			if(i!=3) t=dp[x-1][y-1][j]+c;
			else if(y-2>=0) t=dp[x-1][y-2][j]+c;
			if(dp[x][y][i]>t)
				dp[x][y][i]=t;
		}
	if(y<2) dp[x][y][3]=inf;
	if(vst[0][x]) dp[x][y][1]=inf;
	if(vst[1][x]) dp[x][y][0]=inf;
}

void solve()
{
	int i, j, k, M=0;
	
    memset(vst, 0, sizeof(vst));
	sort(p,p+N);
	
	for(i=0; i<N; i=j)
	{
		for(j=i; j<N&&p[j].y==p[i].y; j++);
		if(j-i==1)
		{
			if(p[i].x==1) vst[0][++M]=1;
			else vst[1][++M]=1;
		}
		else
		{
			vst[0][++M]=1;
			vst[1][M]=1;
		}
		a[M]=a[M]=p[i].y;

	}
	for(i=1; i<=M; i++)
		for(j=0; j<=K; j++)
			for(k=0; k<4; k++)
				dp[i][j][k]=inf;
	for(i=1; i<=M; i++)
		for(j=1; j<=K; j++)
			calc(i,j);
	int ans=inf;
	for(i=0; i<4; i++)
		if(dp[M][K][i]<ans)
			ans=dp[M][K][i];
	printf("%d\n",ans);

}

int main()
{
	freopen("bits.in", "r", stdin);
	freopen("bits.out", "w", stdout);
    int T;
    scanf("%d", &T);
    assert(1 <= T && T <= 10);
    while (T--) {
	   input();
	   solve();
    }
   // while (true);
	return 0;
}
