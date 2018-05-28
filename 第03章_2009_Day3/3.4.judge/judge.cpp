#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

const int maxProject = 100;
const int maxEngineer = 30;
const int maxWeek = 50;

//w: 每个工程师每个星期的总工作量
//pw: 每个工程每个星期的工作量
//app: 每个工程被几个工程师负责
int w[maxEngineer][maxWeek], pw[maxProject][maxWeek], app[maxProject];
int N, M, W, C;

void wrong()
{
    puts("Infeasible");
}

void judge()
{
	int i, j, k, cot, st, ed, cas, p, ok = 1;
    scanf("%d%d%d", &N, &M, &C);
    W = 0;
    for (i=0;i<N;i++){
       scanf("%d%d", &st, &ed);
	   for (j=st;j<=ed;j++) scanf("%d", &pw[i][j]);
	   if (ed > W) W = ed;
    }
       
    memset(app, 0, sizeof(app));
    for (i=0;i<M;i++){
       if (scanf("%d", &cot)!=1) ok = 0;
       if (cot<0 || cot >N) ok = 0;
       for (j=0;j<cot;j++){
          if (scanf("%d", &p)!=1) ok = 0;
		  //工程编号范围不合法
		  //或者一个工程由不止一个工程师负责
          if (p<0 || p>=N || app[p]) ok = 0;
          app[p]++;

          for (k=0;k<=W;k++){
             w[i][k] += pw[p][k];
			 //工程师的工作量超负荷
             if (w[i][k]<0 || w[i][k] > C) ok = 0;
          }
       }
    }
    if (!ok) return wrong();
    for (i=0;i<N;i++)
       if (app[i] != 1) return wrong();
       
    puts("Feasible");
}

int main() {
	freopen("judge.in", "r", stdin);
	freopen("judge.out", "w", stdout);
	//cas为测试用例个数
	int cas;
	scanf("%d", &cas);
	while (cas--){
       memset(pw, 0, sizeof(pw));
       memset(w, 0, sizeof(w));
       judge();
    }
    return 0;

}
