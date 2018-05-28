#include<stdio.h>
#include<string.h>
#include<map>
#include<vector>
#define div 1000000007
using namespace std;
#define maxn 200

map<int,int> names;

//circle 
long long p[maxn];

//line
long long l[maxn];
 
long long C[maxn][maxn];
 
long long int per[maxn];
 
inline void prepareC(){
    C[0][0]=1;
    int i,j;
    for(i=1;i<maxn;i++){
        C[i][0]=1;
        for(j=1;j<=i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
            C[i][j]%=div;
        }
    }
    per[0]=per[1]=1;
    for(i=2;i<maxn;i++){
        per[i]=(per[i-1]*i)%div;
    }
}
 
inline void perpareP(){
    int i,j,r,now;
    long long int ans,temp;
    for(i=1;i<maxn;i++){
        now=0;
        p[i]=per[i];
        while(1){
            now+=2;
            if(now>i)break;
            temp=(C[i][now]*2)%div;
            for(j=1;j<=now/2;j++){
                temp*=C[i-j*2+2][2];
                temp%=div;
            }
            temp*=per[i-now];
            temp%=div;
            p[i]=(p[i]+temp);
            p[i]%=div;
        }
//        printf("%lld\n",p[i]);
    }
}
inline void perparel(){
    int i,j,r,now;
    long long int ans,temp;
    for(i=2;i<maxn;i++){
        now=1;

        while(1){
	  if(now>i)break;
            temp=(C[i][now])%div;
            for(j=1;j<=now/2;j++){
                temp*=C[i-j*2+1][2];
                temp%=div;
            }
            temp*=per[i-now];
            temp%=div;
            l[i]=(l[i]+temp);
            l[i]%=div;
	    now+=2;
        }
//        printf("%lld\n",p[i]);
    }
}
 
 
 
class TwoSidedCards {
public:
  int theCount(vector <int>, vector <int>);
};
 
int q[maxn];


 
int TwoSidedCards::theCount(vector <int> taro, vector <int> hanako) {
    int n=taro.size(),i,j,temp;
    for(i=0;i<n;i++){
        q[taro[i]]=hanako[i];
    }
    long long ans=1;
    int nowlen=0,left=n;
    for(i=0;i<n;i++)if(q[i]){
        j=i;nowlen=0;
        while(q[j]){
            nowlen++;
            temp=j;
            j=q[j];
            q[temp]=0;
        }
        ans*=C[left][nowlen];
        ans%=div;
        ans*=p[nowlen];
        ans%=div;
        left-=nowlen;
    }
    return ans;
}

int i,j,n,m;

int que[maxn][3],input[maxn][2];

bool checked[maxn];

inline void make(){
  memset(checked,0,sizeof(checked));
  int left=n,nowlen,r;
  long long int ans=1;
  for(i=0;i<m;i++)if(!checked[i]&&que[i][0]==1){
      j=i;
      nowlen=0;
      while(1){
	nowlen++;
	checked[j]=1;
	for(r=1;r<=que[j][0];r++)if(!checked[que[j][r]]){
	    j=que[j][r];
	    break;
	  }
	if(checked[j])break;
      }
      ans*=C[left][nowlen-1];
      ans%=div;
      ans*=l[nowlen];
      ans%=div;
      left-=nowlen-1;
  }
  for(i=0;i<m;i++)if(!checked[i]){
      j=i;
      nowlen=0;
      while(1){
	nowlen++;
	checked[j]=1;
	for(r=1;r<=que[j][0];r++)if(!checked[que[j][r]]){
	    j=que[j][r];
	    break;
	  }
	if(checked[j])break;
      }
      ans*=C[left][nowlen];
      ans%=div;
      ans*=p[nowlen];
      ans%=div;
      left-=nowlen;
  }
  printf("%lld\n",ans);
}

int main(){
	freopen("card.in", "r", stdin);
	freopen("card.out", "w", stdout);
  int ii;
  prepareC();
  perpareP();
  perparel();
  while(scanf("%d",&n)!=EOF){
    names.clear();
    m=0;
    for(j=0;j<2;j++){
      for(i=1;i<=n;i++){
	scanf("%d",&input[i][j]);
	if(names.find(input[i][j])==names.end()){
	  que[m][0]=0;
	  names[input[i][j]]=m++;  
	}      
      }
    }
    for(i=1;i<=n;i++){
      j=names[input[i][0]];
      que[j][0]++;
      que[j][que[j][0]]=names[input[i][1]];
      j=names[input[i][1]];
      que[j][0]++;
      que[j][que[j][0]]=names[input[i][0]];
    }
    make();
  }
  return 0;
}
