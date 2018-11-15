#include <stdio.h>
int main(int argc,char * argv[]) 
{
	int a=3001;
	int b=1000;
	int h=a+b;
	int i=a-b;
	int j=a*b;
	int k=a/b;
	printf("int is %d,%d,%d,%d\n",h,i,j,k);

	long la=4001;
	long lb=2000;
	long lh=la+lb;
	printf("long is %d\n",lh);

	long long lla=6001;
	long long llb=5000;
	long long llh=lla+llb;
	printf("long long is %d\n",llh);
	return 0;
}
