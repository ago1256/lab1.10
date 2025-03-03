#include "complex.h"

void complex_sum(const void* arg1, const void* arg2, void* result){
        Complex_number *x = malloc(sizeof(Complex_number));
        x->Re_part = ((Complex_number *)arg1)->Re_part + ((Complex_number *)arg2)->Re_part;
        x->Im_part = ((Complex_number *)arg1)->Im_part + ((Complex_number *)arg2)->Im_part;
        result = x;
        free(x);
    }

void complex_multiply(const void* arg1, const void* arg2, void* result){
    Complex_number *res_complex = malloc(sizeof(Complex_number));
    res_complex->Re_part += ((Complex_number *)arg1)->Re_part * ((Complex_number *)arg2)->Re_part -\
    ((Complex_number *)arg1)->Im_part * ((Complex_number *)arg2)->Im_part;

    res_complex->Im_part = ((Complex_number *)arg1)->Re_part * ((Complex_number *)arg2)->Im_part + \
    ((Complex_number *)arg1)->Im_part * ((Complex_number *)arg2)->Re_part;
    result = res_complex;
    free(res_complex);
}
void complex_print(const void* data){
   Complex_number *x = (Complex_number *)data;
    printf("%f+%fi ", x->Re_part, x->Im_part);
    free(x);
}

Type_info* Get_complex_Type_info() {
    if (COMPLEX_TYPE_INFO == NULL) {
        COMPLEX_TYPE_INFO = (Type_info*)malloc(sizeof(Type_info));
        COMPLEX_TYPE_INFO ->size = sizeof(float);
        COMPLEX_TYPE_INFO ->sum = complex_sum;
        COMPLEX_TYPE_INFO ->multiply = complex_multiply;
        COMPLEX_TYPE_INFO ->print = complex_print;
    }
    return COMPLEX_TYPE_INFO;
}

