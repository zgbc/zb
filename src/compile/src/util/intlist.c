
/*
    array list
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/util/intlist.h"


pintlist intlist_init(int capacity) {
    pintlist l = (pintlist) malloc(sizeof(intlist));
    if (capacity < 1) return NULL;
    l->arr = (T*) malloc(sizeof(T) * capacity);
    l->capacity = capacity;
    l->size = 0;
    return l;
}

void intlist_expand_capacity(pintlist l) {
    T* new_arr = (T*) malloc(sizeof(T) * (l->capacity * 2 + 1));
    int i = 0;
    for (i = 0; i < l->capacity; i ++)
        new_arr[i] = l->arr[i];
    free(l->arr);
    l->arr = new_arr;
    l->capacity = l->capacity * 2 + 1;
}

void intlist_add_last(pintlist l, T v) {
    if (l->capacity == l->size) intlist_expand_capacity(l);
    l->arr[l->size] = v;
    l->size ++;
}

void intlist_add_first(pintlist l, T v) {
    int i = 0;
    if (l->capacity == l->size) intlist_expand_capacity(l);
    for (i = l->size; i > 0; i --)
        l->arr[i] = l->arr[i - 1];
    l->arr[0] = v;
    l->size ++;
}

void intlist_add_to_index(pintlist l, T v, int index) {
    int i = 0;
    if (index > l->size) return;
    if (l->capacity == l->size) intlist_expand_capacity(l);
    for (i = l->size - 1; i >= index; i --) {
        l->arr[i+1] = l->arr[i];
    }
    l->arr[index] = v;
    l->size ++;
}

//if T is ptr, need to free l->size - 1
void intlist_remove_last(pintlist l) {
    if (l->size == 0) return;
    l->arr[l->size - 1] = 0; //or NULL and free
    l->size --;
}

//if T is ptr, need to free 0
void intlist_remove_first(pintlist l) {
    int i = 0;
    if (l->size == 0) return;
    l->arr[0] = 0; //or NULL and free
    for (i = 1; i < l->size; i ++) {
        l->arr[i - 1] = l->arr[i];
    }
    l->size --;
}

T* intlist_convert_to_array_free_l(pintlist l) {
    T* arr = l->arr;
    free(l);
    return arr;
}

T intlist_at(pintlist l, int index) {
    if (index >= l->size || index < 0) return 0;
    return l->arr[index];
}

void intlist_free_all(pintlist l) {
    free(l->arr);
    free(l);
}

void intlist_print(pintlist l) {
    int i = 0;
    if (l->size == 0) return;
    for (i = 0; i < l->size; i ++)
        printf("%d ", l->arr[i]);
    printf("\r\n");
}