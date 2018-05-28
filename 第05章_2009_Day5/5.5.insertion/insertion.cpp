#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cassert>

using namespace std;

const int BSIZE = 1024;

template <class T>
class List
{
private:
    struct Block
    {
        T a[BSIZE];
        int size;
        Block() : size(0)
        {
        }
    };

    Block* g[10000];

    int n, pNum;

    void getLocate(int ps, int& i, int& p)
    {
        int sum = 0;
        if (ps <= (n >> 1))
        {
            for (i = 0; i < pNum; ++i)
                if ((sum += g[i]->size) > ps)
                    break;
            p = ps - sum + g[i]->size;
        }
        else
        {
            ps = n - ps - 1;
            for (i = pNum - 1; i >= 0; --i)
                if ((sum += g[i]->size) > ps)
                    break;
            p = sum - ps - 1;
        }
    }

    // => [0, p] and [p + 1, size - 1].
    void split(int i, int p)
    {
        if (p < 0 || p + 1 == g[i]->size)
            return;
        memmove(g + i + 2, g + i + 1, (pNum - i - 1) * sizeof(Block *));
        g[i + 1] = new Block();
        pNum++;
        memcpy(g[i + 1]->a, g[i]->a + p + 1, (g[i]->size - p - 1) * sizeof(T));
        g[i + 1]->size = g[i]->size - p - 1;
        g[i]->size = p + 1;
    }

    void merge()
    {
        int i, j;
        for (i = 0; i < pNum; i = j)
            for (j = i + 1; j < pNum && g[i]->size + g[j]->size <= BSIZE; j++)
            {
                memcpy(g[i]->a + g[i]->size, g[j]->a, (g[j]->size) * sizeof(T));
                g[i]->size += g[j]->size;
                delete g[j];
                g[j] = NULL;
            }
        for (i = j = 0; i < pNum; i++)
            if (g[i])
                g[j++] = g[i];
        pNum = j;
    }

public:
    List() : n(0), pNum(1)
    {
        g[0] = new Block();
    }
    

    ~List()
    {
        for (int i = 0; i < pNum; i++)
            delete g[i];
    }
    
    void clear() {
        for (int i = 0; i < pNum; ++i) delete g[i];
        g[0] = new Block();
        n = 0;
        pNum = 1;
    }

    int size()
    {
        return n;
    }

    void append(const T& val)
    {
        if (g[pNum - 1]->size == BSIZE)
            g[pNum++] = new Block();
        g[pNum - 1]->a[g[pNum - 1]->size++] = val;
        n++;
    }

    // ps = 0...n - 1
    T& operator [](int ps)
    {
        int i, p;
        getLocate(ps, i, p);
        return g[i]->a[p];
    }

    // ps = 0...n
    void insert(int ps, const T& val)
    {
        if (ps == n)
        {
            append(val); return;
        }
        int i, p;
        getLocate(ps, i, p);
        // split if the block is full.
        if (g[i]->size == BSIZE)
        {
            split(i, BSIZE / 2 - 1);
            if (p >= BSIZE / 2)
            {
                p -= BSIZE / 2; i++;
            }
        }
        memmove(g[i]->a + p + 1, g[i]->a + p, (g[i]->size - p) * sizeof(T));
        g[i]->a[p] = val;
        g[i]->size++;
        n++;
    }

    void erase(int ps)
    {
        int i, p;
        getLocate(ps, i, p);
        memmove(g[i]->a + p, g[i]->a + p + 1, (g[i]->size - p - 1) * sizeof(T));
        if (--(g[i]->size) == 0)
        {
            delete g[i];
            memmove(g + i, g + i + 1, (pNum - i - 1) * sizeof(Block *));
            pNum--;
        }
        n--;
    }
};

int N, M;
List <int> lt;

void input() {
    int i, v;

    lt.clear();
    scanf("%d%d", &N, &M);
    assert(1 <= N && N <= 100000);
    assert(1 <= M && M <= 100000);
    for (i = 0; i < N; ++i) {
        scanf("%d", &v);
        lt.append(v);
    }
    //while (true);
}

void solve() {
    int i, j, P, V, size;
    for (i = 0; i < M; ++i) {
        scanf("%d%d", &P, &V);
        assert(0 <= P && P <= N - 1);
        lt.insert(P, V);
    }
   // while (true);
    size = lt.size();
    for (i = 0; i < size; ++i) {
        if (i) printf(" ");
        printf("%d", lt[i]);
    }
    printf("\n");
}

int main() {
	freopen("insertion.in", "r", stdin);
	freopen("insertion.out", "w", stdout);
    int T;
    scanf("%d", &T);
    assert(1 <= T && T <= 10);
    while (T--) {
        input();
        solve();
    }
    return 0;
}


