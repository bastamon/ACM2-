#include <stdio.h>
#include <stdlib.h>
#include <map>

const int maxn = 1000;
const int maxm = 12;

typedef std::map<std::pair<int, int>, int>::iterator Iter;
std::map<std::pair<int, int>, int> ans[maxn];
int tc, tt, n, m, ma, mi, x, y, bans;
char a[maxn][maxm];

int main ()
{
	freopen("teleportation.in", "r", stdin);
	freopen("teleportation.out", "w", stdout);
  scanf ("%d", &tc);
  for (int tt = 0; tt < tc; tt++)
  {
    scanf ("%d%d%d%d%d%d", &n, &m, &mi, &ma, &x, &y);
    for (int i = 0; i < n; i++)
    {
      scanf ("%s", a[i]);
      // printf ("%s\n", a[i]);
    }
    ans[0].clear ();
    std::pair<int, int> p = std::make_pair<int, int> (x, y);
    ans[0][p] = 0;
    for (int i = 1; i < n; i++)
    {
      ans[i].clear ();
      for (int j = 0; j < m; j++)
      {
        if (a[i][j] == '*')
        {
          for (int k = j + mi; k <= j + ma && k < m; k++)
          {
            //printf ("--%d: [%d, %d]\n", i, j, k);
            if (a[i][k] == '*')
            {
              p = std::make_pair<int, int> (j, k);
              for (Iter it = ans[i - 1].begin (); it != ans[i - 1].end (); ++it)
              {
                int c = it->second + abs (it->first.first - j) + abs (it->first.second - k);
                if (ans[i].find (p) == ans[i].end () || ans[i][p] > c)
                  ans[i][p] = c;
              }
              // printf ("%d: [%d, %d]:%d\n", i, j, k, ans[i][p]);
            }
          }
        }
      }
    }
    bans = -1;
    for (Iter it = ans[n - 1].begin (); it != ans[n - 1].end (); ++it)
    {
      if (bans == -1 || it->second < bans)
      {
        // printf ("[%d, %d]:%d\n", it->first.first, it->first.second, it->second);
        bans = it->second;
      }
    }
    printf ("%d\n", bans);
  }
  return bans >= 0;
}
