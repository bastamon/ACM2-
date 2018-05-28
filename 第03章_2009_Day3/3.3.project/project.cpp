#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;

//标准程序可以处理的最大规模
#define maxProject 169        
#define maxEngineer 29
#define maxWorkingWeeks 59

//惩罚值
const int penalty = 50000;

//定义一个无穷大的值
const int INF = 0xFFFFFFF;
const int INTSIZE = sizeof(int);

//用来表示一个工程的结构体
struct Projects{
	//一个工程每个星期的工作量
   int workload[maxWorkingWeeks];
   //一个工程的起始星期，结束星期和所有星期的工作量总和
   int startingWeek, endingWeek, totWorkload;
}project[maxProject];

struct Engineer{
	//totWorkload用来表示工程师的分数值
	//workload表示工程师每个星期的总工作量
   int totWorkload, workload[maxWorkingWeeks];
   //asn表示工程师所负责的工程数目
   //asg表示工程师所负责的具体工程
   int asn, asg[maxProject];
}engineer[maxEngineer];

//工程数目
int projectCount;
//工程师数目
int engineerCount;
//数据中最多涉及的星期范围
int totalWorkingWeeks;
//阈值
int maxWorkload;


//读入数目
void readData()
{
    int i, j;
    scanf("%d%d%d", &projectCount, &engineerCount, &maxWorkload);
    assert(projectCount<=40&&engineerCount<=5);
    totalWorkingWeeks = 0;
    memset(project, 0, sizeof(project));
    for (i=0; i<projectCount; i++){
        scanf("%d%d", &project[i].startingWeek, &project[i].endingWeek);
		//求出数据中最多涉及的星期范围
        if (project[i].endingWeek > totalWorkingWeeks) totalWorkingWeeks = project[i].endingWeek;
		for (j=project[i].startingWeek; j<=project[i].endingWeek; j++){ 
		    scanf("%d", &project[i].workload[j]);
		    assert(project[i].workload[j]<=10&&project[i].workload[j]>0);
			//预计算某个工程的工作量总和
		    project[i].totWorkload += project[i].workload[j];
        }
    }
    totalWorkingWeeks++;
    assert(totalWorkingWeeks<=20);
}

//输出结果方案
void showResult()
{
 	 int i, j;
	 for (i=0;i<engineerCount;i++){
	     printf("%d", engineer[i].asn);
	     for (j=0;j<engineer[i].asn;j++)
		     printf(" %d", engineer[i].asg[j]);
         printf("\n");
     }
     printf("\n");
}

//把工程prj分配给工程师eng,
//并更新分数值
int assignProject(int eng, int prj)
{
    int i, tmp;
	//分数加上新加入的工程的工作总量
    engineer[eng].totWorkload += project[prj].totWorkload;
    engineer[eng].asg[ engineer[eng].asn++ ] = prj;
	for (i=project[prj].startingWeek; i<= project[prj].endingWeek; i++){
	    tmp = engineer[eng].workload[i];
	    engineer[eng].workload[i] += project[prj].workload[i];

		//调整超出阈值部分的分数
        if (engineer[eng].workload[i] > maxWorkload){
	        if (tmp > maxWorkload) tmp = project[prj].workload[i]; 
 	 	    else tmp = engineer[eng].workload[i] - maxWorkload;
		    engineer[eng].totWorkload += penalty * tmp;
	    }
    }

	//如果分数值大于penalty,则说明工程师超负荷工作
    return (engineer[eng].totWorkload < penalty);
}

//把工程prj从工程师eng负责的工程中去除
//并更新分数值
void removeProject(int eng, int prj)
{
    int i, tmp;
	//分数减去被移除的工程的工作总量
    engineer[eng].totWorkload -= project[prj].totWorkload;
    engineer[eng].asn--;
	for (i=project[prj].startingWeek; i<= project[prj].endingWeek; i++){
	    tmp = engineer[eng].workload[i];
	    engineer[eng].workload[i] -= project[prj].workload[i];

		//调整超出阈值部分的分数
	    if (tmp > maxWorkload){
  	        if (engineer[eng].workload[i] > maxWorkload) tmp = project[prj].workload[i];
  	        else tmp -= maxWorkload;
	        engineer[eng].totWorkload -= tmp * penalty;
	    }
    }
}

