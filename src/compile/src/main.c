#include <stdio.h>
#include <string.h>
#include "../include/argprocess.h"
#include "../include/stringlist.h"
int main(int argc,char * argv[]) 
{ 

	//args process
	zbc_arg cmdarg;
	cmdarg= zbc_arg_process(argc,argv);

    printf("srcPathList.size:%d\n",cmdarg.srcPathList->size);


	return 0;
}

