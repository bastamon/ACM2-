#include <cstdio>
#include <cstring>

const int maxn = 101;

// 节点编号1..nx, 1..ny, cx[], cy[]为对应匹配 
int nx, ny, m, g[maxn][maxn], sy[maxn], cx[maxn], cy[maxn];

int path(int u){
	for(int v = 1; v <= ny; v++) if(g[u][v] && !sy[v]){
		sy[v] = 1;
		if (!cy[v] || path(cy[v])){
			cx[u] = v;
			cy[v] = u;
			return 1;
		}
	} 
	return 0;
}

int match(){
	int i, ret = 0;
	memset(cx, 0, sizeof(cx)); 
	memset(cy, 0, sizeof(cy));
	for (i = 1; i <= nx; i++) if(!cx[i]){
		memset(sy, 0, sizeof(sy));
		ret += path(i); 
	}
	return ret;
}


int i, j, k, l, n;
int t;
int a[maxn][maxn];
int aa[maxn][maxn];
int r[maxn], rr[maxn];
int s[maxn], ss[maxn];
int b[maxn][maxn];
int next[maxn];

int main(){
	freopen("beautiful.in", "r", stdin);
	freopen("beautiful.out", "w", stdout);
	int tt;
	int f;
	scanf("%d", &tt);
	while(tt--){
		scanf("%d", &n);
		for(i = 1; i <= n; i++)scanf("%d", &r[i]);
		memset(s, 0, sizeof(s));
		memset(g, 0, sizeof(g));
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++){
				scanf("%d", &a[i][j]);
				s[a[i][j]]++;
				aa[i][j] = a[i][j];
			}
		for(i = 1; i <= n; i++){
			ss[i] = s[i];
			rr[i] = r[i];
			next[i] = i;
		}
		f = 0;
		for(i = 1; i <= n; i++) if(s[i] != n * r[i]){
			f = 1;
		}
		if (f){
			printf("-1\n");
			continue;
		}
		k=1;
		for(k = 1; k <= n; k++) if(rr[k] == 0){
			for (l = 1; l <= n; l++) if(rr[l] > 1){
				rr[k] = 1;
				rr[l]--;
				next[k] = l;
				break;
			}
			t = n;
			for(i = 1; i <= n; i++){
				for(j = 1; j <= n; j++) if(aa[i][j] == l){
					aa[i][j] = k;
					t--;
					if(!t) break;
				}
				if(!t)break;
			}
		}
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++)
				g[aa[i][j]][i]++;
		for(i = 1; i <= n; i++){
			nx = ny = n;
			m = match();
			if (m != n) {
				printf("god!\n");
				return 0;
			}
			for(j = 1; j <= n; j++){
				b[j][i] = next[cy[j]];
				g[cy[j]][j]--;
				if (g[cy[j]][j]<0) {
					printf("god 2!\n");
					return 0;
				}
			}
		}
		for(i = 1; i <= n; i++){
			for(j = 1; j < n; j++)printf("%d ", b[i][j]);
			printf("%d\n", b[i][n]);
		}
	}
	return 0;
}
				
		
		
			
		
		
		
		

