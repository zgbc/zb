#ifndef _INTLIST_H
#define _INTLIST_H

typedef int T;
typedef struct intlist intlist;
typedef struct intlist * pintlist;

struct intlist {
    int capacity;
    int size;
    T* arr;
};
#endif