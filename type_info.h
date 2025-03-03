#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*BinaryOperator)(const void* arg1, const void* arg2, void* result);

typedef struct {
    size_t size;
    BinaryOperator sum;
    BinaryOperator multiply;
    void (*print)(const void*);
} Type_info;

#endif 


