

#include <stdio.h>
#include "../../include/parse/parse.h"
#include "../../include/util/stringlist.h"
#include "../../include/util/string.h"

#define ZBC_FILE_MAX_LINE_SIZE 10240

zbc_pfile zbc_parse(const char * filename) {
	printf("parse %s start\n", filename);
	zbc_pfile zbfile=(zbc_pfile)malloc(sizeof(zbc_file));
	zbfile->path = (char *)malloc((strlen(filename)) * sizeof(char));
	zbfile->sizeLineCodeTree = 0;
	zbfile->firstLineCodeTree = NULL;
	//zbfile->listLineCodeTree= (zbc_pcodetree[])malloc(10 * sizeof(zbc_pcodetree));
	strcpy(zbfile->path, filename);
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
			zbc_pcodetree lineCodeTree = zbc_parse_line(strRead);
			if (lineCodeTree != NULL) {
				zbfile->firstLineCodeTree = lineCodeTree;
				zbfile->sizeLineCodeTree++;
				//printf("----s%s\n",lineCodeTree->firstChild->value);
				print_codeTree(lineCodeTree);
				//printf("----s\n");
				//print_codeTree(*);
				//print_codeTree(*lineCodeTree);
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


zbc_pcodetree zbc_parse_line(char * str) {
	int lenStr = strlen(str);
	pstringlist strList;
	strList= stringlist_init(4);
	char * strLast= (char *)malloc(ZBC_FILE_MAX_LINE_SIZE * sizeof(char));
	int indexStrLast = 0;
	zbc_pcodetree nowTree;
	zbc_pcodetree lastTree;
	zbc_pcodetree rootTree;

	for (int i = 0; i < lenStr; i++) {
		char c = str[i];
		if (zbc_char_is_lbrackets(c)) {
			if (indexStrLast > 0) {//call函数名称

				nowTree = (zbc_pcodetree)malloc(sizeof(zbc_codetree));
				nowTree->name = strLast;
				nowTree->_asmname = NULL;
				nowTree->codeType = 501;
				nowTree->valueType = 0;
				nowTree->isVariable = false;
				nowTree->sizeSon = 0;
				nowTree->value = NULL;
				nowTree->firstChild = NULL;
				nowTree->nextSibing = NULL;
				strLast = (char *)malloc(ZBC_FILE_MAX_LINE_SIZE * sizeof(char));
				indexStrLast = 0;
				printf("nowTree is %d,%s\n", nowTree->codeType, nowTree->name);
				lastTree = nowTree;
				if (rootTree == NULL) {
					rootTree = nowTree;
				}
			}
		}
		else if (zbc_char_is_comma(c)) {
			if (lastTree != NULL && lastTree->codeType == 501) {//函数非结尾参数
				nowTree = zbc_get_const(strLast);
				//TODO
				printf("lastTree is %d,%s\n", lastTree->codeType, lastTree->name);
			}
		}
		else if (zbc_char_is_rbrackets(c)) {
			if (lastTree != NULL && lastTree->codeType == 501) {//函数结尾参数
				nowTree = zbc_get_const(strLast);
				nowTree->codeType = 511;
				strLast = (char *)malloc(ZBC_FILE_MAX_LINE_SIZE * sizeof(char));
				indexStrLast = 0;

				//print_codeTree(*nowTree);
				if (lastTree->codeType == 501) {
					lastTree->firstChild = nowTree;
					lastTree->sizeSon++;

					lastTree = nowTree;
				}
			}

		}
		else if (!zbc_char_is_symbol(c)){
			strLast[indexStrLast] = c;
			indexStrLast++;
		}

		
	}

	print_codeTree(rootTree);
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
zbc_pcodetree zbc_get_const(char * str) {
	zbc_pcodetree tmpTree=(zbc_pcodetree)malloc(sizeof(zbc_codetree));
	if (str[0] == '"') {
		tmpTree->name = NULL;
		tmpTree->_asmname = NULL;
		tmpTree->codeType = 0;
		tmpTree->valueType = 11;
		tmpTree->isVariable = false;
		tmpTree->sizeSon = 0;
		tmpTree->value = (void *)malloc(strlen(str) - 1);
		tmpTree->firstChild = NULL;
		tmpTree->nextSibing = NULL;
		substring(tmpTree->value,str,1,strlen(str)-2);
	}
	else {
		tmpTree->name = NULL;
		tmpTree->_asmname = NULL;
		tmpTree->codeType = 0;
		tmpTree->valueType = 1;
		tmpTree->isVariable = false;
		tmpTree->sizeSon = 0;
		tmpTree->value = str;
		tmpTree->firstChild = NULL;
		tmpTree->nextSibing = NULL;
	}
	return tmpTree;
}
void print_codeTree(zbc_pcodetree zbCodeTree) {
	printf("zbc_codetree is ");
	printf("name:%s,_asmname:%s,codeType:%d,valueType:%d,isVariable:%d,sizeSon:%d,value:%s,son:{",
		(zbCodeTree->name != NULL) ? zbCodeTree->name : "",
		(zbCodeTree->_asmname != NULL) ? zbCodeTree->_asmname : "",
		zbCodeTree->codeType,
		zbCodeTree->valueType,
		zbCodeTree->isVariable,
		zbCodeTree->sizeSon,
		(zbCodeTree->value != NULL) ? zbCodeTree->value : "");

	zbc_pcodetree son = zbCodeTree->firstChild;
	for (int i = 0; i < zbCodeTree->sizeSon;i++) {
		printf("\t%p", son);
		if (NULL!=son) {
			print_codeTree(son);
			son = son->nextSibing;
		}
		else {
			printf("NULL");
			break;
		}
	}
	printf("}\n");
	/*printf("zbc_codetree is name:%s,value:%s,sizeSon:%d\n", (zbCodeTree->name!=NULL)?zbCodeTree->name:"", 
		(zbCodeTree->value!=NULL)?zbCodeTree->value:"",
		zbCodeTree->sizeSon);*/
}

