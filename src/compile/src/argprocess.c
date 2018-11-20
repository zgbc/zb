#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/argprocess.h"


zbc_parg zbc_arg_process(int argc,char * argv[])
{ 
	zbc_parg arg=(zbc_parg)malloc(sizeof(zbc_arg));
	//args process
	//char* strLibPath = NULL;
	//char* strOutputPath = NULL;
	arg->srcPathList=stringlist_init(2);
	int indexCodePath = 0;
	int i = 1;
	for (; i < argc; i++) {
		if (strcmp(argv[i], "-lib") == 0) {
			arg->strLibPath = argv[i + 1];
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-o") == 0) {
			arg->strOutputPath = argv[i + 1];
			i++;
			continue;
		}
		else {
			break;
		}
	}
	//char* arrCodePath[argc - i];
	for (; i < argc; i++) {
		//arrCodePath[indexCodePath] = argv[i + 1];
		//printf(argv[i]);
		stringlist_add_last(arg->srcPathList,argv[i]);
		indexCodePath++;
	}
	//arrCodePath[indexCodePath] = argv[i];
	printf("strLibPath:%s\n", (arg->strLibPath == NULL) ? "NULL" : arg->strLibPath);
	printf("strOutputPath:%s\n", (arg->strOutputPath == NULL) ? "NULL" : arg->strOutputPath);
	printf("srcPathList:\n");
	stringlist_print(arg->srcPathList);
    return arg;

}

