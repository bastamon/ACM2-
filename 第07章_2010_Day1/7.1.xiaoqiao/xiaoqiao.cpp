#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>

using namespace std;

const int COLOR = 3;
const int RANK = 13;

int cnt[COLOR][RANK];
int max_group[RANK];
char answer[1594324]; // 3 ^ 13 == 1594324

// a数组存储3进制数的每一位，get_slot把数组转化成数字
inline int get_slot(int a[]) {
	int slot = 0;
	for (int i = 0; i < RANK; ++i) {
		slot = slot * 3 + a[i];
	}
	return slot;
}

// 通过记忆化搜索判断每个状态是否可以分成满足第二个条件的组
bool presolve(int a[]) {
	int slot = get_slot(a);
	if (answer[slot] != -1) {
		return answer[slot];
	}

	answer[slot] = false;
	int x = 0;
	while (x < RANK && a[x] == 0) {
		++x;
	}

	if (x + 1 >= RANK || a[x + 1] == 0) {
		return false;
	}

	int b[RANK];
	memcpy(b, a, sizeof(b));
	--b[x];
	--b[x + 1];
	for (int i = 2; x + i < RANK; ++i) {
		if (b[x + i] > 0) {
			--b[x + i];
			if (presolve(b)) {
				answer[slot] = true;
				break;
			}
		}
	}

	return answer[slot];
}

// 枚举所有情况
void preprocess_dfs(int a[], int p) {
	if (p == RANK) {
		presolve(a);
		return;
	}
	for (int i = 0; i < 3; ++i) {
		a[p] = i;
		preprocess_dfs(a, p + 1);
	}
}

// 预处理所有可行解
void preprocess() {
	memset(answer, -1, sizeof(answer));
	int a[RANK];
	memset(a, 0, sizeof(a));
	answer[get_slot(a)] = true;
	preprocess_dfs(a, 0);
}

void input() {
	memset(cnt, 0, sizeof(cnt));

	int n;
	scanf("%d", &n);
	while (n--) {
		int color, rank;
		scanf("%d%d", &color, &rank);
		++cnt[color - 1][rank - 1];
	}
}

// 预处理对于每种rank，可以最多取多少对第一种情况的group
void pre_dfs() {
	for (int i = 0; i < RANK; ++i) {
		int min_value = cnt[0][i];
		for (int j = 1; j < COLOR; ++j) {
			min_value = min(min_value, cnt[j][i]);
		}
		max_group[i] = min_value;
	}
}

// 对于每种颜色，根据预处理出来的answer数组O(1)判断剩下的卡能否被分成第二种group
inline bool check() {
	for (int i = 0; i < COLOR; ++i) {
		if (!answer[get_slot(cnt[i])]) {
			return false;
		}
	}
	return true;
}

// 枚举满足第一种条件的组怎么取
bool dfs(int r) {
	if (r == RANK) {
		return check();
	}

	for (int i = 0; i <= max_group[r]; ++i) {
		for (int j = 0; j < COLOR; ++j) {
			cnt[j][r] -= i;
		}
		if (dfs(r + 1)) {
			return true;
		}
		for (int j = 0; j < COLOR; ++j) {
			cnt[j][r] += i;
		}
	}

	return false;
}

void solve() {
	pre_dfs();
	if (dfs(0)) {
		puts("Yes");
	} else {
		puts("No");
	}
}

int main() {
	freopen("xiaoqiao.in", "r", stdin);
	freopen("xiaoqiao.out", "w", stdout);
	preprocess();
	int T;
	scanf("%d", &T);
	while (T--) {
		input();
		solve();
	}

	return 0;
}

