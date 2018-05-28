#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>

using namespace std;

const int maxn=309;
const int maxm=90009;
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

struct Edge
{
	int to;
	Edge *next;
};

Edge edgeM[maxm*8], *g[maxm], *gt[maxm];
int dfs_time, order[maxm], scc_id[maxm], sccID, scc_vn[maxm];
bool vst[maxm];
int N, M, ID, in_degree[maxm], out_degree[maxm];
int mat[maxn][maxn];

void link(Edge *g[],int x,int y)
{
	Edge *p=&edgeM[ID++];
	p->to=y;
	p->next=g[x];
	g[x]=p;
}

void dfs(int x)
{
	vst[x]=true;
	Edge *p;
	for(p=g[x]; p; p=p->next)
		if(!vst[p->to])
			dfs(p->to);
	order[dfs_time++]=x;
}

void dfst(int x)
{
	vst[x]=true;
	scc_vn[scc_id[x]=sccID]++;
	Edge *p;
	for(p=gt[x]; p; p=p->next)
		if(!vst[p->to])
			dfst(p->to);
}


void input()
{
	int i, j;

    ID = 0;
    dfs_time = 0;
    sccID = 0;
    memset(g, 0, sizeof(g));
    memset(gt, 0, sizeof(gt));
    memset(vst, 0, sizeof(vst));
    memset(scc_vn, 0, sizeof(scc_vn));
    memset(in_degree, 0, sizeof(in_degree));
    memset(out_degree, 0, sizeof(out_degree));

	scanf("%d%d",&N,&M);
	assert(1 <= N && N <= 300);
	assert(1 <= M && M <= 300);
	for(i=0; i<N; i++)
		for(j=0; j<M; j++) {
			scanf("%d",&mat[i][j]);
			assert(1 <= mat[i][j] && mat[i][j] <= 1000000);
        }
}

void solve()
{
	int i, j, k;
	Edge *p;
	for(i=0; i<N; i++)
		for(j=0; j<M; j++)
			for(k=0; k<4; k++)
			{
				int r=i+dx[k], c=j+dy[k];
				if(r>=0 && r<N && c>=0 && c<M && mat[i][j]>=mat[r][c])
				{
					link(g,i*M+j,r*M+c);
					link(gt,r*M+c,i*M+j);
				}
			}
	memset(vst,false,N*M);
	for(i=0; i<N*M; i++)
		if(!vst[i]) dfs(i);
	memset(vst,false,N*M);
	for(i=N*M-1, sccID=0; i>=0; i--)
		if(!vst[order[i]])
		{
			dfst(order[i]);
			sccID++;
		}
	for(i=0; i<N*M; i++)
		for(p=g[i]; p; p=p->next)
			if(scc_id[i]!=scc_id[p->to])
			{
				out_degree[scc_id[i]]++;
				in_degree[scc_id[p->to]]++;
			}
	if(sccID==1)
	{
		printf("0\n");
		return ;
	}
	int a, b;
	for(i=a=b=0; i<sccID; i++)
	{
		if(in_degree[i]==0) a++;
		if(out_degree[i]==0) b++;
	}
	printf("%d\n",a>b ? a: b);
}

int main()
{
    freopen("add.in", "r", stdin);
    freopen("add.out", "w", stdout);
    int T;
    scanf("%d", &T);
    assert(1 <= T && T <= 10);
    while (T--) {
	   input();
	   solve();
    }
    //while (true);
	return 0;
}