//重置某个工程师负责的工程
inline void clearProject(int eng)
{
 	engineer[eng].asn = engineer[eng].totWorkload = 0;
    memset(engineer[eng].workload, 0, INTSIZE*(totalWorkingWeeks + 1));
}
void init()
{
 	int i;
 	for (i=0; i<engineerCount; i++) clearProject(i);
}

//be1,be2,be3分别为要重新调整的三个工程师
//bsgp1,bsgp2记录前两个工程师负责工程的数目
//mxdp代表可以选用的工程的总数目
//dpCot记录回溯函数被调用的次数
//fbr: 如果等于2则说明回溯函数成功找到一个解
int be1, be2, be3, bsgp1,bsgp2, mxdp, dpCot, fbr;
//pod: 按起始星期排序的工程的编号
//bsg: 原来的三个工程师的分配方案
int pod[maxProject], bsg[maxProject];


bool cmpStartingWeek(int a, int b){ return project[a].startingWeek < project[b].startingWeek; }
//最大步数限制为3000
const int maxDPCot = 3000;

//用回溯法搜索三个工程师的分配方案
//d代表深度，即对应哪个工程
void dfsbb3(int d)
{
	//已经搜到结果或者超过步数限制则返回
 	if (fbr == 2 || dpCot > maxDPCot) return ;

	//每调用一次计数加一
    dpCot++;
	
	//已经处理完所有工程，说明搜索到一个
	//解了
 	if (d >= mxdp){
	   	fbr |= 2;
		return ;
    }

	//分别尝试把工程分配给3个工程师
    if (assignProject(be1, pod[d])){ 
	    dfsbb3(d+1);
		if (fbr == 2) return ;    
    }
    removeProject(be1, pod[d]);
	
    if (assignProject(be2, pod[d])){ 
		dfsbb3(d+1);
    	if (fbr == 2) return ;    
    }
    removeProject(be2, pod[d]);

    if (assignProject(be3, pod[d])){ 
		dfsbb3(d+1);
    	if (fbr == 2) return ;    
    }
    removeProject(be3, pod[d]);
}

//搜索三个工程师的新的分配方案
int branchAndBound3(int eg1, int eg2, int eg3)
{
 	int i, j, n, sum;

	//先把原来的分配方案保存起来
 	bsgp1 = engineer[eg1].asn;
 	bsgp2 = bsgp1 + engineer[eg2].asn;
	//这里的n代表要三个工程师负责的工程的数目
 	n = bsgp2 + engineer[eg3].asn;
 	for (i=0;i<bsgp1;i++) bsg[i] = engineer[eg1].asg[i];
 	for (i=bsgp1;i<bsgp2;i++) bsg[i] = engineer[eg2].asg[i-bsgp1];
 	for (i=bsgp2;i<n;i++) bsg[i] = engineer[eg3].asg[i-bsgp2];
 	
	//如果有某一星期要考虑的工程的工作量总和大于阈值的3倍
	//则由鸽巢原理得无论怎么调整总有一个工程师工作负荷超过阈值
	//于是不用搜索，直接返回
 	for (i=0;i<totalWorkingWeeks;i++){
		sum = 0;
		for (j=0;j<n;j++)
	    	if (i >= project[bsg[j]].startingWeek && i <= project[bsg[j]].endingWeek)
	            sum += project[bsg[j]].workload[i];
 	    if (sum > maxWorkload + maxWorkload + maxWorkload) 
            return -1;
	}
 	
	//按要考虑的工程按起始星期的顺序排序
	//从而使回溯过程按照时间顺序来搜索
 	for (i=0;i<n;i++) pod[i] = bsg[i];
 	sort(pod, pod+n, cmpStartingWeek);
 	be1 = eg1;	
	be2 = eg2;	
	be3 = eg3;
 	mxdp = n; 	
	dpCot = fbr = 0;

	//先把三个工程师的分配方案重置
 	clearProject(eg1); 	
	clearProject(eg2);  
	clearProject(eg3);

	//调用回溯函数进行具体搜索
	dfsbb3(0);
	
	if (fbr == 0){
		//调整失败，把方案还原
 		clearProject(eg1); 	
		clearProject(eg2);  
		clearProject(eg3);
 		for (i=0;i<bsgp1;i++) assignProject(eg1, bsg[i]);
 		for (i=bsgp1;i<bsgp2;i++) assignProject(eg2, bsg[i]); 
 		for (i=bsgp2;i<n;i++) assignProject(eg3, bsg[i]);
	}

	//找到一个使三个工程师不用超负荷工作的方案
 	return (fbr == 2);
}

