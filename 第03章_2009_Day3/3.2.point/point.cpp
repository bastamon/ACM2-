#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<map>
#include<cstring>
#include<iostream>
using namespace std;

//64位整数
typedef long long int64;

//KD树的结点结构
//t对应一棵KD树
struct node{ int x, y, x2, y2, c, ls, rs; }t[200009];
//二维点结构
//c表示在(x,y)这个位置上有多少个点重叠在一起
struct point{ int x, y, c; }p[50009];

//n表示点的数目
//cas存储test case数目
//xn,yn分别对应按x坐标和y坐标离散化
//之后有多少不同的坐标
int n, tn, cas, q, xn, yn;
int64 ans;
//xo,yo用于反查离散化之后的坐标
map<int, int>xo, yo;
//xa,ya表示离散化之后的坐标对应的原坐标
int xa[50009], ya[50009];

//分别按x和y来排序
bool cmpx(point a, point b){ return a.x<b.x; }
bool cmpy(point a, point b){ return a.y<b.y; }
//建立KD树
//dp表示深度
//nd是目前总共有多少结点
//st,ed表示当前结点对应的二维点在数组中的范围(起始位置，结束位置)
void buildTree(int dp, int nd, int st, int ed)
{
    int mid, i;
	//初始化当前结点，求出当前结点对应的矩形范围
    t[nd].c = p[st].c;
    t[nd].ls = t[nd].rs = -1;
    t[nd].x = t[nd].x2 = p[st].x;
    t[nd].y = t[nd].y2 = p[st].y;
    for (i=st+1;i<=ed;i++){
        t[nd].c += p[i].c;
        if (p[i].x < t[nd].x) t[nd].x = p[i].x;
        if (p[i].x > t[nd].x2) t[nd].x2 = p[i].x;
        if (p[i].y < t[nd].y) t[nd].y = p[i].y;
        if (p[i].y > t[nd].y2) t[nd].y2 = p[i].y;
    }
    if (st == ed) return ;
    
    if (dp & 1){ 
		//按y划分
        sort(p+st, p+ed+1, cmpy);

		//把当前区域按y坐标划分成两部分
        mid = (p[st].y + p[ed].y) / 2;
        for (i=st;i<=ed;i++)
            if (p[i].y > mid) break;
        if (st <= i-1){
           tn++;
           t[nd].ls = tn;
           buildTree(dp+1, tn, st, i-1);
        }
        if (i <= ed){
           tn++;
           t[nd].rs = tn;
           buildTree(dp+1, tn, i, ed);
        }
    }else{ 
		//按x划分
        sort(p+st, p+ed+1, cmpx);
		//把当前区域按x坐标划分成两部分
        mid = (p[st].x + p[ed].x) / 2;
        for (i=st;i<=ed;i++)
            if (p[i].x > mid) break;
        if (st <= i-1){
           tn++;
           t[nd].ls = tn;
           buildTree(dp+1, tn, st, i-1);
        }
        if (i <= ed){
           tn++;
           t[nd].rs = tn;
           buildTree(dp+1, tn, i, ed);
        }
    }
}

bool cmpxy(point a, point b){ if (a.x==b.x) return a.y<b.y;else return a.x<b.x; }
//预处理
void init()
{
    int i, j, nn = 0;
    //先按x坐标排序，再按y坐标排序
    sort(p, p+n, cmpxy);
    
	//把相同坐标的点合并
    i = 0;
    while (i<n){
        j = i + 1;
        while (j<n && p[j].x == p[i].x && p[j].y == p[i].y) j++;
        p[nn].x = p[i].x;
        p[nn].y = p[i].y;
        p[nn].c = j - i;
        i = j;
        nn++;
    }
    n = nn;
	
	//把x坐标离散化
    xn = 0; 
    sort(p, p+n, cmpx);
    xo.clear();
    for (i=0;i<n;i++){
       if (xo.find(p[i].x) == xo.end()){
           xa[xn] = p[i].x;
           xo[p[i].x] = xn++;
       }
       p[i].x = xo[p[i].x];
    }
    
	//把y坐标离散化
    yn = 0; 
    sort(p, p+n, cmpy);
    yo.clear();
    for (i=0;i<n;i++){
       if (yo.find(p[i].y) == yo.end()){
           ya[yn] = p[i].y;
           yo[p[i].y] = yn++;
       }
       p[i].y = yo[p[i].y];
    }
    tn = 0;

	//建立KD树
    buildTree(0, 0, 0, n-1);
}

