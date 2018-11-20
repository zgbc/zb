#ifndef _PARSE_PARSE_H
#define _PARSE_PARSE_H

/*
结构
package
file
class
function
call
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../util/intlist.h"

typedef struct zbc_package zbc_package;

typedef struct zbc_file zbc_file;
typedef struct zbc_file * zbc_pfile;

typedef struct zbc_type zbc_type;

typedef struct zbc_class zbc_class;

typedef struct zbc_function zbc_function;

typedef struct zbc_function_arg zbc_function_arg;

typedef struct zbc_call zbc_call;

typedef struct zbc_call_arg zbc_call_arg;

typedef struct _zbc_codetree * zbc_pcodetree;

typedef struct _zbc_codetree {
	char * name;//名称
	char * _asmname;//编译名称
	int codeType;//代码类型 501=callName,511=callArg
	int valueType;//值类型 1=int,11=string
	bool isVariable;//可变类型 false=const 常量,true=var 变量
	char * value;
	int sizeSon;
	struct _zbc_codetree *firstChild;//第一个子节点
	struct _zbc_codetree *nextSibing;//下一个节点
} zbc_codetree;


//1xx
struct zbc_package {
	intlist files;
} ;

//2xx
struct zbc_file {
	char * path;
	int sizeLineCodeTree;
	zbc_codetree* firstLineCodeTree;

	/*intlist zbclass;
	intlist zbfunction;
	char * body;*/
};

struct zbc_type {
	char * name;
};

//3xx
struct zbc_class {

};

//4xx
struct zbc_function {

};
//41x
struct zbc_function_arg {

};

//5xx
struct zbc_call {
	char * name;
	zbc_type returnType;
	int argsSize;
	intlist args;
};
//51x
struct zbc_call_arg {
	char * name;
	char * value;
	zbc_type argType;
};




extern zbc_pfile zbc_parse(const char * file);

extern zbc_pcodetree zbc_parse_line(char * str);

extern bool zbc_char_is_blank(char c);

extern bool zbc_char_is_comma(char c);

extern bool zbc_char_is_semicolon(char c);

extern bool zbc_char_is_operator(char c);

extern bool zbc_char_is_lbrackets(char c);

extern bool zbc_char_is_rbrackets(char c);

extern bool zbc_char_is_symbol(char c);

extern zbc_pcodetree zbc_get_const(char * str);

extern void print_codeTree(zbc_pcodetree zbCodeTree);

#endif // !_PARSE_PARSE_H
