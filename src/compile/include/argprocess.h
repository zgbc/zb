#ifndef _ARGPROCESS_H
#define _ARGPROCESS_H

#include "util/stringlist.h"

typedef struct zbc_arg {
	char* strLibPath;
	char* strOutputPath;
	pstringlist srcPathList;
} zbc_arg;

extern zbc_arg zbc_arg_process(int argc,char * argv[]);

#endif