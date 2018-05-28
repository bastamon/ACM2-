#include <cstdio>
#include <cstring>

const int maxn = 1000010;
const int u = 1000000;

// Same as Segment tree, but query on [1..maxn)
int tree[maxn];
void init () { memset( tree, 0, sizeof( tree )); };
void insert (int p, int v)
{
	while(p < maxn) {
		tree[p] += v; 
		p += p & (-p);
	}
}
int count (int p)
{
	int res = 0;
	while(p) {
		res += tree[p];
		p -= p & (-p);
	} 
	return res;
}

int main(){
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	int T;
	int n, x, y, maxi;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		maxi = 0;
		init();
		while(n--){
			scanf("%d", &x);
			y = count(u) - count(x);
			if (y > maxi) maxi = y;
			insert(x, 1);
		}
		printf("%d\n", maxi + 1);
	}
	return 0;
}
			
	
