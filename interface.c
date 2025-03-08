#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"interface.h"




void enter() {
    int vector_count;
    printf("Введите количество векторов: ");
    scanf("%d", &vector_count);

    Vector** vectors = malloc(vector_count * sizeof(Vector*));
    for (int i = 0; i < vector_count; i++) {
        printf("Введите тип вектора №%d (1-вещественное, 2-комплексное)\n", i + 1);
        int type;
        scanf("%d", &type);
        printf("Введите длину(количество координат) вектора №%d\n", i + 1);
        int count;
        scanf("%d", &count);
        Type_info* type_info = NULL;
        if(type==1){
            type_info = Get_double_Type_info();
        }
        if(type==2){
            type_info = Get_complex_Type_info();
        }

        Vector_errors operation_result;
        vectors[i] = add_vector(type_info, count, NULL, &operation_result);
        
        printf("Введите координаты вектора №%d\n", i + 1);
        for (int j = 0; j < count; j++) {
            if (type == 1) {
                scanf("%lf", (double*)((char*)vectors[i]->coord + j * type_info->size));
            } else if (type == 2) {
                Complex_number* z;
                scanf("%lf %lf", z->Re_part, z->Im_part);
                memcpy((char*)vectors[i]->coord + j * type_info->size, &z, type_info->size);
            }
        }
        print_vector(vectors[i]);///////////////////////////////////////////////////////
    }

    while (1) {
        printf("Выберите операцию: 1-векторная сумма, 2-скалярное произведение, 3-умножение координат вектора на скаляр\n \
             4- изменение координат вектора, 5-выход\n");
        int operation_type;
        scanf("%d", &operation_type);
        Vector_errors operation_result;


        switch (operation_type) {
            case 1: { 
                printf("Выберите индексы векторов: ");
                int index1, index2;
                scanf("%d %d", &index1, &index2);
                index1-=1;
                index2-=1;
                Vector* v_sum_res = add_vector(vectors[index1]->type_info, vectors[index1]->v_count, NULL, &operation_result);
                sum_vector(vectors[index1], vectors[index2], v_sum_res);
                print_vector(v_sum_res);
                free_vector(v_sum_res);
                break;
            }
            case 2: {
                printf("Выберите индексы векторов: ");
                int index1, index2;
                scanf("%d %d", &index1, &index2);
                index1-=1;
                index2-=1;
                void* multiply_res = malloc(sizeof(double)*2);
                scalar_multiplication(vectors[index1], vectors[index2], multiply_res);
                vectors[index1]->type_info->print(multiply_res);
                free(multiply_res);
                break;
            }
            case 3: {
                printf("Выберите индекс вектора: ");
                int index1;
                scanf("%d", &index1);
                index1-=1;
                double k;
                printf("Введите скаляр: ");
                scanf("%lf", &k);
                Vector* v_mult_numb_res= add_vector(vectors[index1]->type_info, vectors[index1]->v_count, NULL, &operation_result);
                multiply_by_a_number(vectors[index1], k, v_mult_numb_res);
                print_vector(v_mult_numb_res);
                free(v_mult_numb_res);
                break;
        
            }
            case 4: { 
                printf("Выберите индекс вектора: ");
                int index1;
                scanf("%d", &index1);
                index1-=1;
                printf("Введите новые координаты для вектора %d:\n", index1+1);
                void* new_coord = malloc(vectors[index1]->v_count * sizeof(vectors[index1]->type_info->size));
                
                for (int i = 0; i < vectors[index1]->v_count; i++) {
                    if (vectors[index1]->type_info->size == sizeof(double)) {
                        scanf("%lf", (double*)((char*)new_coord + i * sizeof(double)));
                    } else if (vectors[index1]->type_info->size == sizeof(Complex_number)) {
                        Complex_number z;
                        scanf("%lf %lf", &z.Re_part, &z.Im_part);
                        memcpy((char*)new_coord + i * sizeof(Complex_number), &z, sizeof(Complex_number));
                    }
                }
                vector_overwrite(vectors[index1], new_coord);
                print_vector(vectors[index1]);
                break;
            }
            case 5:{
                return 0;
            }
            default:
                printf("Некорректный выбор операции.\n");
               
        }
    }

    for (int i = 0; i < vector_count; i++) {
        free_vector(vectors[i]);
    }
    free(vectors);
}

/*void enter() {
    printf("Введите тип вектора №1(1-вещественное, 2-комплексное)\n");
    int type_1;
    scanf("%d", &type_1);
    printf("Введите длину(количество координат) вектора №1\n");
    int count_1;
    scanf("%d", &count_1);
    Type_info* type_info_1 = NULL;
    if(type_1==1){
        type_info_1 = Get_double_Type_info();
    }
    else if(type_1==2){
        type_info_1 = Get_complex_Type_info();
    }
    Vector_errors operation_result;
    Vector* v1 = add_vector(type_info_1, count_1, NULL, &operation_result);
    printf("Введите координаты вектора №1\n");
    for(int i=0; i<count_1; i++){
        if(type_1==1){
            scanf("%lf", (double*)((char*)v1->coord+ i * type_info_1->size));
        }
        else if(type_1==2){
            Complex_number *z;
            scanf("%lf %lf", z->Re_part, z->Im_part);
            memcpy((char*)v1->coord + i * type_info_1->size, z, type_info_1->size);
        }
    }

    printf("Введите тип вектора №2(1-вещественное, 2-комплексное)\n");
    int type_2;
    Type_info* type_info_2;
    scanf("%d", &type_2);
    printf("Введите длину(количество координат) вектора №2\n");
    int count_2;
    scanf("%d", &count_2);
    if(type_2==1){
        type_info_2 = Get_double_Type_info();
    }
    if(type_2==2){
        type_info_2 = Get_complex_Type_info();
    }

    Vector* v2 = add_vector(type_info_2, count_2, NULL, &operation_result);
    printf("Введите координаты вектора №2\n");
    for(int i=0; i<count_2; i++){
        if(type_2==1){
            scanf("%lf", (double*)((char*)v2->coord + i * type_info_2->size));
        }
        if(type_2==2){
            Complex_number *z;
            scanf("%lf %lf", z->Re_part,z->Im_part);
            memcpy((char*)v2->coord + i * type_info_2->size, z, type_info_2->size);
        }
    }

    print_vector(v1);
    print_vector(v2);
    printf("Выберите операцию над векторами: 1-векторная сумма, 2-скалярное произведение\n");
    int operation_type;
    scanf("%d", operation_type);
    if (operation_type==1){
        Vector* v_sum_res = add_vector(v1->type_info, v1->v_count, NULL, &operation_result);
        sum_vector(v1, v2,v_sum_res);
        print_vector(v_sum_res);
    }
    if (operation_type==2){
        void* multiply_res;
        scalar_multiplication(v1, v2, multiply_res);
        v1->type_info->print(multiply_res);
    }


}


*/
