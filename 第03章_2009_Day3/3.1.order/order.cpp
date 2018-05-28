#include<stdio.h>
#include<algorithm>
#include<cstring>
using namespace std;

//由于对应的整数太大，需要64位整数来表示
typedef long long int64;

//a是输入的排列，同时存储输出的结果
int a[35], i, N, K;
//p用来存储可变进制数每一位的权值
int64 s, p[35];

//获取排列a对应的整数
int64 get_per(int *a)
{
    int i, j;
    int64 c, ret = 0;
    
	//计算可变进制数的值，这里是把排列倒过来
	//算，因此排最前的排列对应的数是N! - 1,
	//而排最后的排列对应的数是0
    for (i=N-2;i>=0;i--){
        c = 0;
        for (j=i;j<N;j++)
           if (a[j] > a[i]) c++;
        ret += c*p[N-i-1];
    }
    return ret;
}

//根椐一个整数key构造出对应的排列a
void set_per(int *a, int64 key)
{
    int i, h[30], j, k;
    memset(h, 0, sizeof(h)); 
    
    for (i=0;i<N;i++){
		//解出可变进制数的某一位
        for (k=0;key>=p[N-i-1];k++,key-=p[N-i-1]);
        for (j=N;j>0;j--){
            if (h[j] == 0) k--;
            if (k<0) break;
        }
        
        a[i] = j;
        h[j] = 1;
    }
}

int main()
{
	freopen("order.in", "r", stdin);
	freopen("order.out", "w", stdout);
	
	//预处理可变进制数每一位的权值
    p[0] = p[1] = 1;
    for (i=2;i<=20;i++){ 
        p[i] = i * p[i-1];
    }
    while (scanf("%d%d",&N, &K)&&N){
        for (i=0;i<N;i++) scanf("%d", &a[i]);
		//先把排列映射成整数
        s = get_per(a);
		//是否存在前K个排列
        if (s + K >= p[N]) printf("-1\n"); 
        else{
			//整数加K,即对应的排列往前倒推K
            s += K;
            set_per(a, s);
        }
        for (i=0;i<N;i++) 
            printf("%d%c",a[i],i==N-1?'\n':' ');
    }
    return 0;
}
