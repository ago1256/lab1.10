#ifndef VECTORERRORS_H
#define VECTORERRORS_H

#include<stdio.h>

typedef enum {
    VECTOR_OPERATION_OK = 0,
    MEMORY_ALLOCATION_FAILED = 100,
    VECTOR_NOT_DEFINED = 200,
    OPERATION_NOT_DEFINED = 201,
    INCOMPATIBLE_VECTOR_TYPES = 300,
    DIFFERENT_LENGHT_VECTORS = 301,
    UNKNOWN_ERROR = 400

} Vector_errors;

Vector_errors error_detection(Vector_errors operation_result);

#endif 
