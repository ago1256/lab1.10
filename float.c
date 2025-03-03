#include "float.h"

void float_sum(const void* arg1, const void* arg2, void* result) {
    *(float*)result = *(float*)arg1 + *(float*)arg2;
}

void float_multiply(const void* arg1, const void* arg2, void* result) {
    *(float*)result = *(float*)arg1 * *(float*)arg2;
}

void float_print(const void* data) {
    printf("%f", *(const float*)data);
}

Type_info* Get_float_Type_info() {
    if (FLOAT_TYPE_INFO == NULL) {
        FLOAT_TYPE_INFO = (Type_info*)malloc(sizeof(Type_info));
        FLOAT_TYPE_INFO ->size = sizeof(float);
        FLOAT_TYPE_INFO ->sum = float_sum;
        FLOAT_TYPE_INFO ->multiply = float_multiply;
        FLOAT_TYPE_INFO ->print = float_print;
    }
    return FLOAT_TYPE_INFO;
}