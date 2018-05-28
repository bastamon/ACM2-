#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
using namespace std;

//容许的误差范围
const double eps=1e-6;

//n为输入的数的个数
//m满足2^m=n
int n, m;

//a用来存储输入的数
//s用于存储在枚举过程中确定的值
//r用于存储s排序之后的值，方便比较
double a[100], s[100], r[100];

bool cmp(double a, double b)
{
    return a>b;
}

//读入并作初步判断
bool prepare()
{
    int i;
    double sum = 0.0;
    for(i=0; i<n; i++) {
		scanf("%lf", &a[i]);
		sum += a[i];
	}

	//检验和是否为1
	if(fabs(sum - 1.0) > eps) {
		return false;
	}

	//从大到小排序
    sort(a, a+n, cmp);
	//把0去掉
    while(n>0 && fabs(a[n-1])<eps) n--;
    m=0;
    while((1<<m)<n) m++;
	//检查0的个数是否正确
	return (1<<m)==n;
}


//检查枚举出来的对应关系是否是
//一个分解
bool check()
{
    int i, j;
	//求出组合2^(k-1)~2^k-1的值
    for(j=1; j<=(1<<(m-1)); j++) s[(1<<m)-1-j]=s[(1<<m)-1]*s[0]/s[j];

	//比较枚举出来的值是否和输入的值一致
    for(i=0; i<n; i++) r[i]=s[i];
    sort(r, r+n, cmp);
    for(i=0; i<n; i++)
        if(fabs(r[i]-a[i])>eps) return false;
        
    return true;
}


//回溯法枚举m-1个对应关系
bool backtrace(int k)
{
    int i, j;
    
    if(k==m) return check();
    
	//枚举组合2^k-1对应的数
    for(i=1; i<n-1; i++){
        s[(1<<k)-1]=a[i];
		//求出组合2^(k-1)~2^k-1对应的值
        for(j=1; j<=(1<<(k-1)); j++) s[(1<<k)-1-j]=s[(1<<k)-1]*s[0]/s[j];
		//找到解则直接返回
        if(backtrace(k+1)) return true;
    }
    
    return false;
}

int main()
{
		freopen("quantum.in", "r", stdin);
		freopen("quantum.out", "w", stdout);
    int cas;
    scanf("%d", &cas);
    while(cas--){
        scanf("%d", &n);
        if(!prepare()){
            printf("NO\n");
            continue;
        }
        //组合0对应最小的数
        s[0]=a[n-1];
		//组合2^m-1对应最大的数
        s[n-1]=a[0];

        if(backtrace(1)) printf("YES\n");
        else printf("NO\n");
        
    }
    
    return 0;
}
