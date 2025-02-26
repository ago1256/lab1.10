#include <stdio.h>
#include <stdlib.h>
#include"vector.h"
#include"array.h"

Vector* init_vector(int type) {
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    vector->coord = malloc(3 * sizeof(void *));
    vector->type = type;
    return vector;
}

void add_vector(Vector *vector, void *x, void *y, void *z) {
    vector->coord[0] = x;
    vector->coord[1] = y;
    vector->coord[2] = z;
}

void free_vector(Vector *vector){
    free(vector->coord); 
    free(vector);
}

void init_array(Array *array, int count) {
    array->count = count;
    array->size = 0;
    array->data = malloc(count * sizeof(Vector *));
}

void add_element(Array *array, Vector *v) {
    if (array->size < array->count) {
        array->data[array->size] = v;
        array->size++;
    }
}

void free_array(Array *array) {
    for (int i = 0; i < array->size; i++) {
        free_vector(array->data[i]);
        free(array->data[i]); 
    }
    free(array->data);
}


void summ_vector(Vector *v1, Vector *v2, Vector *v_res, int type) {
    if (type == 1) { 
        float *x = malloc(sizeof(float));
        float *y = malloc(sizeof(float));
        float *z = malloc(sizeof(float));
        *x = *(float *)v1->coord[0] + *(float *)v2->coord[0];
        *y = *(float *)v1->coord[1] + *(float *)v2->coord[1];
        *z = *(float *)v1->coord[2] + *(float *)v2->coord[2];
        v_res->coord[0] = x;
        v_res->coord[1] = y;
        v_res->coord[2] = z;
    }
    if (type == 2) {
        Complex_number *x_res = malloc(sizeof(Complex_number));
        Complex_number *y_res = malloc(sizeof(Complex_number));
        Complex_number *z_res = malloc(sizeof(Complex_number));

        x_res->Re_part = ((Complex_number *)v1->coord[0])->Re_part + ((Complex_number *)v2->coord[0])->Re_part;
        x_res->Im_part = ((Complex_number *)v1->coord[0])->Im_part + ((Complex_number *)v2->coord[0])->Im_part;
        y_res->Re_part = ((Complex_number *)v1->coord[1])->Re_part + ((Complex_number *)v2->coord[1])->Re_part;
        y_res->Im_part = ((Complex_number *)v1->coord[1])->Im_part + ((Complex_number *)v2->coord[1])->Im_part;
        z_res->Re_part = ((Complex_number *)v1->coord[2])->Re_part + ((Complex_number *)v2->coord[2])->Re_part;
        z_res->Im_part = ((Complex_number *)v1->coord[2])->Im_part + ((Complex_number *)v2->coord[2])->Im_part;
        
        v_res->coord[0] = x_res;
        v_res->coord[1] = y_res;
        v_res->coord[2] = z_res;
    }
}

void scalar_multiplication(Vector *v1, Vector *v2, void** res, int type){
    if(type==1){
        float *res_float = malloc(sizeof(float));
        *res_float = (*(float *)v1->coord[0]) * (*(float *)v2->coord[0]) + \
                    (*(float *)v1->coord[1]) * (*(float *)v2->coord[1]) + \
                    (*(float *)v1->coord[2]) * (*(float *)v2->coord[2]);
        *res = res_float;
    }
    if(type==2){
        Complex_number *res_complex = malloc(sizeof(Complex_number));

        res_complex->Re_part = (((Complex_number *)v1->coord[0])->Re_part) * (((Complex_number *)v2->coord[0])->Re_part) - \
                            (((Complex_number *)v1->coord[0])->Im_part) * (((Complex_number *)v2->coord[0])->Im_part) + \
                            (((Complex_number *)v1->coord[1])->Re_part) * (((Complex_number *)v2->coord[1])->Re_part) - \
                            (((Complex_number *)v1->coord[1])->Im_part) * (((Complex_number *)v2->coord[1])->Im_part) + \
                            (((Complex_number *)v1->coord[2])->Re_part) * (((Complex_number *)v2->coord[2])->Re_part) - \
                            (((Complex_number *)v1->coord[2])->Im_part) * (((Complex_number *)v2->coord[2])->Im_part);

        res_complex->Im_part = (((Complex_number *)v1->coord[0])->Re_part) * (((Complex_number *)v2->coord[0])->Im_part) - \
                            (((Complex_number *)v1->coord[0])->Im_part) * (((Complex_number *)v2->coord[0])->Re_part) + \
                            (((Complex_number *)v1->coord[1])->Re_part) * (((Complex_number *)v2->coord[1])->Im_part) - \
                            (((Complex_number *)v1->coord[1])->Im_part) * (((Complex_number *)v2->coord[1])->Re_part) + \
                            (((Complex_number *)v1->coord[2])->Re_part) * (((Complex_number *)v2->coord[2])->Im_part) - \
                            (((Complex_number *)v1->coord[2])->Im_part) * (((Complex_number *)v2->coord[2])->Re_part);
        *res = res_complex;
    }
}

