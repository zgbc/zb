#include <stdio.h>
#include <string.h>
#include "../include/argprocess.h"
#include "../include/util/stringlist.h"
#include "../include/util/string.h"
#include "../include/parse/parse.h"
#include "../include/asm/asm.h"

int main(int argc,char * argv[])
{
	//args process
	zbc_parg cmdarg= zbc_arg_process(argc,argv);

    printf("srcPathList.size:%d\n",cmdarg->srcPathList->size);
	for (int i = 0; i < cmdarg->srcPathList->size; i++) {
		zbc_pfile zbFile= zbc_parse(cmdarg->srcPathList->arr[i]);
		printf("zbfile path is %s\n", zbFile->path);
		zbc_pasm_file zbAsmFile= zbc_toasm(zbFile);
		free(zbFile);
		free(zbAsmFile);
	}
	printf("-----------zb compile end------------");
	return 0;
}

