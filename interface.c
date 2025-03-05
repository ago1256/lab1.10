#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"interface.h"


void enter() {
    printf("Введите тип вектора №1(1-вещественное, 2-комплексное)\n");
    int type_1;
    scanf("%d", &type_1);
    printf("Введите длину(количество координат) вектора №1\n");
    int count_1;
    scanf("%d", &count_1);
    Type_info* type_info_1 = NULL;
    if(type_1==1){
        type_info_1 = Get_float_Type_info();
    }
    else if(type_1==2){
        type_info_1 = Get_complex_Type_info();
    }
    Vector_errors operation_result_1;
    Vector* v1 = add_vector(type_info_1, count_1, NULL, &operation_result_1);
    printf("Введите координаты вектора №1\n");
    for(int i=0; i<count_1; i++){
        if(type_1==1){
            scanf("%f", (float*)((char*)v1->coord+ i * type_info_1->size));
        }
        else if(type_1==2){
            Complex_number *z;
            scanf("%f %f", z->Re_part, z->Im_part);
            memcpy((char*)v1->coord + i * type_info_1->size, z, type_info_1->size);
        }
    }

print_vector(v1);


printf("Введите тип вектора №2(1-вещественное, 2-комплексное)\n");
int type_2;
Type_info* type_info_2;
scanf("%d", &type_2);
printf("Введите длину(количество координат) вектора №2\n");
int count_2;
scanf("%d", &count_2);
if(type_2==1){
    type_info_2 = Get_float_Type_info();
}
if(type_2==2){
    type_info_2 = Get_complex_Type_info();
}
Vector_errors operation_result_2;
Vector* v2 = add_vector(type_info_2, count_2, NULL, &operation_result_2);
printf("Введите координаты вектора №2\n");
for(int i=0; i<count_2; i++){
    if(type_2==1){
        scanf("%f", (float*)((char*)v2->coord + i * type_info_2->size));
    }
    if(type_2==2){
        Complex_number *z;
        scanf("%f %f", z->Re_part,z->Im_part);
        memcpy((char*)v2->coord + i * type_info_2->size, z, type_info_2->size);
    }
}
print_vector(v2);
}



