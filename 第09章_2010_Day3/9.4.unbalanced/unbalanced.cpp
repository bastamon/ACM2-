#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 100;

using namespace std;

int i, j, k, l, m, n;

int x[maxn], y[maxn];

long long  px[maxn * maxn], py[maxn * maxn];
int v[maxn * maxn];
/*
double det(const Point&a , const Point&b , const Point&c) {
  return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x) ;
}
*/

long long det(long long p1x, long long p1y, long long p2x, long long  p2y){
	return p1x * p2y - p1y * p2x;
}

int cmp(int p, int q){
	long long u = det(px[p], py[p], px[q], py[q]);
	return u < 0 || u == 0 && px[p] < px[q];
}

int main(){
	freopen("unbalanced.in", "r", stdin);
	freopen("unbalanced.out", "w", stdout);
	int tt;
	while(scanf("%d", &n) != EOF){
		for(i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
		k = 0;
		for(i = 0; i < n - 1; i++){
			for(j = i + 1; j < n; j++){
				if(y[i] < y[j] || y[i] == y[j] && x[i] > x[j]){
					px[k] = x[j] - x[i];
					py[k] = y[j] - y[i];
					k++;
				} else {
					px[k] = x[i] - x[j];
					py[k] = y[i] - y[j];
					k++;
				}
			}
		}
		for(i = 0; i < k; i++) v[i] = i;
		//printf("%d\n", k);
		sort(v, v + k, cmp);
		m = k;
		for(i = 0; i < k - 1; i++){
			if(det(px[v[i]], py[v[i]], px[v[i + 1]], py[v[i + 1]]) == 0) m--;
		}
		printf("%d\n", m * 2);
	}
	return 0;
}
		
		
