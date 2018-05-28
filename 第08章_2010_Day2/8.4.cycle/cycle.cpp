#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
using namespace std;

#define maxn 50 
#define maxk 7 

int g[maxn][maxn + 1];
bool gg[maxn][maxn];
int n, k;

//f[i][state]; x(颜色k-1)到i,路径颜色为state且没有重复颜色的路径是否存在
int f[maxn][1 << (maxk - 1)];
int que[maxn * (1 << (maxk - 1))][2];
int color[maxn];

//O(m*2^(k-1))
bool find_cycle(int start) {
    f[start][0] = start;
    int head = 0, tail = 0;
    int state, end;
    int next_state, to;
    que[tail][0] = start;
    que[tail++][1] = 0;
    while (head < tail) {
        end = que[head][0]; 
        state = que[head++][1];
        for (int j = 1; j <= g[end][0]; ++j) {
            to = g[end][j];
            if (color[to] == k - 1) continue;
            next_state = state | (1 << color[to]);
            if (state != next_state && f[to][next_state] != start) {
                if (next_state == (1 << (k - 1)) - 1 && gg[to][start]) {
                    return true;
                }
                f[to][next_state] = start;
                que[tail][0] = to;
                que[tail++][1] = next_state;
            }
        }
    }
    return false;
}
//O(n*m*2^k)
bool check() {
    memset(f, -1, sizeof(f));
    for (int i = 0; i < n; ++i) {
        if (color[i] == k - 1 && find_cycle(i)) {
            return true;
        }
    }
    return false;
}

int main() {
	freopen("cycle.in", "r", stdin);
	freopen("cycle.out", "w", stdout);
    int start_time = clock();
    int t;
    scanf("%d", &t);
    while (t--) {
        int m;
        scanf("%d%d%d", &n, &m, &k);
        assert(0 < n && n <= 50 && 0 <= m && m <= 500 && 3 <= k && k <= 7);
        memset(gg, 0, sizeof(gg));
        for (int i = 0; i < n; ++i) {
            g[i][0] = 0;
        }
        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            assert(0 <= a && a < n && 0 <= b && b < n);
            g[a][++g[a][0]] = b;
            g[b][++g[b][0]] = a;
            gg[a][b] = gg[b][a] = true;
        }
        int total = 2 * (1 << k);
        int timer;
        bool ok = false;
        for (timer = 1; timer <= total; ++timer) {
            for (int i = 0; i < n; ++i) {
                color[i] = rand() % k;
            }
            if (check()) {
                ok = true;
                break;
            }
        }
        puts(ok ? "YES" : "NO");
//        fprintf(stderr, "iter: %d\n", timer);
    }
    fprintf(stderr, "%d\n", clock() - start_time);
    return 0;
}
