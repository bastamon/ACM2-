#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define maxn 101000

int fa[maxn],sum[maxn];

int que[maxn][2],t;

int i,j,n,m;

int findfa(int a){
  if(a==fa[a])return a;
  fa[a]=findfa(fa[a]);
  return fa[a];
}

void merge(int a,int b){
  a=findfa(a);b=findfa(b);
  if(a==b)return;
  if(sum[a]>sum[b])swap(a,b);
  sum[b]+=sum[a];
  fa[a]=b;
}

long long int C(long long int a){
  a*=(a-1);
  a/=2;
  return a;
}

int main(){
	freopen("rp.in", "r", stdin);
	freopen("rp.out", "w", stdout);
  while(scanf("%d",&n)!=EOF){
    int a,b,c;
    for(i=1;i<=n;i++){
      sum[i]=1;
      fa[i]=i;
    }
    for(i=1;i<n;i++){
      scanf("%d %d %d",&a,&b,&c);
      if(c==0)merge(a,b);
      else {
	t++;
	que[t][0]=a;que[t][1]=b;
      }
    }
    long long nowmax=0,ans=0,temp;
    ans=C(n);
    for(i=1;i<=n;i++)if(findfa(i)==i){
	ans-=C(sum[i]);
      }
    while(t){
      temp=sum[findfa(que[t][0])];
      temp*=sum[findfa(que[t][1])];
      if(temp>nowmax)nowmax=temp;
      t--;
    }
    ans-=nowmax;
    printf("%lld\n",ans);
  }

  return 0;
}
