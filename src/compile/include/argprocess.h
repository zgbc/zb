#ifndef _ARGPROCESS_H
#define _ARGPROCESS_H

#include "util/stringlist.h"

typedef struct zbc_arg * zbc_parg;
typedef struct zbc_arg {
	char* strLibPath;
	char* strOutputPath;
	pstringlist srcPathList;
} zbc_arg;

extern zbc_parg zbc_arg_process(int argc,char * argv[]);

#endif