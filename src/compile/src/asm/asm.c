#include <stdio.h>
#include "../../include/asm/asm.h"

//常量、变量名前缀
#define ZBC_ASM_CONST "C"
#define ZBC_ASM_VAR "V"

zbc_pasm_file zbc_toasm(zbc_pfile zbfile) {
	printf("zbc_toasm %s\n", zbfile->path);
	zbc_pasm_file asmfile=(zbc_pasm_file)malloc(sizeof(zbc_asm_file));
	char * path=(char *)malloc(sizeof(char)*strlen(zbfile->path));
	substring(path, zbfile->path, 0, strlen(zbfile->path) - 2);
	asmfile->path = strConcat(2, path, "s");
	asmfile->sectionData = stringlist_init(8);
	asmfile->sectionText = stringlist_init(16);
	int indexDataConst = 0;
	zbc_pcodetree lineCodeTree = zbfile->firstLineCodeTree;
	for (int i = 0; i < zbfile->sizeLineCodeTree; i++) {
		print_codeTree(lineCodeTree);
		printf("--1\n");
		if (lineCodeTree->codeType == 501) {
			if (strcmp(lineCodeTree->name, "printf")==0) {//printf
				stringlist_add_last(asmfile->sectionText, "\tmovq $1, %rax\n\
\tmovq $1, %rdi\n");
				zbc_pcodetree sonCodeTree = lineCodeTree->firstChild;
				for (int j = 0; j < lineCodeTree->sizeSon; j++) {
					print_codeTree(sonCodeTree);
					if (sonCodeTree->codeType == 511) {
						if (sonCodeTree->sizeSon == 0) {//参数
							if (sonCodeTree->valueType == 11&& !sonCodeTree->isVariable) {
								sonCodeTree->name = strConcat(2, ZBC_ASM_CONST, int2str(indexDataConst));
								indexDataConst++;
								stringlist_add_last(asmfile->sectionData, strConcat(7, sonCodeTree->name, ":\n\
\t.ascii \"", sonCodeTree->value, "\"\n\
\t", sonCodeTree->name, "_length = . - ", sonCodeTree->name));
								stringlist_add_last(asmfile->sectionText, strConcat(3, "\tlea ", sonCodeTree->name, "(%rip), %rsi\n"));
								stringlist_add_last(asmfile->sectionText, strConcat(3, "\tmovq $", sonCodeTree->name, "_length, %rdx\n"));
							}
						}
					}
					sonCodeTree = sonCodeTree->nextSibing;
				}
				stringlist_add_last(asmfile->sectionText, "\tsyscall");
			}

		}
		lineCodeTree = lineCodeTree->nextSibing;
	}
	stringlist_print(asmfile->sectionData);
	stringlist_print(asmfile->sectionText);
	zbc_asm_save(asmfile);
	return asmfile;
}
void zbc_asm_save(zbc_pasm_file asmfile) {
	FILE *fp = NULL;

	fp = fopen(asmfile->path, "w+");
	fputs("\t.section .rodata\n", fp);
	pstringlist slSectionData= asmfile->sectionData;
	int i;
	for (i = 0; i < slSectionData->size; i++) {
		fprintf(fp, "%s\n", slSectionData->arr[i]);
	}

	fputs("\t.section .text\n", fp);
	fputs("\t.global _start\n", fp);
	fputs("_start:\n", fp);

	pstringlist slSectionText = asmfile->sectionText;
	for (i = 0; i < slSectionText->size; i++) {
		fprintf(fp, "%s\n", slSectionText->arr[i]);
	}


	fputs("\tmovq $60, %rax\n", fp);
	fputs("\txor %rdi, %rdi\n", fp);
	fputs("\tsyscall\n", fp);
	fclose(fp);
}

