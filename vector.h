#ifndef VECTOR_H
#define VECTOR_H

#include"type_info.h"
#include"double.h"
#include"complex.h"
#include"vector_errors.h"

typedef struct {
    void **coord; 
    size_t v_count;
    Type_info* type_info;
    
} Vector;


Vector* add_vector(Type_info* type_info, size_t v_count, void *x, Vector_errors* operation_result);

Vector_errors print_vector(const Vector *vector);

Vector_errors sum_vector(const Vector *v1, const Vector *v2, Vector *v_res);

Vector_errors scalar_multiplication(const Vector *v1, const Vector *v2, void* res);

Vector_errors multiply_by_a_number(const Vector *v1, double k, Vector *v_res);

Vector_errors vector_overwrite(Type_info* new_type_info, Vector *v1, size_t new_v_count, void *new_coord);

void free_vector(Vector *vector);

#endif 