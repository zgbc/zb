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



extern pintlist intlist_init(int capacity);

extern void intlist_expand_capacity(pintlist l);

extern void intlist_add_last(pintlist l, T v);

extern void intlist_add_first(pintlist l, T v);

extern void intlist_add_to_index(pintlist l, T v, int index);

//if string is ptr, need to free l->size - 1
extern void intlist_remove_last(pintlist l);

//if string is ptr, need to free 0
extern void intlist_remove_first(pintlist l);

extern  T* intlist_convert_to_array_free_l(pintlist l);

extern  T intlist_at(pintlist l, int index);

extern void intlist_free_all(pintlist l);

extern void intlist_print(pintlist l);
#endif