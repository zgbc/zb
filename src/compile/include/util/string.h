#ifndef _UTIL_STRING_H
#define _UTIL_STRING_H

extern void replaceFirst(char *str1, char *str2, char *str3);
extern void replace(char *str1, char *str2, char *str3);
extern void substring(char *dest, char *src, int start, int end);
extern char charAt(char *src, int index);
extern int indexOf(char *str1, char *str2);
extern int lastIndexOf(char *str1, char *str2);
extern void ltrim(char *str);
extern void rtrim(char *str);
extern void trim(char *str);
extern char * strConcat(int num, ...);
extern char * int2str(int n);
#endif