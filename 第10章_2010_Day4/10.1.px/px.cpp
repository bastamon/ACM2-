#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<map>
using namespace std;
#define maxn 200
#define div 2011

int i,j,r,l,n,m,K;

long long int p[maxn][maxn][maxn];

map<long long int,int> buffer;

int gcd(int a,int b){
  if(a>b)return gcd(b,a);
  if(a==0)return b;
  return gcd(b%a,a);
}

//a<=m
int C(int n,int a){
  if(buffer.find((long long)(n)*maxn+a)!=buffer.end()){
    return buffer[(long long)(n)*maxn+a];
  }
  int q[maxn],i,j,dome,temp;
  for(i=1;i<=a;i++)q[i]=n-i+1;
  for(i=2;i<=a;i++){
    dome=i;
    for(j=1;j<=a&&dome>1;j++){
      temp=gcd(dome,q[j]);
      if(temp>1){
	dome/=temp;
	q[j]/=temp;
      }
    }
  }
  temp=1;
  for(i=1;i<=a;i++){
    temp*=q[i]%div;
    temp%=div;
  }
  buffer[(long long)(n)*maxn+a]=temp;
  return temp;
}


inline void make(){
  int ii,now;
  memset(p,0,sizeof(p));
  p[0][0][0]=1;
  for(ii=1;ii<=K;ii++){
    i=ii-1;
    if(i>n)break;
    for(j=0;j<=m;j++){
      now=(n-i)/K;
      if(i)now++;
      if(now==0&&j>0)break;
      now=C(now+j-1,j);
      for(l=0;l<K;l++)
	for(r=0;r<=m-j;r++)if(p[ii-1][l][r]){
	    p[ii][(l+i*j)%K][r+j]+=now*p[ii-1][l][r];
	    p[ii][(l+i*j)%K][r+j]%=div;
	}
    }
  }
  now=0;
  for(i=0;i<=m;i++){
    now+=p[ii-1][0][i];
    now%=div;
  }
  printf("%d\n",now);
  //  printf("%d\n",buffer.size());
}

int main(){
	freopen("px.in", "r", stdin);
	freopen("px.out", "w", stdout);
  int ii;
  scanf("%d",&ii);
  while(ii--){
    scanf("%d %d %d",&n,&m,&K);
    make();
  }
  return 0;
}
