#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    void **coord; 
    int type;
} Vector;

typedef struct {
    float Re_part;
    float Im_part;
} Complex_number;

Vector* init_vector(int type);

void add_vector(Vector *vector, void *x, void *y, void *z);

void print_vector(Vector *vector);

void summ_vector(Vector *v1, Vector *v2, Vector *v_res, int type);

void scalar_multiplication(Vector *v1, Vector *v2, void** res, int type);

void vector_multiplication(Vector *v1, Vector *v2, Vector *v_res, int type);

void free_vector(Vector *vector);

#endif 
