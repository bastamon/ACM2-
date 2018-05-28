#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N = 1005;
const int INF = 1000000000;
int g[N][N];
int n;
int d[N];
int pnt[N];
char used[N];
struct Edge {
  int u, v, w;
  Edge(int uu = 0, int vv = 0, int ww = 0) : u(uu), v(vv), w(ww) {}
  bool operator <(const Edge &o) const {
    return w > o.w;
  }
}edge[N * N];
int adj[N][N];
int cnt[N];
int first[N], last[N];
char inmst[N][N];
int tim;
void input() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &g[i][j]);
    }
  }
}
void dfs(int u) {
  used[u] = 1;
  first[u] = tim++;
  for (int i = 0; i < cnt[u]; i++) {
    int v = adj[u][i];
    if (!used[v]) {
      dfs(v);
    }
  }
  last[u] = tim++;
}
inline int is_ance(int u, int v) {
  return first[u] <= first[v] && last[u] >= last[v];
}
void mst() {
  memset(used, 0, sizeof(used));
  memset(cnt, 0, sizeof(cnt));
  memset(inmst, 0, sizeof(inmst));
  for (int i = 0; i < n; i++) {
    d[i] = g[0][i];
    pnt[i] = 0;
  }
  d[0] = 0;
  pnt[0] = 0;
  int u = 0;
  for (int i = 0; i < n; i++) {
    if (u != pnt[u]) {
      inmst[u][pnt[u]] = inmst[pnt[u]][u] = 1;
      adj[pnt[u]][cnt[pnt[u]]++] = u;
    }
    used[u] = 1;
    int v = -1;
    for (int j = 0; j < n; j++) {
      if (!used[j]) {
        if (d[j] > g[u][j]) {
          d[j] = g[u][j];
          pnt[j] = u;
        }
        if (v == -1 || d[v] > d[j]) v = j;
      }
    }
    u = v;
  }
}
void preprocess() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (g[i][j] == -1) g[i][j] = INF;
    }
  }
}
int left;
int ans;
int curr_w;
void erase1(int st, int ed) {
  if (is_ance(st, ed)) return;
  if (inmst[st][pnt[st]]) {
    if (curr_w > g[st][pnt[st]]) ans++;
    inmst[st][pnt[st]] = inmst[pnt[st]][st] = 0;
    left--;
  }
  erase1(pnt[st], ed);
  pnt[st] = ed;
}
void solve() {
  preprocess();
  mst();
  tim = 0;
  memset(used, 0, sizeof(used));
  dfs(0);
  int m = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (!inmst[i][j] && g[i][j] != INF) {
        edge[m++] = Edge(i, j, g[i][j]);
      }
    }
  }
  sort(edge, edge + m);
  ans = 0;
  left = n - 1;
  for (int i = m - 1; i >= 0 && left; i--) {
    int u = edge[i].u;
    int v = edge[i].v;
    curr_w = edge[i].w;
    if (is_ance(u, v)) {
      erase1(v, u);
    } else if (is_ance(v, u)) {
      erase1(u, v);
    } else {
      int ed = u;
      while (!is_ance(ed, v)) {
        ed = pnt[ed];
      }
      erase1(u, ed);
      erase1(v, ed);
    }    
  }
  printf("%d\n", ans);
}
int main() {
  freopen("cadan.in", "r", stdin);
  freopen("cadan.out", "w", stdout);
  int T;
  scanf("%d", &T);
  while (T--) {
    input();
    solve();    
  }
  return 0;
}
