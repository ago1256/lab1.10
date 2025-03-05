#include "vector.h"


int main(){

    float a1[] = {1.0, 2.0, 3.0, 4.0};
    float a2[] = {8.0, 3.0, 5.0, 6.0};
    float a3[] = {0.0, 0.0, 0.0, 0.0};
    //float a4[] = {-4.0, -3.0, 2.0, 1.0};
    //float a5[] = {8.0, 3.0, 5.5, 2.0, 7.5};

    Vector_errors operationResult = VECTOR_OPERATION_OK;

    Vector* v1 = add_vector(Get_float_Type_info(), 4, a1, &operationResult);
    Vector* v2 = add_vector(Get_float_Type_info(), 4, a2, &operationResult);
    Vector* v3 = add_vector(Get_float_Type_info(), 4, a3, &operationResult);
 
    printf("Vector 1: ");
    print_vector(v1);

    printf("Vector 2: ");
    print_vector(v2);

    sum_vector(v1, v2, v3);

    printf("Sum of vectors: ");
    print_vector(v3);



    free_vector(v1);
    free_vector(v2);
    free_vector(v3);

}