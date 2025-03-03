#ifndef COMPLEX_H
#define COMPLEX_H

#include "type_info.h"

typedef struct {
    float Re_part;
    float Im_part;

} Complex_number;

static Type_info* COMPLEX_TYPE_INFO = NULL;

void complex_sum(const void* arg1, const void* arg2, void* result);
void complex_multiply(const void* arg1, const void* arg2, void* result);
void complex_print(const void* data);

Type_info* Get_complex_Type_info();

#endif 

