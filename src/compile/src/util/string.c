#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
/*��str1�ַ����е�һ�γ��ֵ�str2�ַ����滻��str3*/
void replaceFirst(char *str1, char *str2, char *str3)
{
	char str4[strlen(str1) + 1];
	char *p;
	strcpy(str4, str1);
	if ((p = strstr(str1, str2)) != NULL)/*pָ��str2��str1�е�һ�γ��ֵ�λ��*/
	{
		while (str1 != p && str1 != NULL)/*��str1ָ���ƶ���p��λ��*/
		{
			str1++;
		}
		str1[0] = '\0';/*��str1ָ��ָ���ֵ���/0,�Դ����ض�str1,����str2���Ժ�����ݣ�ֻ����str2��ǰ������*/
		strcat(str1, str3);/*��str1��ƴ����str3,�����str1*/
		strcat(str1, strstr(str4, str2) + strlen(str2));/*strstr(str4,str2)��ָ��str2���Ժ������(����str2),strstr(str4,str2)+strlen(str2)���ǽ�ָ����ǰ�ƶ�strlen(str2)λ������str2*/
	}
}
/*��str1���ֵ����е�str2���滻Ϊstr3*/
void replace(char *str1, char *str2, char *str3)
{
	while (strstr(str1, str2) != NULL)
	{
		replaceFirst(str1, str2, str3);
	}
}
/*��ȡsrc�ַ�����,���±�Ϊstart��ʼ��end-1(endǰ��)���ַ���������dest��(�±��0��ʼ)*/
void substring(char *dest, char *src, int start, int end)
{
	int i = start;
	if (start>strlen(src))return;
	if (end>strlen(src))
		end = strlen(src);
	while (i<end)
	{
		dest[i - start] = src[i];
		i++;
	}
	dest[i - start] = '\0';
	return;
}
/*����src���±�Ϊindex���ַ�*/
char charAt(char *src, int index)
{
	char *p = src;
	int i = 0;
	if (index<0 || index>strlen(src))
		return 0;
	while (i<index)i++;
	return p[i];
}
/*����str2��һ�γ�����str1�е�λ��(�±�����),�����ڷ���-1*/
int indexOf(char *str1, char *str2)
{
	char *p = str1;
	int i = 0;
	p = strstr(str1, str2);
	if (p == NULL)
		return -1;
	else {
		while (str1 != p)
		{
			str1++;
			i++;
		}
	}
	return i;
}
/*����str1�����һ�γ���str2��λ��(�±�),�����ڷ���-1*/
int lastIndexOf(char *str1, char *str2)
{
	char *p = str1;
	int i = 0, len = strlen(str2);
	p = strstr(str1, str2);
	if (p == NULL)return -1;
	while (p != NULL)
	{
		for (; str1 != p; str1++)i++;
		p = p + len;
		p = strstr(p, str2);
	}
	return i;
}
/*ɾ��str��ߵ�һ���ǿհ��ַ�ǰ��Ŀհ��ַ�(�ո���ͺ����Ʊ��)*/
void ltrim(char *str)
{
	int i = 0, j, len = strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] != 32 && str[i] != 9)break;/*32:�ո�,9:�����Ʊ��*/
		i++;
	}
	if (i != 0)
		for (j = 0; j <= len - i; j++)
		{
			str[j] = str[j + i];/*��������ַ�˳��ǰ��,����ɾ���Ŀհ�λ��*/
		}
}
/*ɾ��str���һ���ǿհ��ַ���������пհ��ַ�(�ո���ͺ����Ʊ��)*/
void rtrim(char *str)
{
	char *p = str;
	int i = strlen(str) - 1;
	while (i >= 0)
	{
		if (p[i] != 32 && p[i] != 9)break;
		i--;
	}
	str[++i] = '\0';
}
/*ɾ��str���˵Ŀհ��ַ�*/
void trim(char *str)
{
	ltrim(str);
	rtrim(str);
}
/*�����ַ���*/
char * strConcat(int num, ...) {
	va_list valist;
	va_start(valist, num);
	int len = 0;
	int i;
	for (i = 0; i < num; i++)
	{
		len += strlen(va_arg(valist, char *));
	}
	char * strReturn =(char *)malloc(len);

	va_start(valist, num);
	strcpy(strReturn, va_arg(valist, char *));
	for (i = 1; i < num; i++)
	{
		strcat(strReturn, va_arg(valist, char *));
	}
	va_end(valist);
	return strReturn;
}
/*����ת�ַ���*/
char * int2str(int n) {
	char *str= (char *)malloc(10);
	sprintf(str,"%d",n);
	return str;
}