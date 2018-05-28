#include<stdio.h>
#include<string.h>

const int N = 20;
const int DAY = 5;
const int PAT = 1 << DAY;

int n;
int love[N][PAT];
int req[DAY];
int memo[N][N/2+1][N/2+1][N/2+1][N/2+1][N/2+1];
int bit[PAT][DAY];
int changed[DAY];

void preprocess() {
  for (int i = 0; i < PAT; i++) {
    int k = i;
    for (int j = 0; j < DAY; j++) {
      bit[i][DAY - 1 - j] = k & 1;
      k >>= 1;
    }
  }
}
inline int getDec(int r0, int r1, int r2, int r3, int r4) {
  return (((((((r0 << 1) | r1) << 1) | r2) << 1) | r3) << 1) | r4;
}
void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < PAT; j++) {
      scanf("%d", &love[i][j]);
    }
  }
  for (int i = 0; i < DAY; i++) {
    scanf("%d", &req[i]);
  }
}
int dp(int p, int r0, int r1, int r2, int r3, int r4) {
  if (memo[p][r0][r1][r2][r3][r4] != -1) return memo[p][r0][r1][r2][r3][r4];
  if (p == 0) {
    return memo[p][r0][r1][r2][r3][r4] = love[0][getDec(changed[0] ^ r0,
        changed[1] ^ r1, changed[2] ^ r2, changed[3] ^ r3, changed[4] ^ r4)];
  }
  int ret = 0;
  for (int i = 0; i < PAT; i++) {
    int rr0 = r0 - (bit[i][0] ^ changed[0]);
    int rr1 = r1 - (bit[i][1] ^ changed[1]);
    int rr2 = r2 - (bit[i][2] ^ changed[2]);
    int rr3 = r3 - (bit[i][3] ^ changed[3]);
    int rr4 = r4 - (bit[i][4] ^ changed[4]);
    if (rr0 >= 0 && rr0 <= p && rr1 >= 0 && rr1 <= p
        && rr2 >= 0 && rr2 <= p && rr3 >= 0 && rr3 <= p
        && rr4 >= 0 && rr4 <= p) {
      int t = dp(p - 1, rr0, rr1, rr2, rr3, rr4) + love[p][i];
      if (t > ret) ret = t;
    }
  }
  return memo[p][r0][r1][r2][r3][r4] = ret;
}
void solve() {
  for (int i = 0; i < DAY; i++) {
    if (req[i] + req[i] > n) {
      req[i] = n - req[i];
      changed[i] = 1;
    } else {
      changed[i] = 0;
    }
  }
  memset(memo, -1, sizeof(memo));
  printf("%d\n", dp(n - 1, req[0], req[1], req[2], req[3], req[4]));
}
int main() {
  freopen("nurse.in", "r", stdin);
  freopen("nurse.out", "w", stdout);
  preprocess();
  int T;
  scanf("%d", &T);
  while (T--) {
    input();
    solve();
  }
  //while (1);
  return 0;
}
