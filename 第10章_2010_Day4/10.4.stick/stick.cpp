#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;


#define maxn 1010000

int p[maxn][2];

int i,j,n,m,maxpoint,minpoint;

double f(double a){
    double ans=0;
    int i;
    for(i=1;i<=n;i++){
        if(a<=p[i][0]||a>=p[i][1]){
            if(p[i][1]-p[i][0]>ans)ans=p[i][1]-p[i][0];
        }else {
            if(p[i][1]-a>ans)ans=p[i][1]-a;
            if(a-p[i][0]>ans)ans=a-p[i][0];
        }

    }
    return ans;
}

inline void make(){
    double    low = minpoint, high = maxpoint;
    while (high - low > 1e-6) {
        double mid1 = (2 * low + high) / 3.;
        double mid2 = (low + 2 * high) / 3.;
        if (f(mid1) < f(mid2)) high = mid2;
        else low = mid1;
    }
    printf("%.2lf\n",f(low));

}

int main(){
	freopen("stick.in", "r", stdin);
	freopen("stick.out", "w", stdout);
    int ii;
    scanf("%d",&ii);
    while(ii--){
        scanf("%d",&n);
        maxpoint=0;
        for(i=1;i<=n;i++){
            scanf("%d %d",&p[i][0],&p[i][1]);
            if(p[i][1]-p[i][0]>maxpoint-minpoint)maxpoint=p[i][1],minpoint=p[i][0];
        }
        make();
    }
    return 0;
}
