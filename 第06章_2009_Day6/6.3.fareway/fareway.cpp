#include<stdio.h>

double ans;


int i,j,n,m,A,B;

int main(){
	freopen("fareway.in", "r", stdin);
	freopen("fareway.out", "w", stdout);
    int ii;
    scanf("%d",&ii);
    while(ii--){
        scanf("%d %d %d",&n,&A,&B);
        ans=0;
        for(i=1;i<=n;i++){
            ans+=B*1.0/(n-i+2);
        }
        ans+=A;
        printf("%.2lf ",ans*10);

        ans=0;
        for(i=1;i<=n;i++){
            ans=(ans+B)/2;
        }
        ans+=A;
        printf("%.2lf ",ans*10);
        ans=0;
        for(i=1;i<=n;i++){
            ans=(ans+B)/3;
        }
        ans+=A;
        printf("%.2lf\n",ans*10);

    }
    return 0;
}
