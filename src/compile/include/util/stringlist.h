#ifndef _STRINGLIST_H
#define _STRINGLIST_H

typedef char * string;
typedef struct stringlist sstringlist;
typedef struct stringlist * pstringlist;

struct stringlist {
    int capacity;
    int size;
    string* arr;
};


pstringlist stringlist_init(int capacity) ;

void stringlist_expand_capacity(pstringlist l) ;

void stringlist_add_last(pstringlist l, string v);

void stringlist_add_first(pstringlist l, string v) ;

void stringlist_add_to_index(pstringlist l, string v, int index);

//if string is ptr, need to free l->size - 1
void stringlist_remove_last(pstringlist l);

//if string is ptr, need to free 0
void stringlist_remove_first(pstringlist l) ;

string* stringlist_convert_to_array_free_l(pstringlist l) ;

string stringlist_at(pstringlist l, int index);

void stringlist_free_all(pstringlist l);

void stringlist_print(pstringlist l) ;

#endif