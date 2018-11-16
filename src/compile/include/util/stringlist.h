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


extern pstringlist stringlist_init(int capacity) ;

extern void stringlist_expand_capacity(pstringlist l) ;

extern void stringlist_add_last(pstringlist l, string v);

extern void stringlist_add_first(pstringlist l, string v) ;

extern void stringlist_add_to_index(pstringlist l, string v, int index);

//if string is ptr, need to free l->size - 1
extern void stringlist_remove_last(pstringlist l);

//if string is ptr, need to free 0
extern void stringlist_remove_first(pstringlist l) ;

extern string* stringlist_convert_to_array_free_l(pstringlist l) ;

extern string stringlist_at(pstringlist l, int index);

extern void stringlist_free_all(pstringlist l);

extern void stringlist_print(pstringlist l) ;

#endif