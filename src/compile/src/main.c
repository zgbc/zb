#include <stdio.h>
#include <string.h>
#include "../include/argprocess.h"
#include "../include/util/stringlist.h"
#include "../include/util/string.h"
#include "../include/parse/parse.h"

int main(int argc,char * argv[]) 
{ 

	//args process
	zbc_arg cmdarg;
	cmdarg= zbc_arg_process(argc,argv);

    printf("srcPathList.size:%d\n",cmdarg.srcPathList->size);
	for (int i = 0; i < cmdarg.srcPathList->size; i++) {
		zbc_file zbfile= zbc_parse(cmdarg.srcPathList->arr[i]);
		printf("zbfile path is %s\n", zbfile.path);
		/*for (int i = 0; i < zbfile.indexListLineCodeTree; i++) {
			zbc_codetree* lineCodeTree = zbfile.listLineCodeTree[i];
			printf("lineCodeTree is codeType:%d\n", lineCodeTree->codeType);

		}*/
	}

	return 0;
}

