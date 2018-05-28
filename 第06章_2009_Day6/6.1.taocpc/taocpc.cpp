#include<stdio.h>
#include<string.h>
#define maxn 1100

int p[maxn],ans[maxn];

int q[maxn],qnum[maxn],ht;

int i,j,n,m;

int main(){
	freopen("taocpc.in", "r", stdin);
	freopen("taocpc.out", "w", stdout);
    int ii;
    scanf("%d",&ii);
    while(ii--){
	scanf("%d %d",&n,&m);
        memset(p,0,sizeof(p));
        memset(ans,0,sizeof(ans));
        memset(q,0,sizeof(q));
        memset(qnum,0,sizeof(qnum));
        ht=0;
	int temp;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			scanf("%d",&temp);
			if(temp==0)	p[j]++;else p[j]=0;
			temp=j;
			while(ht&&q[ht]>=p[j]){
				if(ans[q[ht]]<j-qnum[ht])ans[q[ht]]=j-qnum[ht];
				temp=qnum[ht];
				ht--;
			}
			ht++;
			q[ht]=p[j];
			qnum[ht]=temp;
		}
		p[j]=0;
		while(ht&&q[ht]>=p[j]){
				if(ans[q[ht]]<j-qnum[ht])ans[q[ht]]=j-qnum[ht];
				temp=qnum[ht];
				ht--;
		}
	}
	for(i=n-1;i;i--)if(ans[i+1]>ans[i])ans[i]=ans[i+1];
	scanf("%d",&j);
	while(j--){
		scanf("%d %d",&n,&m);
		printf("%c\n",ans[n]>=m?'Y':'N');
	}
    }
	return 0;
}
