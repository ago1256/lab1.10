#ifndef COMPLEX_H
#define COMPLEX_H

#include "type_info.h"

typedef struct {
    double Re_part;
    double Im_part;

} Complex_number;

static Type_info* COMPLEX_TYPE_INFO = NULL;

void complex_sum(const void* arg1, const void* arg2, void* result);
void complex_multiply(const void* arg1, const void* arg2, void* result);
void complex_print(const void* data);

Type_info* Get_complex_type_info();

#endif 

