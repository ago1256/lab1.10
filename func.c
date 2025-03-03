#include <stdio.h>
#include <stdlib.h>
#include"vector.h"
#include"vector_errors.h"

Vector* add_vector(Type_info* type_info, int v_count, void **x, Vector_errors* operationResult) {
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    if (vector == NULL) {
        *operationResult = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    vector->type_info = type_info;
    vector->v_count = v_count;
    vector->coord = malloc(type_info->size * vector->v_count);
    for(int i=0; i<vector->v_count; i++){
        memcpy(vector->coord[i], x[i], type_info->size);
        }
    *operationResult = VECTOR_OPERATION_OK;
    return vector;
}


Vector_errors vector_sum(const Vector* v1, const Vector* v2, Vector* v_res){
    if (v1 == NULL || v2 == NULL || v_res == NULL) return VECTOR_NOT_DEFINED;
    if (v1->type_info != v2->type_info || v1->type_info != v_res->type_info) return INCOMPATIBLE_VECTOR_TYPES;
    if (v1->type_info->sum == NULL) return OPERATION_NOT_DEFINED;
    for(int i=0; i<v1->v_count; i++){
        v1->type_info->sum(v1->coord[i], v2->coord[i], v_res->coord[i]);
    }
    return VECTOR_OPERATION_OK;
}

Vector_errors scalar_multiplication(const Vector *v1, const Vector *v2, void* res){
    if (v1 == NULL || v2 == NULL || res == NULL) return VECTOR_NOT_DEFINED;
    if (v1->type_info != v2->type_info) return INCOMPATIBLE_VECTOR_TYPES;
    if (v1->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;
    for(int i=0; i<v1->v_count; i++){
        v1->type_info->multiply(v1->coord[i], v2->coord[i], res);
    }
    return VECTOR_OPERATION_OK;
}



Vector_errors printVector(const Vector* vector) {
    if (vector == NULL) return VECTOR_NOT_DEFINED;
    if (vector->type_info->print == NULL) return OPERATION_NOT_DEFINED;

    for(int i=0; i<vector->v_count; i++){
        vector->type_info->print(vector->coord[i]);
    }

    return VECTOR_OPERATION_OK;
}

void free_vector(Vector *vector) {
    free(vector->coord);
    free(vector);
}