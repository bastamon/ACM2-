#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

const int maxProject = 100;
const int maxEngineer = 30;
const int maxWeek = 50;
int w[maxEngineer][maxWeek], pw[maxProject][maxWeek], app[maxProject];
int N, M, W, C;

int wrong() {
	puts("no");
	return 0;
}

int main(int argc, char* argv[]) {
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "r");
	//FILE *std = fopen(argv[3], "r");
	
	int i, j, k, cot, st, ed, cas, p;
	
	fscanf(in, "%d", &cas);
	while (cas--){
       memset(pw, 0, sizeof(pw));
       memset(w, 0, sizeof(w));
       fscanf(in, "%d%d%d", &N, &M, &C);
       W = 0;
	   for (i=0;i<N;i++){
           fscanf(in, "%d%d", &st, &ed);
	       for (j=st;j<=ed;j++) fscanf(in, "%d", &pw[i][j]);
	       if (ed > W) W = ed;
       }
       
       memset(app, 0, sizeof(app));
       for (i=0;i<M;i++){
           if (fscanf(out, "%d", &cot)!=1) return wrong();
           if (cot<0 || cot >N) return wrong();
           for (j=0;j<cot;j++){
               if (fscanf(out, "%d", &p)!=1) return wrong();
               if (p<0 || p>=N || app[p]) return wrong();
               app[p]++;
               for (k=0;k<=W;k++){
                  w[i][k] += pw[p][k];
                  if (w[i][k]<0 || w[i][k] > C) return wrong();
               }
           }
       }
       for (i=0;i<N;i++)
           if (app[i] != 1) return wrong();
    }
	
    puts("yes");
    return 0;
}
