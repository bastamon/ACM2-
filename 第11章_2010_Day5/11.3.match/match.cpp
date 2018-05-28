#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 101
using namespace std;


int g[maxn][maxn] , p[maxn] , l[maxn][3] , n , total, status[maxn] , visited[maxn];
int gn[maxn], G[maxn][maxn];
int nodeList[maxn], nn;

void upgrade(int r)
{
	int j=r,i=l[r][1];
	for(p[i]=j;l[i][2]<0xff;) 
	{
		p[j]=i;
		j=l[i][2];
		i=l[j][1];
		p[i]=j;
	}
	p[j]=i;
}

int path(int r)
{
	int i,j,k,v,t,quit;
	memset(status,0,sizeof(status));
	status[r]=2;
	do{
		quit=1;
		for (int y = 0; y < nn; ++y)
		{
			i = nodeList[y];
			if(status[i]>1)
			for (int x=0;x<gn[i];++x)
			{
				j = G[i][x];
				if(g[i][j]>0&&p[j]!=i)
				if(status[j]==0){
				if(p[j]==0) {
					l[j][1]=i;
					upgrade(j);
					return 1;
				} else if(p[j]>0){
					g[i][j]=g[j][i]=-1;status[j]=1;
					l[j][1]=i;g[j][p[j]]=g[p[j]][j]=-1;
					l[p[j]][2]=j;status[p[j]]=2;
					quit=0;
				}
				}else if(status[j]>1&&(status[i]+status[j]<6)){
					quit=0;
					g[i][j]=g[j][i]=-1;
					memset(visited,0,sizeof(visited));
					visited[i]=1;
					k=i; v=2;
					while(l[k][v]!=0xff) {
						k=l[k][v];
						v=3-v;
						visited[k]=1;
					}
					k=j; v=2;
					while(!visited[k]) {
						k=l[k][v];
						v=3-v;
					}
					if(status[i]!=3) l[i][1]=j;
					if(status[j]!=3) l[j][1]=i;
					status[i]=status[j]=3;
					t=i;
					v=2;
					while(t!=k){
						if(status[l[t][v]]!=3) l[l[t][v]][v]=t;
						t=l[t][v];
						status[t]=3;
						v=3-v;
					}
					t=j;v=2;
					while(t!=k){
						if(status[l[t][v]]!=3) l[l[t][v]][v]=t;
						t=l[t][v];
						status[t]=3;
						v=3-v;
					}
				}
			}
		}
	}while(!quit);
	return 0;
}


void maxMatch()
{
	int i,j,k,pass;
	memset(p,0,sizeof(p));
	total = 0;
	nn = 0;
	for (i=1;i<=n;++i) if (gn[i]) nodeList[nn++] = i;
	do{
		i=0;
		do{
			if(p[++i])pass=0;
			else{
				memset(l,0,sizeof(l));
				l[i][2]=0xff;pass=path(i);
				for (int u = 0; u < nn;++u)
				{
					j = nodeList[u];
					for(int v=0;v<gn[j];++v)
					{
						k = G[j][v];
						//for(k=1;k<=n;k++)
						if(g[j][k]<0)g[j][k]=-g[j][k];
					}
				}
			};
		}while(i!=n&&!pass);
		if(pass) total+=2;
	} while(i!=n&&total!=n);
}



struct edge
{
	int a, b, l;
	int operator < (const edge & rhs) const 
	{
		if (l != rhs.l) return l < rhs.l;
		if (a != rhs.a) return a < rhs.a;
		return b < rhs.b;
	}
} e[maxn * maxn];

struct point
{
	int x, y;
} P[maxn];

struct edgeset
{
	int id, match_size;
	int operator < (const edgeset & rhs) const
	{
		if (match_size != rhs.match_size) return match_size < rhs.match_size;
		return id < rhs.id;
	}
} es[maxn * maxn];

int m, kn;
int end[maxn*maxn];

void addEdge(int a, int b)
{
	g[a][b] = g[b][a] = 1;
	G[a][gn[a]++] = b;
	G[b][gn[b]++] = a;
}

void initG()
{
	for (int i=1;i<=n;++i)
		for (int j = 0; j < gn[i];++j)
			g[i][G[i][j]] = 0;
	memset(gn, 0, sizeof(gn));	
}

int main()
{
	freopen("match.in", "r", stdin);
	freopen("match.out", "w", stdout);
	int i, j, k, t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (i=0;i<n;++i) scanf("%d%d", &P[i].x, &P[i].y);
		m = 0;
		for (i=0;i<n;++i)
		for (j=i+1;j<n;++j)
		{
			e[m].a = i + 1;
			e[m].b = j + 1;
			e[m].l = (P[i].x - P[j].x) * (P[i].x - P[j].x) + (P[i].y - P[j].y) * (P[i].y - P[j].y);
			++m;
		}
		sort(e, e+m);
		int kn = 0;
		e[m].l = 0x3fffffff;
		end[0] = -1;
		for (i=0;i<m;++i) if (e[i].l != e[i+1].l) end[++kn] = i;
		int best = 0;
		memset(g, 0, sizeof(g));
		memset(gn, 0, sizeof(gn));
		for (i=0;i<kn;++i)
		{
			// memset(g, 0, sizeof(g));
			initG();
			for (j=end[i]+1;j<=end[i+1];++j) addEdge(e[j].a, e[j].b);
			maxMatch();
			es[i].match_size = total;
			es[i].id = i;
			if (total > best) best = total;
			// printf("Length = %d, match_size = %d\n", e[end[i]+1].l, total);
		}
		sort(es, es+kn);
		if (es[kn-1].match_size == n / 2 * 2) 
		{
			printf("%d\n", es[kn-1].match_size / 2);
			continue;
		}

		// for (i=0;i<kn;++i)
		for (i=kn-1;i>0;--i)
		{
			// for (j = kn-1; j > i && es[i].match_size + es[j].match_size > best; --j)
			for (j = i-1; j >= 0 && es[i].match_size + es[j].match_size > best; --j)
			{
				initG();
				for (k=end[es[i].id]+1;k<=end[es[i].id+1];++k) addEdge(e[k].a,e[k].b);
				for (k=end[es[j].id]+1;k<=end[es[j].id+1];++k) addEdge(e[k].a,e[k].b);
				maxMatch();
				if (total > best) best = total;
				if (best == n / 2 * 2) break;
			}
			if (best == n / 2 * 2) break;
		}
		printf("%d\n", best / 2);
	}
	return 0;
}
