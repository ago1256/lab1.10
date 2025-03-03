#ifndef FLOAT_H
#define FLOAT_H

#include "type_info.h"

static Type_info* FLOAT_TYPE_INFO = NULL;

void float_sum(const void* arg1, const void* arg2, void* result);
void float_multiply(const void* arg1, const void* arg2, void* result);
void float_print(const void* data);
Type_info* Get_float_Type_info();

#endif


