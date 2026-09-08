#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

bool dynamic_array_init(DynamicArray *array, int initial_capacity);
void insert_front(DynamicArray *array, int value);
void insert_back(DynamicArray *array, int value);
int find(DynamicArray *array, int value);
int get(DynamicArray *array, int index);
void remove_front(DynamicArray *array);
void free_collection(DynamicArray *array);

#endif
