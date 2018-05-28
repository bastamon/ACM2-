#include<stdio.h>
#include<math.h>

//N的最大值
const int MAXN = 1000000;
//prime[i]存储第i个质数
//cp表示目前质数数目
int prime[MAXN], cp;
//fg[i]标记i是否不是质数
//即为假表示i是质数
char fg[MAXN];
//phi[i]记录phi函数相应的值
int phi[MAXN];

//线性筛法
void preprocess() {
  phi[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (!fg[i]) {
	  //得到一个质数
      prime[cp++] = i;
      phi[i] = i - 1;
    }
    for (int j = 0; j < cp && (long long) prime[j] * i < MAXN; j++) {
      fg[prime[j] * i] = 1;
	  //应用phi函数的递推式
      if (i % prime[j] == 0) {
        phi[prime[j] * i] = phi[i] * prime[j];
        break;
      } else {
        phi[prime[j] * i] = phi[i] * (prime[j] - 1);
      }
    }
  }
}

//二分幂求模
//用二分法求a^p mod n
int exp_mod(int a, int p, int n) {
  int ret = 1;
  long long aa = a;
  while (p) {
    if (p & 1) {
      ret = ret * aa % n;
    }
    p >>= 1;
    aa = aa * aa % n;
  }
  return ret;
}
int main() {
  freopen("number.in", "r", stdin);
  freopen("number.out", "w", stdout);
  preprocess();
  int T;
  scanf("%d", &T);
  while (T--) {
    int a, n;
    scanf("%d%d", &a, &n);

	//枚举phi(n)的约数
    int nn = (int)sqrt(phi[n]);
    int ans = n;
    for (int i = 1; i <= nn; i++) {
      if (phi[n] % i == 0) {
		//检验i和phi(n)/i是否答案
        if (exp_mod(a, i, n) == 1) {
          if (ans > i) ans = i;
        }
        if (exp_mod(a, phi[n] / i, n) == 1) {
          if (ans > phi[n] / i) ans = phi[n] / i;
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
