#include <fstream>
#include <cstdio>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
	ifstream fin(argv[1]);
	ifstream fout(argv[2]);
	ifstream fstd(argv[3]);

	double x, y;
	while(fout >> x){
		fstd >> y;
		if(abs(x - y) > 0.01){
			puts("no");
			return 1;
		}
	}
	puts("yes");
	return 0;
}
