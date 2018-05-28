#include <stdio.h>
#include <string.h>

const int mod = 10007;
const int maxn = 100 + 1;
int N, M, H;
int Xmin, Ymin, Xmax, Ymax;
int SX, SY, EX, EY;
int n;
int A[maxn][maxn];
int B[maxn][maxn];
int Trans[maxn][maxn];
int matrixTmp_m[maxn][maxn];
int matrixTmp_p[maxn][maxn];

void input()
{
	scanf("%d%d%d", &N, &M, &H);
	scanf("%d%d%d%d", &Xmin, &Ymin, &Xmax, &Ymax);
	scanf("%d%d%d%d", &SX, &SY, &EX, &EY);
}

bool inside(int x, int y)
{
	return (x >= 0 && x <= Xmax && y >= 0 && y <= Ymax);
}

int getIndex(int x, int y)
{
	return (x) * (Ymax + 1) + (y);
}

void unitMatrix(int n, int a[][maxn])
{
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			a[i][j] = 0;
		}
		a[i][i] = 1;
	}
}

void multiMatrix(int n, int a[][maxn], int b[][maxn], int ret[][maxn])
{
	int i, j, k;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			matrixTmp_m[i][j] = 0;
			for(k = 0; k < n; k++){
				matrixTmp_m[i][j] = (matrixTmp_m[i][j] + a[i][k] * b[k][j]) % mod;
			}
		}
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			ret[i][j] = matrixTmp_m[i][j];
		}
	}
}

void powMatrix(int n, int a[][maxn], int p, int ret[][maxn])
{
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			matrixTmp_p[i][j] = a[i][j];
		}
	}
	unitMatrix(n, ret);
	while(p > 0){
		if(p&1){
			multiMatrix(n, ret, matrixTmp_p, ret);
		}
		multiMatrix(n, matrixTmp_p, matrixTmp_p, matrixTmp_p);
		p >>= 1;
	}
}

void initMatrix()
{
	int dx[4] = {0, 0, 1, -1};
	int dy[4] = {1, -1, 0, 0};
	int i, j, k;
	
	memset(A, 0, sizeof(A));
	for(i = 0; i <= Xmax; i++){
		for(j = 0; j <= Ymax; j++) //if (getIndex(i, j) != getIndex(EX, EY))
		{
			for(k = 0; k < 4; k++){
				if(inside(i + dx[k], j + dy[k]) == true){
					if (getIndex(i + dx[k], j + dy[k]) == getIndex(EX, EY)) continue;
					A[getIndex(i, j)][getIndex(i + dx[k], j + dy[k])] = 1;
				}
			}
		}
	}
	A[n - 1][n - 1] = 1;
	
	unitMatrix(n, B);
	B[n - 1][getIndex(EX, EY)] = 1;
	B[getIndex(EX, EY)][getIndex(EX, EY)] = 0;
	
	powMatrix(n, A, N - M, Trans);
	multiMatrix(n, Trans, B, Trans);
	powMatrix(n, A, M, A);
	multiMatrix(n, Trans, A, Trans);
}

int solve()
{
	SX -= Xmin;
	EX -= Xmin;
	Xmax -= Xmin;
	Xmin = 0;
	SY -= Ymin;
	EY -= Ymin;
	Ymax -= Ymin;
	Ymin = 0;
	n = (Xmax + 1) * (Ymax + 1) + 1;
	
	int count;
	if(H % N >= M) count = H / N + 1;
	else count = H / N;
	
	initMatrix();
	powMatrix(n, Trans, count, A);
	return A[n - 1][getIndex(SX, SY)];
}

int main()
{
	freopen("adship.in","r",stdin);
	freopen("adship.out","w",stdout);
	int T;
	scanf("%d", &T);
	while(T--){
		input();
		printf("%d\n", solve());
	}
	return 0;
}
