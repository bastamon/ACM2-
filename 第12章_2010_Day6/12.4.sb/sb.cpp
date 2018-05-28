#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int maxn = 10010;

double d[maxn];
int v[maxn], delta;
int task, n, D, x, y, s, t, h, ret;
int num[maxn];

bool calc( int t ){
    memset( num, 0, sizeof(num) );
    for (int i=0; i<n; i++){
        double dd = max( 0.0, d[i]-v[i]*t );
        int r = int( dd );
        if ( fabs(dd-r)>1e-5 )
            r++;
        if ( r%D==0 )
            r = r/D;else
            r = r/D+1;
        if ( r>n ) r = n+1;
        num[ r ]++;
    }
    int ret = 0;
    for (int i=0; i<=n; i++){
        ret += num[i];
        if ( !( ret>=i+1 ) ) break;
    }
    return ret==n;
}

int main(){
	freopen("sb.in", "r", stdin);
	freopen("sb.out", "w", stdout);
    for (scanf("%d", &task); task--; ){
        scanf("%d%d", &n, &D);
        t = 0; s = 0;
        for (int i=0; i<n; i++){
            scanf("%d%d%d", &x, &y, v+i);
            d[i] =sqrt( double((long long)x*(long long)x+(long long)y*(long long)y) );
            t = max( t, int(d[i]/v[i])+1 );
        }
        ret = t;
        while ( s<=t ){
            h = (s+t)>>1;
            if ( calc( h ) ){
                ret = h;
                t = h-1;
            }else s = h+1;
        }
        printf("%d\n", ret);
    }
    return 0;
}
