#include <cstdio>

const long long  MOD = 100000007;

void ext_gcd(long long a, long long b, long long &d, long long &x, long long &y)
{
		if(b == 0){ 
			d = a; 
			x = 1; 
			y = 0; 
			return ;
		};
         ext_gcd(b, a % b, d, y, x);
         y -= x * (a / b);
}

int i, j, k, l, m, n;
long long s, t, x, y, a, b, ii, jj, d;

int main(){
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	int tt;
	scanf("%d", &tt);
	while(tt--){
		scanf("%d%d", &n, &m);
		if(n < m){
			printf("0\n");
			continue;
		}
		// s/t % MOD
		s = t = 1;
		j = n + m;
		for(i = 1; i <= m; i++){
			ii = i;
			jj = j;
			t = t * ii % MOD;
			s = s * jj % MOD;
			j--;
		}
		jj = n + 1 - m;
		ii = n + 1;
		s = s * jj % MOD;
		t = t * ii % MOD;
		ext_gcd(t, MOD, d, x, y);
		a = s * x % MOD;
		if(a < 0) a += MOD;
		k = a;
		printf("%d\n", k);
	}
	return 0;
}
		
			
			
			
		
		
		
			
		
