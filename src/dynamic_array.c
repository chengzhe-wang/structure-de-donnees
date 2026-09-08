#include "dynamic_array.h"

#include <stdlib.h>

bool dynamic_array_init(DynamicArray *array, int initial_capacity)
{
    if (array == NULL || initial_capacity <= 0){
        return false;
    }

    array->data = malloc(sizeof(int) * initial_capacity);

    array->capacity = initial_capacity;
    array->size = 0;
    return true;
}
    

void insert_front(DynamicArray *array, int value){

    if(array->size == array->capacity){
        array->capacity++;
        array->data = realloc(array->data, sizeof(int) * array->capacity);
    }

    for(int i = array->size - 1; i >= 0; i--){
        array->data[i+1] = array->data[i];
    }

    array->data[0] = value;
    array->size++;
}



void insert_back(DynamicArray *array, int value){
    if(array->size == array->capacity){
        array->capacity++;
        array->data = realloc(array->data, sizeof(int) * array->capacity);
    }
    array->data[array->size] = value;
    array->size++;
}


int find(DynamicArray *array, int value){
    if(array == NULL){
        return -1;
    }

    for(int i = 0; i < array->size; i++){
        if(array->data[i] == value){
            return i;
        }
    }
    return -1;
}

int get(DynamicArray *array, int index){
    if(array == NULL || index < 0 || index >= array->size){
        return -1;
    }
    return array->data[index];
}

void remove_front(DynamicArray *array){
    if(array == NULL || array->size == 0){
        return;
    }

    for(int i = 0; i < array->size - 1; i++){
        array->data[i] = array->data[i+1];
    }

    array->size--;
    array->data[array->size] = 0;
}

void free_collection(DynamicArray *array)
{
    if (array == NULL) {
        return;
    }

    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}
