#include <stdio.h>
#include <string.h>
int main(int argc,char * argv[]) 
{ 
	char* strLibPath=NULL;
	char* strOutputPath = NULL;
	int indexCodePath = 0;
	int i = 1;
	for (; i < argc; i++) {
		if (strcmp(argv[i],"-lib")==0) {
			strLibPath = argv[i + 1];
			i++;
			continue;
		}
		else if (strcmp(argv[i], "-o") == 0) {
			strOutputPath = argv[i + 1];
			i++;
			continue;
		}
		else {
			break;
		}
	}
	char* arrCodePath[argc - i];
	for (; i < argc; i++) {
		arrCodePath[indexCodePath] = argv[i + 1];
		indexCodePath++;
	}
	arrCodePath[indexCodePath] = argv[i];
	printf("strLibPath:%s\n",(strLibPath==NULL)?"NULL":strLibPath);
	printf("strOutputPath:%s\n", (strOutputPath == NULL) ? "NULL" : strOutputPath);
	printf("arrlen:%d\n",(int)(sizeof(arrCodePath)/sizeof(char *)));
	return 0;
}
