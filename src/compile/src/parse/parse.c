

#include <stdio.h>
#include "../../include/parse/parse.h"
#include "../../include/util/stringlist.h"
#include "../../include/util/string.h"

#define ZBC_FILE_MAX_LINE_SIZE 10240

zbc_file zbc_parse(const char * filename) {
	printf("parse %s start\n", filename);
	zbc_file zbfile;
	zbfile.path = (char *)malloc((strlen(filename)) * sizeof(char));
	strcpy(zbfile.path, filename);
	//return zbfile;
	FILE* fp;
	if ((fp = fopen(filename, "r")) == NULL) //判断文件是否存在及可读
	{
	    printf("error file not found %s!",filename);
	    return zbfile;
	}
	char * strLine= (char *)malloc(ZBC_FILE_MAX_LINE_SIZE * sizeof(char));
	
	while (!feof(fp))
	{
	    fgets(strLine, ZBC_FILE_MAX_LINE_SIZE, fp);  //读取一行
		char * strRead= (char *)malloc(strlen(strLine) * sizeof(char));
		int posStrRead = 0;
		int lenLine = strlen(strLine);
		//去掉结尾换行
		if (strLine[lenLine - 1] == '\n') lenLine--;
		if (strLine[lenLine - 1] == '\r') lenLine--;
		for (int i = 0; i < lenLine; i++) {
			char cTemp = strLine[i];
			if ((posStrRead > 0 || (cTemp != ' ' && cTemp != '\t'))//开头空格
				) {
				if (cTemp == '/'&& strLine[i + 1] == '/') {
					strLine[posStrRead--] = '\0';
					break;
				}
				strRead[posStrRead] = cTemp;
				posStrRead++;
			}
		}
		if (posStrRead > 0) {
			strRead[posStrRead] = '\0';
			printf("code is:%s\n", strRead); //输出
			zbc_codetree* lineCodeTree = zbc_parse_line(strRead);
			if (lineCodeTree != NULL) {
				/*zbfile.listLineCodeTree[zbfile.indexListLineCodeTree] = lineCodeTree;
				zbfile.indexListLineCodeTree++;*/
				//printf("lineCodeTree is codeType:%d\n",lineCodeTree->codeType);
			}
		}
		else {
			printf("no code\n");
		}
	}
	printf("parse %s end\n", filename);
	return zbfile;
}


zbc_codetree* zbc_parse_line(char * str) {
	int lenStr = strlen(str);
	pstringlist strList;
	strList= stringlist_init(4);
	char * strLast= (char *)malloc(ZBC_FILE_MAX_LINE_SIZE * sizeof(char));
	int indexStrLast = 0;
	zbc_codetree* nowTree;
	zbc_codetree* lastTree;
	zbc_codetree* rootTree;

	for (int i = 0; i < lenStr; i++) {
		char c = str[i];
		if (zbc_char_is_lbrackets(c)) {
			if (indexStrLast > 0) {//call函数名称

				zbc_codetree tmpTree;
				nowTree = &tmpTree;
				nowTree->codeType = 501;
				nowTree->name = strLast;
				nowTree->sizeSon = 0;
				strLast = (char *)malloc(ZBC_FILE_MAX_LINE_SIZE * sizeof(char));
				indexStrLast = 0;
				printf("nowTree is %d,%s\n", nowTree->codeType, nowTree->name);
				lastTree= (zbc_codetree*)malloc(sizeof(zbc_codetree));
				memcpy(lastTree,nowTree,sizeof(zbc_codetree));
				if (rootTree == NULL) {
					rootTree = (zbc_codetree*)malloc(sizeof(zbc_codetree));
					memcpy(rootTree, nowTree, sizeof(zbc_codetree));
					//memcpy(rootTree, nowTree, sizeof(zbc_codetree));
				}
			}
		}
		else if (zbc_char_is_comma(c)) {
			if (lastTree != NULL && lastTree->codeType == 501) {//函数非结尾参数
				zbc_codetree tmpTree;
				tmpTree= zbc_get_const(strLast);
				lastTree = &tmpTree;

				printf("lastTree is %d,%s\n", lastTree->codeType, lastTree->name);
			}
		}
		else if (zbc_char_is_rbrackets(c)) {
			if (lastTree != NULL && lastTree->codeType == 501) {//函数结尾参数
				zbc_codetree tmpTree;
				tmpTree = zbc_get_const(strLast);
				nowTree = &tmpTree;
				nowTree->codeType = 511;
				strLast = (char *)malloc(ZBC_FILE_MAX_LINE_SIZE * sizeof(char));
				indexStrLast = 0;
				printf("nowTree is codeType:%d,valueType:%d,value:%s\n", nowTree->codeType, nowTree->valueType, nowTree->value);
				
				lastTree->son[lastTree->sizeSon] = nowTree;
				lastTree->sizeSon++;
			}

		}
		else if (!zbc_char_is_symbol(c)){
			strLast[indexStrLast] = c;
			indexStrLast++;
		}

		
	}

	if (rootTree != NULL) {
		printf("rootTree is codeType:%d\n", rootTree->codeType);
	}
	return rootTree;
}
bool zbc_char_is_blank(char c) {
	return c == ' ';
}
bool zbc_char_is_comma(char c) {
	return c == ',';
}
bool zbc_char_is_semicolon(char c) {
	return c == ';';
}
bool zbc_char_is_operator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}
bool zbc_char_is_lbrackets(char c) {
	return c == '(';
}
bool zbc_char_is_rbrackets(char c) {
	return c == ')';
}
bool zbc_char_is_symbol(char c) {
	return zbc_char_is_blank(c) || zbc_char_is_comma(c)||
		zbc_char_is_semicolon(c)|| zbc_char_is_operator(c)||
		zbc_char_is_lbrackets(c)|| zbc_char_is_rbrackets(c);
}
zbc_codetree zbc_get_const(char * str) {
	zbc_codetree tmpTree;
	if (str[0] == '"') {
		tmpTree.valueType = 11;
		tmpTree.value = (void *)malloc(strlen(str) - 1);
		substring(tmpTree.value,str,1,strlen(str)-2);
	}
	else {
		tmpTree.valueType = 1;
		tmpTree.value = str;
	}
	return tmpTree;
}

