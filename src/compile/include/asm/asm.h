#ifndef _ASM_ASM_H
#define _ASM_ASM_H


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../util/intlist.h"
#include "../util/stringlist.h"
#include "../util/string.h"
#include "../parse/parse.h"

typedef struct zbc_asm_file  * zbc_pasm_file;

typedef struct zbc_asm_file {
	char * path;
	pstringlist sectionData;
	pstringlist sectionText;
} zbc_asm_file ;

extern zbc_pasm_file zbc_toasm(zbc_pfile zbfile);

extern void zbc_asm_save(zbc_pasm_file asmfile);

#endif // !_ASM_ASM_H
