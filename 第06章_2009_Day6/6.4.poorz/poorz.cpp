#include<stdio.h>

#define maxn 100

int p[maxn][maxn];

int la,lz,n,m,i,j;

int main(){
	freopen("poorz.in", "r", stdin);
	freopen("poorz.out", "w", stdout);
    int ii;
    scanf("%d",&ii);
    while(ii--){
        scanf("%d %d %d %d",&n,&m,&la,&lz);
        for(i=1;i<=n;i++)for(j=1;j<=m;j++)scanf("%d",&p[i][j]);
        if(lz>la){
            printf("yes\n");
            continue;
        }
        if(lz==la&&p[n][m]==0){
            printf("yes\n");
            continue;
        }
        printf("no\n");
    }
    return 0;
}
