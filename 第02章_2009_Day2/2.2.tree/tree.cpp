#include <stdio.h>
#include <cassert>
#include <string.h>
#include <vector>
using namespace std;
const int MAXN = 111111;
vector <int> adj[MAXN];
vector <int> hardpath[MAXN];
struct Ttree {
	int l, r, lch, rch, par;
	double sum, mul;
}tree[400000];
struct Tedge {
	int a, b, c;
} edge[MAXN];
char mark[MAXN];
int totp, mem;
int par[MAXN], eid[MAXN], size[MAXN], hpc[MAXN], root[MAXN];
int pid[MAXN], pos[MAXN];
int tp1, tp2, st1[MAXN], st2[MAXN];

void dfs(int x, int p) {
	int i, t;
	par[x] = p, size[x] = 1, mark[x] = 1;
	for (i = 0; i < adj[x].size(); i++)	{
		t = adj[x][i];
		if (mark[t]) continue;
		dfs (t, x);
		size[x] += size[t];
	}
}

void makehardpath(int x, int id) {
	int i, t, now = 0;
	for (i = 0; i < adj[x].size(); i++) {
		t = adj[x][i];
		if (par[x] == t) continue;
		if (size[t] > now) now = size[t], hpc[x] = t;
	}
	if (hpc[x])	{		
		pos[hpc[x]] = hardpath[id].size();
		pid[hpc[x]] = id;
		hardpath[id].push_back(hpc[x]);
		makehardpath (hpc[x], id);
	}
	for (i = 0; i < adj[x].size(); i++)	{
		t = adj[x][i];
		if (par[x] == t || hpc[x] == t) continue;
		totp++;
		hardpath[totp].clear();
		pos[t] = 0, pid[t] = totp;
		hardpath[totp].push_back(t);
		makehardpath (t, totp);
	}
}

void buildtree(int l, int r, int id, int p, int hpid) {
	int m = (l+r)/2;
	tree[id].l = l, tree[id].r = r, tree[id].par = p, tree[id].sum = 0;
	if (l == r)	{
		tree[id].lch = tree[id].rch = 0;
		tree[id].sum = edge[eid[hardpath[hpid][l]]].c;
		tree[id].mul = 1;
		return;
	}
	tree[id].lch = mem + 1;
	buildtree (l, m, ++mem, id, hpid);
	tree[id].rch = mem + 1;
	buildtree (m + 1, r, ++mem, id, hpid);
	tree[id].sum = tree[tree[id].lch].sum + tree[tree[id].rch].sum;
	tree[id].mul = 1;
}

double sumtree(int l, int r, int id) {
	int m = (tree[id].l + tree[id].r) / 2;
	double ret = 0;
	if (!id || l > r || r < tree[id].l || l > tree[id].r) return ret;
	if (l <= tree[id].l && r >= tree[id].r)
		return tree[id].sum * tree[id].mul;	
	if (l <= m) {
		ret += sumtree (l, r, tree[id].lch);
	}
	if (r > m) {
		ret += sumtree (l, r, tree[id].rch);
	}
	return ret * tree[id].mul;
}

double sum(int a, int b) {
	int i, j, nowp;
	double ret = 0;
	if (pid[a] == pid[b])
		return sumtree ((pos[a]<pos[b]?pos[a]:pos[b]) + 1,
						pos[a]>pos[b]?pos[a]:pos[b], root[pid[a]]);
	for (tp1 = 0, nowp = pid[a]; nowp != 1;
		 st1[++tp1] = nowp, nowp = pid[par[hardpath[nowp][0]]]);
	for (tp2 = 0, nowp = pid[b]; nowp != 1;
		 st2[++tp2] = nowp, nowp = pid[par[hardpath[nowp][0]]]);
	st1[++tp1] = 1, st2[++tp2] = 1;
	for (; tp1 > 1 && tp2 > 1 && st1[tp1-1] == st2[tp2-1]; tp1 --, tp2 --);
	if (tp1 > 1) {
		if (pos[a]) ret += sumtree (1, pos[a], root[pid[a]]);
		for (i = 2; i < tp1; i++) {
			ret += edge[eid[hardpath[st1[i-1]][0]]].c;
			if (pos[par[hardpath[st1[i-1]][0]]])
				ret += sumtree(1, pos[par[hardpath[st1[i-1]][0]]],
							   root[st1[i]]);
		}
		a = hardpath[st1[tp1-1]][0];
		ret += edge[eid[a]].c;
		a = par[a];
	}
	if (tp2 > 1) {
		if (pos[b]) ret += sumtree (1, pos[b], root[pid[b]]);
		for (j = 2; j < tp2; j++) {
			ret += edge[eid[hardpath[st2[j-1]][0]]].c;
			if (pos[par[hardpath[st2[j-1]][0]]])
				ret += sumtree(1, pos[par[hardpath[st2[j-1]][0]]],
							   root[st2[j]]);
		}	
		b = hardpath[st2[tp2-1]][0];
		ret += edge[eid[b]].c;
		b = par[b];
	}
	if (pos[a] != pos[b]) {
		ret += sumtree ((pos[a]<pos[b]?pos[a]:pos[b]) + 1,
						pos[a]>pos[b]?pos[a]:pos[b], root[st1[tp1]]);
	}
	return ret;
}

void multiplytree(int l, int r, int id, int mul) {
	int m = (tree[id].l+tree[id].r)/2;
	if (!id || l > r || r < tree[id].l || l > tree[id].r) return;
	if (l <= tree[id].l && r >= tree[id].r)	{
		tree[id].mul *= mul;
		return;
	}
	if (l <= m) multiplytree (l, r, tree[id].lch, mul);
	if (r > m) multiplytree (l, r, tree[id].rch, mul);
	tree[id].sum = tree[tree[id].lch].sum * tree[tree[id].lch].mul +
				   tree[tree[id].rch].sum * tree[tree[id].rch].mul;
}

