#include"vector.h"

Vector* add_vector(Type_info* type_info, size_t v_count, void *x, Vector_errors* operation_result) {
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    if (vector == NULL) {
        *operation_result = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    vector->type_info = type_info;
    vector->v_count = v_count;
    vector->coord = malloc(type_info->size * vector->v_count);
    if (vector->coord == NULL) {
        *operation_result = MEMORY_ALLOCATION_FAILED;
        free(vector);
        return NULL;
    }
    if (x != NULL) {
        memcpy(vector->coord, x, type_info->size * vector->v_count);
    }
    *operation_result = VECTOR_OPERATION_OK;
    return vector;
}


Vector** add_vector_to_array(Vector** vectors, size_t* vector_count, Vector* new_vector) {
    vectors = realloc(vectors, (*vector_count + 1) * sizeof(Vector*));
    if (vectors == NULL) {
        return NULL;
    }
    vectors[*vector_count] = new_vector;
    (*vector_count)++;
    return vectors;
}

Vector** remove_vector_from_array(Vector** vectors, size_t* vector_count, int index) {

    free_vector(vectors[index]); 
    for (size_t i = index; i < *vector_count - 1; i++) {
        vectors[i] = vectors[i + 1];
    }
    vectors = realloc(vectors, (*vector_count - 1) * sizeof(Vector*));
    if (vectors == NULL){
        return NULL;
    }
    (*vector_count)--; 
    return vectors;
}

Vector_errors sum_vector(const Vector* v1, const Vector* v2, Vector* v_res){
    if (v1 == NULL || v2 == NULL || v_res == NULL) return VECTOR_NOT_DEFINED;
    if (v1->type_info != v2->type_info || v1->type_info != v_res->type_info) return INCOMPATIBLE_VECTOR_TYPES;
    if (v1->v_count != v2->v_count) return DIFFERENT_LENGHT_VECTORS;
    if (v1->type_info->sum == NULL) return OPERATION_NOT_DEFINED;
    for(int i=0; i<v1->v_count; i++){
        v1->type_info->sum(
            (char*)v1->coord+ i * v1->type_info->size,
            (char*)v2->coord + i * v1->type_info->size,
            (char*)v_res->coord + i * v1->type_info->size);
    }
    return VECTOR_OPERATION_OK;
}
Vector_errors scalar_multiplication(const Vector *v1, const Vector *v2, void* res){
    if (v1 == NULL || v2 == NULL || res == NULL) return VECTOR_NOT_DEFINED;
    if (v1->type_info != v2->type_info) return INCOMPATIBLE_VECTOR_TYPES;
    if (v1->v_count != v2->v_count) return DIFFERENT_LENGHT_VECTORS;
    if (v1->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;
    memset(res, 0, v1->type_info->size);
    for(int i=0; i<v1->v_count; i++){
        void* arg1 = (char*)v1->coord + i * v1->type_info->size;
        void* arg2 = (char*)v2->coord + i * v2->type_info->size;
        void* temp_result = malloc(v1->type_info->size);
        if (temp_result == NULL) return MEMORY_ALLOCATION_FAILED; 
        v1->type_info->multiply(arg1, arg2, temp_result);  
        v1->type_info->sum(res, temp_result, res);
        free(temp_result); 
    }
    return VECTOR_OPERATION_OK;
}

Vector_errors multiply_by_a_number(const Vector *v1, double k, Vector *v_res){
    if (v1 == NULL || v_res == NULL) return VECTOR_NOT_DEFINED;
    if(v1->type_info == Get_complex_type_info()) return INCOMPATIBLE_VECTOR_TYPES;
    for(int i=0; i<v1->v_count; i++){
        v1->type_info->multiply(
            (char*)v1->coord+ i * v1->type_info->size,
            (char*)&k,
            (char*)v_res->coord + i * v1->type_info->size);
    }
    return VECTOR_OPERATION_OK;
}

Vector_errors vector_overwrite(Type_info* new_type_info, Vector *v1, size_t *new_v_count, void *new_coord) {
    if (v1 == NULL || new_coord == NULL || new_v_count == NULL) return VECTOR_NOT_DEFINED;
    v1->type_info = new_type_info;
    void *coord = realloc(v1->coord, new_type_info->size * (*new_v_count));
    if (coord == NULL) {
        return VECTOR_NOT_DEFINED; 
    }
    v1->coord = coord;
    v1->v_count = *new_v_count;
    memcpy(v1->coord, new_coord, v1->v_count * new_type_info->size);
    return VECTOR_OPERATION_OK;
}

Vector_errors print_vector(const Vector* vector) {
    if (vector == NULL) return VECTOR_NOT_DEFINED;
    if (vector->type_info->print == NULL) return OPERATION_NOT_DEFINED;

    for(int i=0; i<vector->v_count; i++){
        vector->type_info->print((char*)vector->coord + i * vector->type_info->size);
    }
    printf("\n");

    return VECTOR_OPERATION_OK;
}

void free_vector(Vector *vector) {
    free(vector->coord);
    free(vector);
}