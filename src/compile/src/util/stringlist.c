
/*
    array list
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/util/stringlist.h"


pstringlist stringlist_init(int capacity) {
    pstringlist l = (pstringlist) malloc(sizeof(sstringlist));
    if (capacity < 1) return NULL;
    l->arr = (string*) malloc(sizeof(string) * capacity);
    l->capacity = capacity;
    l->size = 0;
    return l;
}

void stringlist_expand_capacity(pstringlist l) {
    string* new_arr = (string*) malloc(sizeof(string) * (l->capacity * 2 + 1));
    int i = 0;
    for (i = 0; i < l->capacity; i ++)
        new_arr[i] = l->arr[i];
    free(l->arr);
    l->arr = new_arr;
    l->capacity = l->capacity * 2 + 1;
}

void stringlist_add_last(pstringlist l, string v) {
    if (l->capacity == l->size) stringlist_expand_capacity(l);
    l->arr[l->size] = v;
    l->size ++;
}

void stringlist_add_first(pstringlist l, string v) {
    int i = 0;
    if (l->capacity == l->size) stringlist_expand_capacity(l);
    for (i = l->size; i > 0; i --)
        l->arr[i] = l->arr[i - 1];
    l->arr[0] = v;
    l->size ++;
}

void stringlist_add_to_index(pstringlist l, string v, int index) {
    int i = 0;
    if (index > l->size) return;
    if (l->capacity == l->size) stringlist_expand_capacity(l);
    for (i = l->size - 1; i >= index; i --) {
        l->arr[i+1] = l->arr[i];
    }
    l->arr[index] = v;
    l->size ++;
}

//if T is ptr, need to free l->size - 1
void stringlist_remove_last(pstringlist l) {
    if (l->size == 0) return;
    l->arr[l->size - 1] = 0; //or NULL and free
    l->size --;
}

//if T is ptr, need to free 0
void stringlist_remove_first(pstringlist l) {
    int i = 0;
    if (l->size == 0) return;
    l->arr[0] = 0; //or NULL and free
    for (i = 1; i < l->size; i ++) {
        l->arr[i - 1] = l->arr[i];
    }
    l->size --;
}

string* stringlist_convert_to_array_free_l(pstringlist l) {
    string* arr = l->arr;
    free(l);
    return arr;
}

string stringlist_at(pstringlist l, int index) {
    if (index >= l->size || index < 0) return 0;
    return l->arr[index];
}

void stringlist_free_all(pstringlist l) {
    free(l->arr);
    free(l);
}

void stringlist_print(pstringlist l) {
    int i = 0;
    if (l->size == 0) return;
    for (i = 0; i < l->size; i ++)
        printf("%s ", l->arr[i]);
    printf("\r\n");
}