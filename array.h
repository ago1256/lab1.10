#ifndef ARRAY_H
#define ARRAY_H
#include"vector.h"

typedef struct {
    int count; // Размер массива
    int size;  // Текущее количество добавленных элементов
    Vector **data; 
} Array;

void init_array(Array *array, int count);

void add_element(Array *array, Vector *v);

void free_array(Array *array);

#endif