void vector_multiplication(Vector *v1, Vector *v2, Vector *v_res, int type){
    if (type == 1) { 
        float *x = malloc(sizeof(float));
        float *y = malloc(sizeof(float));
        float *z = malloc(sizeof(float));

        *x = (*(float *)v1->coord[1]) * (*(float *)v2->coord[2]) - (*(float *)v1->coord[2]) * (*(float *)v2->coord[1]);
        *y = -(*(float *)v1->coord[0]) * (*(float *)v2->coord[2]) + (*(float *)v1->coord[2]) * (*(float *)v2->coord[0]);
        *z = (*(float *)v1->coord[0]) * (*(float *)v2->coord[1]) - (*(float *)v1->coord[1]) * (*(float *)v2->coord[0]);
        
        v_res->coord[0] = x;
        v_res->coord[1] = y;
        v_res->coord[2] = z;
    }

    if (type == 2) {

        Complex_number *x_res = malloc(sizeof(Complex_number));
        Complex_number *y_res = malloc(sizeof(Complex_number));
        Complex_number *z_res = malloc(sizeof(Complex_number));

        x_res->Re_part = (((Complex_number *)v1->coord[1])->Re_part) * (((Complex_number *)v2->coord[2])->Re_part) - \
                        (((Complex_number *)v1->coord[2])->Re_part) * (((Complex_number *)v2->coord[1])->Re_part) - \
                        (((Complex_number *)v1->coord[1])->Im_part) * (((Complex_number *)v2->coord[2])->Im_part) + \
                        (((Complex_number *)v1->coord[2])-> Im_part) * (((Complex_number *)v2->coord[1])->Im_part);

        x_res->Im_part = -(((Complex_number *)v1->coord[1])->Im_part) * (((Complex_number *)v2->coord[2])->Re_part) - \
                        (((Complex_number *)v1->coord[1])->Re_part) * (((Complex_number *)v2->coord[2])->Im_part) + \
                        (((Complex_number *)v1->coord[2])->Im_part) * (((Complex_number *)v2->coord[1])->Re_part) + \
                        (((Complex_number *)v1->coord[2])-> Re_part) * (((Complex_number *)v2->coord[1])->Im_part);

        y_res->Re_part = -((((Complex_number *)v1->coord[0])->Re_part) * (((Complex_number *)v2->coord[2])->Re_part) - \
                        (((Complex_number *)v1->coord[2])->Re_part) * (((Complex_number *)v2->coord[0])->Re_part) - \
                        (((Complex_number *)v1->coord[0])->Im_part) * (((Complex_number *)v2->coord[2])->Im_part) + \
                        (((Complex_number *)v1->coord[2])-> Im_part) * (((Complex_number *)v2->coord[0])->Im_part));

        y_res->Im_part = -(-(((Complex_number *)v1->coord[0])->Im_part) * (((Complex_number *)v2->coord[2])->Re_part) - \
                        (((Complex_number *)v1->coord[0])->Re_part) * (((Complex_number *)v2->coord[2])->Im_part) + \
                        (((Complex_number *)v1->coord[2])->Im_part) * (((Complex_number *)v2->coord[0])->Re_part) + \
                        (((Complex_number *)v1->coord[2])-> Re_part) * (((Complex_number *)v2->coord[0])->Im_part));

        z_res->Re_part = (((Complex_number *)v1->coord[0])->Re_part) * (((Complex_number *)v2->coord[1])->Re_part) - \
                        (((Complex_number *)v1->coord[1])->Re_part) * (((Complex_number *)v2->coord[0])->Re_part) - \
                        (((Complex_number *)v1->coord[0])->Im_part) * (((Complex_number *)v2->coord[1])->Im_part) + \
                        (((Complex_number *)v1->coord[1])-> Im_part) * (((Complex_number *)v2->coord[0])->Im_part);

        z_res->Im_part = -(((Complex_number *)v1->coord[0])->Im_part) * (((Complex_number *)v2->coord[1])->Re_part) - \
                        (((Complex_number *)v1->coord[0])->Re_part) * (((Complex_number *)v2->coord[1])->Im_part) + \
                        (((Complex_number *)v1->coord[1])->Im_part) * (((Complex_number *)v2->coord[0])->Re_part) + \
                        (((Complex_number *)v1->coord[1])-> Re_part) * (((Complex_number *)v2->coord[0])->Im_part);
        
        v_res->coord[0] = x_res;
        v_res->coord[1] = y_res;
        v_res->coord[2] = z_res;
    }

}

void print_vector(Vector *vector) {
    if (vector->type == 1) { 
        printf("%f %f %f\n", *(float *)vector->coord[0], *(float *)vector->coord[1], *(float *)vector->coord[2]);
    }

    if (vector->type == 2) { 
        Complex_number *x = (Complex_number *)vector->coord[0];
        Complex_number *y = (Complex_number *)vector->coord[1];
        Complex_number *z = (Complex_number *)vector->coord[2];
        printf("%f+%fi %f+%fi %f+%fi\n", x->Re_part, x->Im_part, y->Re_part, y->Im_part, z->Re_part, z->Im_part );
    }
}
 void print_array(Array *array, int count){
    for(int i=0; i<count; i++){
        print_vector(array->data[i]);
    }
 }