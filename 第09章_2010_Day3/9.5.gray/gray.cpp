#include <cstdio>
#include <cstring>

const int maxn = 100010;

int tree[maxn];
void init () { memset( tree, 0, sizeof( tree )); };
void insert ( int p, int v )
{
	while( p < maxn ) {
		tree[p]+=v; p+=p&(-p);
	}
}
int count ( int p )
{
	int res=0;
	while( p ) {
		res+=tree[p]; p-=p&(-p);
	} 
	return res;
}

int i, j, k, l, m, n, s;
int g[maxn];
int ans, maxf;

int get1(int n){
	if(count(1) == 1) return 1;
	int high, low, mid;
	int j;
	int s, t;
	low = 2;
	high = n;
	while(low <= high) {
		mid = (low + high) / 2;
		s = count(mid);
		t = count(mid - 1);
		if(t == 0 && s == 1){
			return mid;
		} else if (t > 0) high = mid - 1;
		else low = mid + 1;
	}
	return 0;
}
			
	

int main(){
	freopen("gray.in", "r", stdin);
	freopen("gray.out", "w", stdout);
	int tt;
	scanf("%d", &tt);
	while(tt--){
		scanf("%d%d", &n, &k);
	//	printf("%d %d, n, k\n", n, k);
		for(i = 1; i <= n; i++) scanf("%d", &g[n + 1 - i]);
		ans = 0;
		maxf = 0;
		j = 0;
		init();
		for(i = 1; i <= n; i++) {
			insert(i, g[i]);
			j += g[i];
		}
		//for(i = n; i >= 1; i--) printf("%d ", g[i]);printf("\n");
		ans += j;
		maxf = j;
		while(k--){
			if(j % 2 == 0) s = 1;
			else {
				s = get1(n);
				if(s == n && g[s] == 1){
					j = 0;
					g[s] = 0;
					insert(s, -1);
					//for(i = n; i >= 1; i--) printf("%d ", g[i]);printf("\n");
					continue;
				} else s = s + 1;
			}
			
			//printf("%d, k ,%d, s\n", k, s);
			//printf("%d, k ,%d, s\n", k, s);
			if(g[s] == 0){
				j++;
				insert(s, 1);
				g[s] = 1;
			} else {
				j--;
				insert(s, -1);
				g[s] = 0;
			}
	//		for(i = n; i >= 1; i--) printf("%d ", g[i]);printf("\n");
			if(j > maxf) maxf = j;
			ans += j;
		}
		printf("%d %d\n", ans, maxf);
	}
	return 0;
}
		
				
				
		
	
		
	