//询问矩形(x,y)--(x2,y2)中包含的点的数目
//nd是当前结点的编号
int64 queryTree(int nd, int x, int y, int x2, int y2)
{
	
    if (t[nd].x >= x && t[nd].x2 <= x2 && t[nd].y >= y && t[nd].y2 <= y2){
		//假如结点被完全包含
        return t[nd].c;
    }
    if (t[nd].x > x2 || t[nd].x2 < x || t[nd].y > y2 || t[nd].y2 < y){
		//假如结点与询问完全没有交集
        return 0;
    }

    int64 tmp = 0;
	//相交但不完全包含
    if (t[nd].ls != -1) tmp += queryTree(t[nd].ls, x, y, x2, y2);
    if (t[nd].rs != -1) tmp += queryTree(t[nd].rs, x, y, x2, y2);
    return tmp;
}

//找到离散化坐标中比给定坐标大的最小的一个
//二分查找,a是存放坐标的数组，xa,ya中的一个
//val是给定的坐标值,len是数组长度
int findMinLarger(int *a, int val, int len)
{
    int low = 0, high = len - 1, mid;
    while (low < high){
        mid = (low + high) / 2;
        if (a[mid] > val && (mid==0 || a[mid-1] < val)) return mid;
        if (a[mid] > val) high = mid - 1; else low = mid+1;
    }
    low -= 5;if (low < 0) low = 0;
    high += 5; if (high > len-1) high = len-1;
    for (mid = low; mid <= high; mid++)
       if (a[mid] > val && ( mid==low || a[mid-1] < val)) return mid;
    //printf("Larger val = %d Not Found!\n", val);
    return -1;
}

//找到离散化坐标中比给定坐标小的最大的一个
int findMaxLess(int *a, int val, int len)
{
    int low = 0, high = len - 1, mid;
    while (low < high){
        mid = (low + high) / 2;
        if (a[mid] < val && (mid==len-1 || a[mid+1] > val)) return mid;
        if (a[mid] < val) low = mid+1; else high = mid-1;
    }
    low -= 5;if (low < 0) low = 0;
    high += 5; if (high > len-1) high = len-1;
    for (mid = low; mid <= high; mid++)
       if (a[mid] < val && ( mid==high || a[mid+1] > val)) return mid;
    //printf("Less val = %d Not Found!\n", val);
    return -1;
}

//处理询问
void work()
{
    int q, x, y, x2, y2;
    int64 ret;
    ans = 0;
    scanf("%d", &q);
    while (q--){
        scanf("%d%d%d%d", &x, &y, &x2, &y2);
		//先把询问替换成离散坐标
        if (xo.find(x) == xo.end()) x = findMinLarger(xa, x, xn); else x = xo[x] + 1;
        if (xo.find(x2) == xo.end()) x2 = findMaxLess(xa, x2, xn); else x2 = xo[x2] - 1;
        if (yo.find(y) == yo.end()) y = findMinLarger(ya, y, yn); else y = yo[y] + 1;
        if (yo.find(y2) == yo.end()) y2 = findMaxLess(ya, y2, yn); else y2 = yo[y2] - 1;

		//执行询问
        if (x == -1 || y == -1 || x2 == -1 || y2 == -1 || x > x2 || y > y2) ret = 0;
        else ret = queryTree(0, x, y, x2, y2);
        ans += ret;
    }
    cout<<ans<<endl;
}

int main()
{
	freopen("point.in", "r", stdin);
	freopen("point.out", "w", stdout);

	int i;
	scanf("%d", &cas);
	while (cas--){
		scanf("%d", &n);
		for (i=0;i<n;i++){
			scanf("%d%d", &p[i].x, &p[i].y);
			p[i].c = 1;
		}
		init();
		work();
	}
	return 0;
}
