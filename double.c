#include "double.h"

void double_sum(const void* arg1, const void* arg2, void* result) {
    *(double*)result = *(double*)arg1 + *(double*)arg2;
}

void double_multiply(const void* arg1, const void* arg2, void* result) {
    *(double*)result = *(double*)arg1 * *(double*)arg2;
}

void double_print(const void* data) {
    printf("%.3lf ", *(const double*)data);
}

Type_info* Get_double_type_info() {
    if (DOUBLE_TYPE_INFO == NULL) {
        DOUBLE_TYPE_INFO = (Type_info*)malloc(sizeof(Type_info));
        DOUBLE_TYPE_INFO ->size = sizeof(double);
        DOUBLE_TYPE_INFO ->sum = double_sum;
        DOUBLE_TYPE_INFO ->multiply = double_multiply;
        DOUBLE_TYPE_INFO ->print = double_print;
    }
    return DOUBLE_TYPE_INFO;
}