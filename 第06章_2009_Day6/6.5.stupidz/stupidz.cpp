#include<stdio.h>
#include<string.h>

#define maxn 1010

int i,j,n,m,LA,LZ;


int p[maxn],q[maxn],sum[maxn];

int getSum(int a,int b){return sum[b]-sum[a-1];}

int mymin(int a,int b){return a<b?a:b;}

int main(){
	freopen("stupidz.in", "r", stdin);
	freopen("stupidz.out", "w", stdout);
	int ii;
		scanf("%d",&ii);
		while(ii--){
			scanf("%d %d %d",&n,&LA,&LZ);
				for(i=1;i<=n;i++){
					scanf("%d",&p[i]);
						sum[i]=p[i]+sum[i-1];
				}
			for(i=1;i<=n;i++){
				q[i+1]=0;
					for(j=i;j;j--){
						q[j]=mymin(q[j+1]+p[j],p[j]+getSum(j+1,i)-q[j+1]);
					}
				if(q[1]>LZ||getSum(1,i)-q[1]>LA){
					if(q[1]>LZ&&getSum(1,i)-q[1]>LA){
						while(1){
							p[i]--;
							sum[i]--;
								q[i+1]=0;
								for(j=i;j;j--){
									//sum[j]--;
									q[j]=mymin(q[j+1]+p[j],p[j]+getSum(j+1,i)-q[j+1]);
								}
							if(q[1]<=LZ||getSum(1,i)-q[1]<=LA)break;
						}
					}
					//                printf("%d %d\n",i,q[1]);
					if(q[1]<=LZ)printf("stupid zzzzzzyyy\n");
					else printf("poor zzzzzzyyy\n");
						break;
				}
			}
		}
	return 0;
}
