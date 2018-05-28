#include<stdio.h>
#include<algorithm>

using namespace std;

#define maxn 1000

int p[maxn];

int i,j,n,m;

int main(){
	freopen("back.in", "r", stdin);
	freopen("back.out", "w", stdout);
    int ii;
    scanf("%d",&ii);
    while(ii--){
        scanf("%d",&n);
        for(i=1;i<=n;i++)scanf("%d",&p[i]);
        sort(&p[1],&p[1+n]);
        m=0;
        for(i=0,j=1;i<n&&j<=n;){
            if(p[j]>=i)m++,i++,j++;
            else j++;
        }
        printf("%d\n",m);
    }
    return 0;
}
