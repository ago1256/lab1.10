#ifndef DOUBLE_H
#define DOUBLE_H

#include "type_info.h"

static Type_info* DOUBLE_TYPE_INFO = NULL;

void double_sum(const void* arg1, const void* arg2, void* result);
void fdouble_multiply(const void* arg1, const void* arg2, void* result);
void double_print(const void* data);
Type_info* Get_double_Type_info();

#endif


