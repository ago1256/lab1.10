#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"interface.h"
#include"vector_errors.h"


int enter() {

    size_t vector_count;
    printf("Введите количество векторов: ");
    scanf("%lu", &vector_count);
    Vector_errors operation_result;

    Vector** vectors = malloc(vector_count * sizeof(Vector*));
    for (int i = 0; i < vector_count; i++) {
        printf("Введите тип вектора № %d (1-вещественное, 2-комплексное)\n", i + 1);
        int type;
        scanf("%d", &type);
        printf("Введите длину(количество координат) вектора №%d\n", i + 1);
        size_t count;
        scanf("%lu", &count);
        Type_info* type_info = NULL;
        if(type==1){
            type_info = Get_double_Type_info();
        }
        if(type==2){
            type_info = Get_complex_Type_info();
        }


        printf("Введите координаты вектора №%d\n", i + 1);
        void* coord = malloc(count *type_info->size);

        for (int j = 0; j < count; j++) {
            if (type == 1) {
                scanf("%lf", (double*)((char*)coord + j * type_info->size));
            } else if (type == 2) {
                Complex_number* z = (Complex_number*)((char*)coord + j * type_info->size);
                scanf("%lf %lf", &z->Re_part, &z->Im_part);
            }
        }
        vectors[i] = add_vector(type_info, count, coord, &operation_result);
        printf("Вектор №%d: ", i + 1);
        print_vector(vectors[i]);
    }

    while (1) {
        printf("\nВыберите операцию:\n");
        printf(" 1 - векторная сумма\n");
        printf(" 2 - скалярное произведение\n");
        printf(" 3 - умножение координат вектора на скаляр\n");
        printf(" 4 - изменение координат вектора\n");
        printf(" 5 - вывести массив векторов\n");
        printf(" 6 - выход\n");
        int operation_type;
        scanf("%d", &operation_type);


        switch (operation_type) {
            case 1: { 
                printf("Выберите индексы векторов: ");
                int index1, index2;
                scanf("%d %d", &index1, &index2);
                index1-=1;
                index2-=1;
                Vector* v_sum_res = add_vector(vectors[index1]->type_info, vectors[index1]->v_count, NULL, &operation_result);
                if(error_detection(sum_vector(vectors[index1], vectors[index2], v_sum_res))){
                    break;
                }
                else{
                    printf("Сумма векторов %d и %d: ", index1+1, index2+1);
                    print_vector(v_sum_res);
                }
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
                if(error_detection(scalar_multiplication(vectors[index1], vectors[index2], multiply_res))){
                    break;
                }
                else{
                    printf("Скалярное произведение векторов %d и %d: ", index1+1, index2+1);
                    vectors[index1]->type_info->print(multiply_res);
                }
                
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
                if(error_detection(multiply_by_a_number(vectors[index1], k, v_mult_numb_res))){
                    break;
                }
                else{
                    printf("Вектор %d умноженный на %lf: ", index1+1, k);
                    print_vector(v_mult_numb_res);
                }
                free(v_mult_numb_res);
                break;
        
            }
            case 4: { 
                printf("Выберите индекс вектора: ");
                int index1;
                scanf("%d", &index1);
                index1-=1;
                printf("Введите тип вектора № %d (1-вещественное, 2-комплексное)\n", index1+1);
                int new_type;
                scanf("%d", &new_type);
                printf("Введите длину(количество координат) вектора №%d\n", index1+1);
                size_t new_count;
                scanf("%lu", &new_count);
                Type_info* new_type_info = NULL;
                if(new_type==1){
                    new_type_info = Get_double_Type_info();
                }
                if(new_type==2){
                    new_type_info = Get_complex_Type_info();
                }
                printf("Введите новые координаты для вектора %d:\n", index1+1);
                void* new_coord = malloc(vectors[index1]->v_count * sizeof(vectors[index1]->type_info->size));
                
                for (int j = 0; j < new_count; j++) {
                    if (new_type == 1) {
                        scanf("%lf", (double*)((char*)new_coord + j * new_type_info->size));
                    } else if (new_type == 2) {
                        Complex_number* z = (Complex_number*)((char*)new_coord + j * new_type_info->size);
                        scanf("%lf %lf", &z->Re_part, &z->Im_part);
                    }
                }
                if(error_detection(vector_overwrite(new_type_info, vectors[index1], new_count, new_coord))){
                    break;
                }
                else{
                    printf("Измененный вектор %d: ", index1+1);
                    print_vector(vectors[index1]);
                }
                free(new_coord);
                break;

            }
            case 5:{
                for(int j=0; j<vector_count; j++){
                    print_vector(vectors[j]);
                }
                break;
            }
            case 6:{
                return 0;
            }
            default:
                printf("Некорректный выбор операции.\n");
                break;
               
        }
    }

    for (int i = 0; i < vector_count; i++) {
        free_vector(vectors[i]);
    }
    free(vectors);
}

