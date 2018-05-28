#include<stdio.h>

int i,j,n,m;

int main(){
	freopen("nim.in", "r", stdin);
	freopen("nim.out", "w", stdout);
  bool ans;
  while(scanf("%d",&n)!=EOF){
    ans=0;
    while(n--){
      scanf("%d",&m);
      if(m%4)ans=1;
    }
    if(ans)printf("yes\n");
    else printf("no\n");
  }
  return 0;
}
