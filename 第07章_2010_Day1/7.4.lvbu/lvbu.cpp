#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cstring>

using namespace std;

const int ROW = 6;
const int COL = 6;
const int MAX_STATE = 100000;
const int HASH_SIZE = 211117;

void input(char g[][COL]) {
	for (int r = 0; r < ROW; ++r) {
		char str[COL + 5];
		scanf("%s", str);
		for (int c = 0; c < COL; ++c) {
			g[r][c] = str[c];
		}
	}
}

struct State {
	char g[ROW][COL];
	int cost;
	State() {}
	State(char g_[ROW][COL], int cost_) : cost(cost_) {
		memcpy(g, g_, sizeof(g));
	}
	State& operator =(const State& other) {
		memcpy(g, other.g, sizeof(g));
		cost = other.cost;
		return *this;
	}
};

struct HashNode {
	char g[ROW][COL];
	HashNode *next;
};

State open[MAX_STATE];
HashNode hash_node[MAX_STATE];
HashNode* hash[HASH_SIZE];
int hash_node_num;
int head;
int tail;

inline void init() {
	head = tail = 0;
	memset(hash, 0, sizeof(hash));
	hash_node_num = 0;
}

inline void push(const State& state) {
	open[tail++] = state;
	//assert (tail <= MAX_STATE);
}

inline void pop(State& state) {
	state = open[head++];
}

inline bool equal(char g1[ROW][COL], char g2[ROW][COL]) {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			if (g1[i][j] != g2[i][j]) {
				return false;
			}
		}
	}
	return true;
}

inline void copy(char g1[ROW][COL], char g2[ROW][COL]) {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			g1[i][j] = g2[i][j];
		}
	}
}

inline int hash_code(char g[ROW][COL]) {
	int ret = 0;
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			ret = (ret * 127 + g[i][j]) % HASH_SIZE;
		}
	}
	return ret;
}

bool hash_it(char g[ROW][COL]) {
	int slot = hash_code(g);
	HashNode* ptr = hash[slot];
	while (ptr != NULL) {
		if (equal(ptr->g, g)) {
			return false;
		}
		ptr = ptr->next;
	}
	copy(hash_node[hash_node_num].g, g);
	hash_node[hash_node_num].next = hash[slot];
	hash[slot] = &hash_node[hash_node_num];
	++hash_node_num;

	//assert (hash_node_num <= MAX_STATE);

	return true;
}

inline bool empty() {
	return head == tail;
}

inline bool is_target(const State& state) {
	return state.g[2][5] == ']';
}

inline int get_cost(const State& state) {
	return state.cost;
}

void move(char g[ROW][COL], int i, int j, int k) {
	switch (g[i][j]) {
		case '<':
		case '[':
			g[i][j - k] = g[i][j];
			do {
				++j;
				g[i][j - k] = g[i][j];
			} while (g[i][j] == '-');
			for (int l = 0; l < k; ++l) {
				g[i][j - l] = '.';
			}
			break;
				
		case '>':
		case ']':
			g[i][j + k] = g[i][j];
			do {
				--j;
				g[i][j + k] = g[i][j];
			} while (g[i][j] == '-');
			for (int l = 0; l < k; ++l) {
				g[i][j + l] = '.';
			}
			break;

		case '^':
			g[i - k][j] = g[i][j];
			do {
				++i;
				g[i - k][j] = g[i][j];
			} while (g[i][j] == '|');
			for (int l = 0; l < k; ++l) {
				g[i - l][j] = '.';
			}
			break;

		case 'v':
			g[i + k][j] = g[i][j];
			do {
				--i;
				g[i + k][j] = g[i][j];
			} while (g[i][j] == '|');
			for (int l = 0; l < k; ++l) {
				g[i + l][j] = '.';
			}
			break;
	}
}

void unmove(char g[ROW][COL], int i, int j, int k) {
	switch (g[i][j]) {
		case '<':
		case '[':
			++j;
			while (g[i][j] == '-') {
				++j;
			}
			move(g, i, j, k);
			break;

		case '>':
		case ']':
			--j;
			while (g[i][j] == '-') {
				--j;
			}
			move(g, i, j, k);
			break;

		case '^':
			++i;
			while (g[i][j] == '|') {
				++i;
			}
			move(g, i, j, k);
			break;

		case 'v':
			--i;
			while (g[i][j] == '|') {
				--i;
			}
			move(g, i, j, k);
			break;
	}
}

void expand(State& curr) {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			switch (curr.g[i][j]) {
				case '<':
				case '[':
					for (int k = 1; j - k >= 0; ++k) {
						if (curr.g[i][j - k] == '.') {
							move(curr.g, i, j, k);
							if (hash_it(curr.g)) {
								push(State(curr.g, get_cost(curr) + 1));
							}
							unmove(curr.g, i, j - k, k);
						} else {
							break;
						}
					}
					break;

				case '>':
				case ']':
					for (int k = 1; j + k < COL; ++k) {
						if (curr.g[i][j + k] == '.') {
							move(curr.g, i, j, k);
							if (hash_it(curr.g)) {
								push(State(curr.g, get_cost(curr) + 1));
							}
							unmove(curr.g, i, j + k, k);
						} else {
							break;
						}
					}
					break;

				case '^':
					for (int k = 1; i - k >= 0; ++k) {
						if (curr.g[i - k][j] == '.') {
							move(curr.g, i, j, k);
							if (hash_it(curr.g)) {
								push(State(curr.g, get_cost(curr) + 1));
							}
							unmove(curr.g, i - k, j, k);
						} else {
							break;
						}
					}
					break;

				case 'v':
					for (int k = 1; i + k < ROW; ++k) {
						if (curr.g[i + k][j] == '.') {
							move(curr.g, i, j, k);
							if (hash_it(curr.g)) {
								push(State(curr.g, get_cost(curr) + 1));
							}
							unmove(curr.g, i + k, j, k);
						} else {
							break;
						}
					}
					break;
			}
		}
	}
}

void show(State& state) {
	printf("cost : %d\n", state.cost);
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			putchar(state.g[i][j]);
		}
		puts("");
	}
}

void solve(char g[][COL]) {
	init();
	State start(g, 0);
	push(start);
	hash_it(g);
	bool solved = false;
	while (!empty()) {
		State curr;
		pop(curr);
		if (is_target(curr)) {
			printf("%d\n", get_cost(curr));
			solved = true;
			break;
		}
		expand(curr);
	}
	if (!solved) {
		puts("NANI!");
	}
}

int main() {
	freopen("lvbu.in", "r", stdin);
	freopen("lvbu.out", "w", stdout);
	int T;
	scanf("%d", &T);

	while (T--) {
		char g[ROW][COL];
		input(g);
		solve(g);
	}

	return 0;
}

