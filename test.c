#include "Vector.h"

int test(){
    float a1[4] = {1.0, 2.0, 3.0, 4.0};
    float a2[4] = {8.0, 3.0, 5.0, 6.0};
    float a3[4] = {0.0, 0.0, 0.0, 0.0};
    float a4[4] = {-4.0, -3.0, 2.0, 1.0};
    float a5[5] = {8.0, 3.0, 5.5, 2.0, 7.5};
    float a_sum_v1_v2[4] = {0};

    Vector_errors operationResult = VECTOR_OPERATION_OK;

    Vector* v1 = add_vector(Get_float_Type_info(), sizeof(a1), a1, &operationResult);
    Vector* v2 = add_vector(Get_float_Type_info(), sizeof(a2), a2, &operationResult);
    Vector* v3 = add_vector(Get_float_Type_info(), sizeof(a3), a3, &operationResult);
    Vector* v4 = add_vector(Get_float_Type_info(), sizeof(a4), a4, &operationResult);
    Vector* v5 = add_vector(Get_float_Type_info(), sizeof(a5), a5, &operationResult);
    Vector* sum_v1_v2 = add_vector(Get_float_Type_info(), sizeof(a_sum_v1_v2), a_sum_v1_v2, &operationResult);

    printf("Vector 1: ");
   print_vector(v1);

    printf("Vector 2: ");
    print_vector(v2);

   summ_vector(v1, v2, sum_v1_v2);

    printf("Sum of vectors: ");
    print_vector(sum_v1_v2);



    free_vector(v1);
    free_vector(v2);
    free_vector(sum_v1_v2);

    return 0;
}