void multiply(int a, int b, int mul) {
	int i, j, nowp;
	if (pid[a] == pid[b]) {
		multiplytree ((pos[a]<pos[b]?pos[a]:pos[b]) + 1,
					  pos[a]>pos[b]?pos[a]:pos[b], root[pid[a]], mul);
		return;
	}
	for (tp1 = 0, nowp = pid[a]; nowp != 1;
		 st1[++tp1] = nowp, nowp = pid[par[hardpath[nowp][0]]]);
	for (tp2 = 0, nowp = pid[b]; nowp != 1;
		 st2[++tp2] = nowp, nowp = pid[par[hardpath[nowp][0]]]);
	st1[++tp1] = 1, st2[++tp2] = 1;
	for (; tp1 > 1 && tp2 > 1 && st1[tp1-1] == st2[tp2-1]; tp1 --, tp2 --);
	if (tp1 > 1) {
		if (pos[a]) multiplytree (1, pos[a], root[pid[a]], mul);
		for (i = 2; i < tp1; i++) {
			edge[eid[hardpath[st1[i-1]][0]]].c *= mul;
			if (pos[par[hardpath[st1[i-1]][0]]])
				multiplytree(1, pos[par[hardpath[st1[i-1]][0]]],
							 root[st1[i]], mul);
		}
		a = hardpath[st1[tp1-1]][0];
		edge[eid[a]].c *= mul;
		a = par[a];
	}
	if (tp2 > 1) {
		if (pos[b]) multiplytree (1, pos[b], root[pid[b]], mul);
		for (j = 2; j < tp2; j++) {
			edge[eid[hardpath[st2[j-1]][0]]].c *= mul;
			if (pos[par[hardpath[st2[j-1]][0]]])
				multiplytree(1, pos[par[hardpath[st2[j-1]][0]]],
							 root[st2[j]], mul);
		}	
		b = hardpath[st2[tp2-1]][0];
		edge[eid[b]].c *= mul;
		b = par[b];
	}
	if (pos[a] != pos[b])
		multiplytree ((pos[a]<pos[b]?pos[a]:pos[b]) + 1,
					  pos[a]>pos[b]?pos[a]:pos[b], root[st1[tp1]], mul);
}

void update (int x, double v) {
	int a = edge[x].a, b = edge[x].b, t, id, po;
	if (par[b] == a) t = a, a = b, b = t;
	if (pos[a] == 0) {
		edge[x].c = (int)(v + 1e-6);
	} else {		
		for (po = pos[a], id = root[pid[a]]; tree[id].l != tree[id].r;) {
			v = v / tree[id].mul;
			if (po <= (tree[id].l+tree[id].r)/2)
				id = tree[id].lch;
			else
				id = tree[id].rch;
		}
		tree[id].mul = 1, tree[id].sum = v;
		for (id = tree[id].par; id; id = tree[id].par) {		
			tree[id].sum = tree[tree[id].lch].sum * tree[tree[id].lch].mul +
						   tree[tree[id].rch].sum * tree[tree[id].rch].mul;			
		}
	}
}

int main() {	
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int n, i, tn, a, b;
	char s[11];
	for (assert(scanf ("%d", &tn) == 1 && tn >= 1 && tn <= 10); tn --;) {
		mem = totp = 0;
		memset (size, 0, sizeof(size));
		memset (mark, 0, sizeof(mark));
		memset (hpc, 0, sizeof(hpc));
		memset (par, 0, sizeof(par));
		memset (eid, 0, sizeof(eid));
		memset (pid, 0, sizeof(pid));
		memset (pos, 0, sizeof(pos));
		memset (root, 0, sizeof(root));
		assert(scanf ("%d", &n) == 1 && 1 <= n && n <= 50000);
		for (i = 1; i <= n; i++) adj[i].clear();
		for (i = 1; i < n; i++) {
			assert(scanf ("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].c) == 3);
			assert(edge[i].a >= 1 && edge[i].a <= n);
			assert(edge[i].b >= 1 && edge[i].b <= n && edge[i].a != edge[i].b);
			assert(edge[i].c >= 1 && edge[i].c <= 100);
			adj[edge[i].a].push_back(edge[i].b);
			adj[edge[i].b].push_back(edge[i].a);
		}
		dfs (1, 0);
		for (i = 1; i < n; i++)
			if (par[edge[i].a] == edge[i].b)
				eid[edge[i].a] = i;
			else
				eid[edge[i].b] = i;			
		totp = 1, hardpath[1].clear();
		hardpath[1].push_back(1), pid[1] = 1, pos[1] = 0;
		makehardpath (1, 1);
		for (i = 1; i <= totp; i++) {
			if (hardpath[i].size() > 1) {
				root[i] =++ mem;
				buildtree (1, hardpath[i].size()-1, root[i], 0, i);
			}
		}		
		while (assert(scanf ("%s", s) == 1), s[0] != 'E') {
			assert(scanf ("%d%d", &a, &b) == 2);
			if (s[0] == 'Q') {
				assert(1 <= a && a <= n && 1 <= b && b <= n && a != b);
				printf ("%.0lf\n", sum(a, b) + 1e-6);
			} else if (s[0] == 'C') {
				assert(1 <= a && a < n && 1 <= b && b <= 100);
				update (a, b);				
			} else {
				int c;
				assert(scanf("%d", &c) == 1 && -10 <= c && c <= 10 && c != 0);
				assert(1 <= a && a <= n && 1 <= b && b <= n && a != b);
				multiply(a, b, c);
			}
		}
	}
	assert(scanf("%*s") == EOF);
	return 0;
}
