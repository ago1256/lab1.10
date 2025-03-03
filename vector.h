#ifndef VECTOR_H
#define VECTOR_H

#include"type_info.h"
#include"vector_errors.h"

typedef struct {
    void **coord; 
    int v_count;
    Type_info* type_info;
    
} Vector;


Vector* add_vector(Type_info* type_info, int v_count, void **x, Vector_errors* operationResult);

Vector_errors print_vector(Vector *vector);

Vector_errors summ_vector(const Vector *v1, const Vector *v2, Vector *v_res);

Vector_errors scalar_multiplication(const Vector *v1, const Vector *v2, void* res);

void free_vector(Vector *vector);

#endif 