bool cmpLoad(int a, int b){ return engineer[a].totWorkload > engineer[b].totWorkload; }
//产生一个随机的解并调整
//看看是否可以得出一个合要求的解
int getFeasibleAssignment()
{
	//rep为重复执行次数
	//suc为是否成功找到一个合法解的标记
    int i, j, k, mi, rep = 4, suc = 0, micost = INF;
	int cost, n, pt, ph, needop, res;
	//od存放工程随机洗牌之后的顺序
	//eod存放按分数排序的工程师的编号
    static int od[maxProject], eod[maxEngineer];
    //注意这里的n代表工程师数目
	n = engineerCount;
	//重复进行rep次
    while (!suc && rep--){
		suc = 1;  
		//把工程随机洗牌
		for (i=0;i<projectCount;i++) od[i] = i;
        random_shuffle(od, od+projectCount);
 	    for (i=0;i<n;i++) clearProject(i);

        //根据随机出来的顺序使用某种贪心的策略
        if (rep & 1){
			//第一次重复尝试采用first fit策略
			//即工程分配给第一个可以负责该工程而不会超负荷
			//的工程师，如果不存在这样的工程师则
			//分配给分数值最小的工程师
		    for (i=0;i<projectCount;i++){
				k = 0;
				mi = INF;
				for (j=0;j<engineerCount;j++)
					if ( assignProject(j, od[i]) ) break; else{ 
					    if (engineer[j].totWorkload < mi){
					        mi = engineer[j].totWorkload;
					    	k = j;
					    } 
						removeProject(j, od[i]); 
					}
				if (j >= engineerCount) {
			   	   suc = 0;
		           assignProject(k, od[i]);
      	        }
  		    }
		}else{ 
			//不是第一次重复则采用best fit策略
			//即分配给负责该工程的情况下分数值最小的
			//工程师
		    for (i=0;i<projectCount;i++){
                mi = INF;
                k = 0;
                for (j=0;j<engineerCount;j++){
                    assignProject(j, od[i]);
                    cost = engineer[j].totWorkload;
                    if (cost < mi){
                        mi = cost;
                        k = j;
                    }
                    removeProject(j, od[i]);
                }
                assignProject(k, od[i]);
                if (cost > penalty) suc = 0; 
            }
        }
		//如果贪心地放得到了一个符合要求的解，则直接返回
        if (suc) break;

		//neeop表示是否需要进行3-opt调整操作
		needop = 1;
        while (needop){
	        needop = 0;
	        ph = 0; pt = n-1;
	        for (i=0;i<n;i++) eod[i] = i;
			//按分数排序工程师
	        sort(eod, eod+n, cmpLoad);
			//如果已经是一个合条件的解,则返回
            if (engineer[eod[0]].totWorkload < penalty){ 
				suc = 1; 
				break; 
			}
			//按顺序处理超负荷工作的工程师
	        while (ph + 1 < pt && engineer[eod[ph]].totWorkload > penalty){
				//如果正在处理的超负荷工作工程师
				//与最后两个工程师进行调整无法达到目的
				//则和倒数第二第三个工程师一起进行调整
				//如果再不行再把右界向左移
	            while (ph + 1 < pt){
					int pjn = engineer[eod[pt]].asn + engineer[eod[pt-1]].asn + engineer[eod[ph]].asn;
			        res = branchAndBound3(eod[pt], eod[pt - 1], eod[ph]);
			        if (res == 1){ 
						//成功调整，进行下一次3-opt操作
				   		needop = 1; 
				   		break;
		            }
			        pt--;
		        }
		        if (needop)	break; 
				//如果到最后都不能成功调整，则尝试处理
				//下一个超负荷工作的工程师
                ph ++;
                pt = n-1;
		    }
		}
		if (suc) break; 
    }
    
    return suc;
}



void work(int repc)
{
	//重复多次随机--调整的过程
 	 while(repc--){
		 if (getFeasibleAssignment()){
		     showResult();
		     return ;
		 }
     }
}

int main(int argc, char** argv)
{
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
	int T;

	srand(9973);
	scanf("%d", &T);
	while (T--){
        readData();
        init();
        work(100);
	}
    return 0;
}
