#include <stdio.h>
#include <stdlib.h>
#include"vector.h"
#include"array.h"
#include"func.c"


void enter() {
    Array A;
    printf("Введите количество векторов\n");
    int count;
    scanf("%d", &count);
    init_array(&A, count);
    for (int i = 0; i < count; i++) {
        printf("Введите тип переменных: 1 - вещественное, 2 - комплексное\n");
        int type;
        scanf("%d", &type);
        Vector *vector = init_vector(type);
        if (type == 1) { 
            printf("Введите координаты вектора %d в формате x y z\n", i + 1);
            float *x = malloc(sizeof(float));
            float *y = malloc(sizeof(float));
            float *z = malloc(sizeof(float));
            scanf("%f", x);
            scanf("%f", y);
            scanf("%f", z);
            add_vector(vector, x, y, z);
        } else if (type == 2) {
            printf("Введите координаты вектора %d в формате Re.x Im.x Re.y Im.y Re.z Im.z\n", i + 1);
            Complex_number *x = malloc(sizeof(Complex_number));
            Complex_number *y = malloc(sizeof(Complex_number));
            Complex_number *z = malloc(sizeof(Complex_number));
            scanf("%f %f", &x->Re_part, &x->Im_part);
            scanf("%f %f", &y->Re_part, &y->Im_part);
            scanf("%f %f", &z->Re_part, &z->Im_part);
            add_vector(vector, x, y, z);
        }
        add_element(&A, vector);
    }
    print_array(&A, count);
    printf("Введите операцию, которая будет выполнена с векторами:\n \
            1 - сложение 2х векторов,\n \
            2 - скалярное умножение 2х векторов\n \
            3 - векторное умножение 2х векторов\n");

    int type_operation;
    scanf("%d", &type_operation);
    printf("Введите индексы векторов с которыми хотите провести операцию\n");
    int ind1;
    int ind2;
    scanf("%d %d", &ind1, &ind2);
    Vector *v1 = A.data[ind1-1];
    Vector *v2 = A.data[ind2-1];

    if (v1->type != v2->type){
        printf("Ошибка:разные типы данных");
    }
    else{
    if(type_operation==1){
        Vector *v_res = init_vector(v1->type);
        summ_vector(v1, v2, v_res, v_res->type);
        print_vector(v_res);
        free_vector(v_res);
    }
    if(type_operation==2){
        void *res;
        scalar_multiplication(v1, v2, &res, v1->type);
        if (v1->type==1){
            printf("%f\n", *(float *)res);
            free(res);
        }
        if(v1->type==2){
            Complex_number *res_complex = (Complex_number *)res;
            printf("%f +%fi\n", res_complex->Re_part, res_complex->Im_part);
            free(res);
        }
    }
    if(type_operation==3){
        Vector *v_res = init_vector(v1->type);
        vector_multiplication(v1, v2, v_res, v_res->type);
        print_vector(v_res);
        free_vector(v_res);
    }
}
    free_array(&A);
}


int main() {
    enter();
    return 0;
}

