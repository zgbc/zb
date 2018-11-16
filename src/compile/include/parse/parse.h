#ifndef _PARSE_PARSE_H
#define _PARSE_PARSE_H

/*
½á¹¹
package
file
class
function
call
*/
#include "../util/intlist.h"

typedef struct zbc_package zbc_package;

typedef struct zbc_file zbc_file;

typedef struct zbc_type zbc_type;

typedef struct zbc_class zbc_class;

typedef struct zbc_function zbc_function;

typedef struct zbc_function_arg zbc_function_arg;

typedef struct zbc_call zbc_call;

typedef struct zbc_call_arg zbc_call_arg;

struct zbc_package {
	intlist files;
} ;

struct zbc_file {
	char * path;
	intlist zbclass;
	intlist zbfunction;
	char * body;
};

struct zbc_type {
	char * name;
};

struct zbc_class {

};

struct zbc_function {

};

struct zbc_function_arg {

};


struct zbc_call {
	char * name;
	zbc_type returnType;
	int argsSize;
	intlist args;
};

struct zbc_call_arg {
	char * name;
	char * value;
	zbc_type argType;
};





zbc_file zbc_parse(const char * file);

#endif // !_PARSE_PARSE_H
