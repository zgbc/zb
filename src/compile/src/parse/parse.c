

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/parse/parse.h"

#define ZBC_FILE_MAX_LINE_SIZE 10240

zbc_file zbc_parse(const char * filename) {
	printf("parse %s start\n", filename);
	zbc_file zbfile;
	zbfile.path = (char *)malloc((strlen(filename)) * sizeof(char));
	strcpy(zbfile.path, filename);
	//return zbfile;
	FILE* fp;
	if ((fp = fopen(filename, "r")) == NULL) //�ж��ļ��Ƿ���ڼ��ɶ�
	{
	    printf("error file not found %s!",filename);
	    return zbfile;
	}
	char * strLine= (char *)malloc(ZBC_FILE_MAX_LINE_SIZE * sizeof(char));
	while (!feof(fp))
	{
	    fgets(strLine, ZBC_FILE_MAX_LINE_SIZE, fp);  //��ȡһ��
	    //printf("%s\n", strLine); //���
		char * strRead= (char *)malloc(strlen(strLine) * sizeof(char));
		int posStrRead = 0;
		int lenLine = strlen(strLine);
		//ȥ����β����
		if (strLine[lenLine - 1] == '\n') lenLine--;
		if (strLine[lenLine - 1] == '\r') lenLine--;
		for (int i = 0; i < lenLine; i++) {
			char cTemp = strLine[i];
			if ((posStrRead > 0 || (cTemp != ' ' && cTemp != '\t'))//��ͷ�ո�
				) {
				if (cTemp == '/'&& strLine[i + 1] == '/') {
					strLine[posStrRead--] = '\0';
					break;
				}
				//printf("c is:%c\n", cTemp); //���
				strRead[posStrRead] = cTemp;
				posStrRead++;
			}
		}
		if (posStrRead > 0) {
			strRead[posStrRead] = '\0';
			printf("code is:%s\n", strRead); //���
		}
		else {
			printf("no code\n");
		}
	}
	printf("parse %s end\n", filename);
	return zbfile;
}

