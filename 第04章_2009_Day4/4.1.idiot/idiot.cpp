#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

const int MAXN = 100005;

struct Point {
  int x, y;
}p[2][MAXN], pp[2][MAXN];
int Q[MAXN], tail;
int n[2], nn[2];
int w, h;
FILE* fp;

void input() {
  for (int i = 0; i < 2; i++) {  
    scanf("%d", &n[i]);
    for (int j = 0; j < n[i]; j++) {
      scanf("%d,%d", &p[i][j].x, &p[i][j].y);
    }
  }
  scanf("%d%d", &w, &h);
  memcpy(pp, p, sizeof(pp));
  memcpy(nn, n, sizeof(nn));
}
void solve() {
  tail = -1;
  for (int i = 0; i < n[0]; i += 2) {
    while (tail >= 0 && p[0][i].y > p[0][Q[tail]].y) {
      int t = p[0][i].x - w;
      if (t < p[0][Q[tail]].x) {
        p[0][Q[tail]].x = t;
      }
      --tail;
    }
    Q[++tail] = i + 1;
  }
  int tmp = p[0][n[0] - 1].x - w;
  while (tail >= 0) {
    if (tmp < p[0][Q[tail]].x) {
      p[0][Q[tail]].x = tmp;
    }
    --tail;
  }  
  tail = -1;
  for (int i = n[0] - 1; i >= 1; i -= 2) {
    while (tail >= 0 && p[0][i].y > p[0][Q[tail]].y) {
      p[0][Q[tail]].x = max(pp[0][i].x, pp[0][Q[tail]].x - w);
      --tail;
    }
    Q[++tail] = i - 1;
  }
  while (tail >= 0) {
    p[0][Q[tail]].x = max(pp[0][0].x, pp[0][Q[tail]].x - w);
    --tail;
  }
  int nn = 0;
  for (int i = 0; i < n[0]; i += 2) {
    if (p[0][i].x <= p[0][i + 1].x) {
      p[0][nn++] = p[0][i];
      p[0][nn++] = p[0][i + 1];
    }
  }
  n[0] = nn;
    //for (int i = 0; i < n[0]; i++) printf("%d, %d\n", p[0][i].x, p[0][i].y);
    //puts("splitting line...........");
  if (nn == 0) {
    puts("impossible");
    return;
  }

  tail = -1;
  for (int i = 0; i < n[1]; i += 2) {
    while (tail >= 0 && p[1][i].y < p[1][Q[tail]].y) {
      int t = p[1][i].x - w;
      if (t < p[1][Q[tail]].x) {
        p[1][Q[tail]].x = t;
      }
      --tail;
    }
    Q[++tail] = i + 1;
  }
  tmp = p[1][n[1] - 1].x - w;
  while (tail >= 0) {
    if (tmp < p[1][Q[tail]].x) {
      p[1][Q[tail]].x = tmp;
    }
    --tail;
  }
  tail = -1;
  for (int i = n[1] - 1; i >= 1; i -= 2) {
    while (tail >= 0 && p[1][i].y < p[1][Q[tail]].y) {
      p[1][Q[tail]].x = max(pp[1][i].x, pp[1][Q[tail]].x - w);
      --tail;
    }
    Q[++tail] = i - 1;
  }
  while (tail >= 0) {
    p[1][Q[tail]].x = max(pp[1][0].x, pp[1][Q[tail]].x - w);
    --tail;
  }
  nn = 0;
  for (int i = 0; i < n[1]; i += 2) {
    if (p[1][i].x <= p[1][i + 1].x) {
      p[1][nn++] = p[1][i];
      p[1][nn++] = p[1][i + 1];
    }
  }
  n[1] = nn;
    //for (int i = 0; i < n[1]; i++) printf("%d, %d\n", p[1][i].x, p[1][i].y);
    //puts("splitting line...........");
  if (nn == 0) {
    puts("impossible");
    return;
  }

  for (int i = 0, j = 0;;) {    
    if (p[1][j].x <= p[0][i].x && p[0][i].x <= p[1][j + 1].x) {
      if (p[1][j].y - p[0][i].y >= h) {
        printf("%d,%d\n", p[0][i].x, p[0][i].y);
        return;
      }
    }
    
    if (p[0][i].x <= p[1][j].x && p[1][j].x <= p[0][i + 1].x) {
      if (p[1][j].y - p[0][i].y >= h) {
        printf("%d,%d\n", p[1][j].x, p[0][i].y);
        return;
      }
    }
    
    if (j == n[1] - 2 && i == n[0] - 2) break;
    else if (j == n[1] - 2) i += 2;
    else if (i == n[0] - 2) j += 2;
    else if (p[0][i + 1].x < p[1][j + 1].x) i += 2;
    else j += 2;
  }
  
  puts("impossible");
}
void visualize() {  
  fprintf(fp, "Graphics[{{Pink, Polygon[{");
  for (int i = 0; i < nn[0]; i++) {
    if (i > 0) fprintf(fp, ",");
    fprintf(fp, "{%d,%d}", pp[0][i].x, pp[0][i].y);
  }
  for (int i = nn[1] - 1; i >= 0; i--) {
    fprintf(fp, ",");
    fprintf(fp, "{%d,%d}", pp[1][i].x, pp[1][i].y);
  }
  fprintf(fp, "}]},");
  fprintf(fp, "{Green, Line[{");
  for (int i = 0; i < n[0]; i++) {
    if (i > 0) fprintf(fp, ",");
    fprintf(fp, "{%d,%d}", p[0][i].x, p[0][i].y);
  }
  fprintf(fp, "}]},");
  fprintf(fp, "{Blue, Line[{");
  for (int i = 0; i < n[1]; i++) {
    if (i > 0) fprintf(fp, ",");
    fprintf(fp, "{%d,%d}", p[1][i].x, p[1][i].y);
  }
  fprintf(fp, "}]}},Axes->True, AspectRatio->Automatic]\n");
}
int main() {
	freopen("idiot.in", "r", stdin);
	freopen("idiot.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--) {
		input();
		solve();
	}
	return 0;
}
