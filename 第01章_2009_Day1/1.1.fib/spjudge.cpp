#include <cstdio>
#include <cstring>
#define maxn 64

int f[maxn];
int x[maxn], y[maxn];
void init() {
    f[1] = f[2] = 1;
    for (int i = 3; i <= 50; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }
}

int wrong() {
    puts("no");
    return 0;
}

int main(int argc, char* argv[]) {
    init();
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "r");
    int t;
    fscanf(in, "%d", &t);
    for (int kase = 1; kase <= t; ++kase) {
        int n;
        fscanf(in, "%d", &n);
        int tt, length, width;
        int ret = fscanf(out, "Case %d: %d %d\n", &tt, &length, &width);
        if (ret != 3 || tt != kase) {
            return wrong();
        }
        if (!(length == f[n] && width == f[n + 1] || 
                width == f[n] && length == f[n + 1])) {
            return wrong();
        }
        for (int i = 1; i <= n; ++i) {
            ret = fscanf(out, "%d %d\n", &x[i], &y[i]);
            if (ret != 2) {
                return wrong();
            }
            if (x[i] < 0 || y[i] < 0 ||
                    x[i] + f[i] > length || y[i] + f[i] > width) {
                return wrong();
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (!(x[i] >= x[j] + f[j] || 
                            x[j] >= x[i] + f[i] ||
                            y[i] >= y[j] + f[j] ||
                            y[j] >= y[i] + f[i])) {
                    return wrong();
                }
            }
        }
    }
    fclose(out);
    fclose(in);
    puts("yes");
    return 0;
}
