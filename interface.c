#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"interface.h"
#include"vector_errors.h"


int enter() {

    size_t vector_count = 0;
    Vector_errors operation_result;
    Vector** vectors = NULL;

    while (1) {
        //getchar();
      //  system("cls");
        printf("\nВыберите операцию:\n");
        printf(" 1 - добавить вектор в массив\n");
        printf(" 2 - векторная сумма\n");
        printf(" 3 - скалярное произведение\n");
        printf(" 4 - умножение координат вектора на число\n");
        printf(" 5 - изменение вектора\n");
        printf(" 6 - вывести массив векторов\n");
        printf(" 7 - удалить вектор из массива по индексу\n");
        printf(" 8 - выход\n");
        int operation_type;
        scanf("%d", &operation_type);

        switch (operation_type) {
            case 1:{
                printf("Введите тип вектора № %d (1-вещественное, 2-комплексное)\n", vector_count+1);
                int type;
                scanf("%d", &type);
                printf("Введите длину(количество координат) вектора №%d\n", vector_count+1);
                size_t count;
                scanf("%lu", &count);
                Type_info* type_info = NULL;
                if(type==1){
                    type_info = Get_double_type_info();
                }
                if(type==2){
                    type_info = Get_complex_type_info();
                }
                printf("Введите координаты вектора №%d\n", vector_count+1);
                void* coord = malloc(count *type_info->size);
                for (int j = 0; j < count; j++) {
                    if (type == 1) {
                        scanf("%lf", (double*)((char*)coord + j * type_info->size));
                    } else if (type == 2) {
                        Complex_number* z = (Complex_number*)((char*)coord + j * type_info->size);
                        scanf("%lf %lf", &z->Re_part, &z->Im_part);
                    }
                }
                Vector* new_vector = add_vector(type_info, count, coord, &operation_result);
                vectors = add_vector_to_array(vectors, &vector_count,new_vector);
                printf("Добавлен вектор №%d: ", vector_count);
                print_vector(vectors[vector_count-1]);
                break;
            }
            
            case 2: { 
                printf("Выберите индексы векторов: ");
                int index1, index2;
                scanf("%d %d", &index1, &index2);
                index1-=1;
                index2-=1;
                Vector* v_sum_res = add_vector(vectors[index1]->type_info, vectors[index1]->v_count, NULL, &operation_result);
                if(error_detection(sum_vector(vectors[index1], vectors[index2], v_sum_res)) != VECTOR_OPERATION_OK){
                    break;
                }
                else{
                    printf("Сумма векторов %d и %d: ", index1+1, index2+1);
                    print_vector(v_sum_res);
                    printf("Хотите добавить вектор суммы в массив векторов? 1-да, 2-нет\n");
                    int flag_add_sum;
                    scanf("%d",&flag_add_sum);
                    if(flag_add_sum==1){
                        add_vector_to_array(vectors, &vector_count, v_sum_res);
                    }
                    if(flag_add_sum==2){
                        free_vector(v_sum_res);
                    }
                }
                break;
            }
            case 3: {
                printf("Выберите индексы векторов: ");
                int index1, index2;
                scanf("%d %d", &index1, &index2);
                index1-=1;
                index2-=1;
                void* multiply_res = malloc(sizeof(double)*2);
                if(error_detection(scalar_multiplication(vectors[index1], vectors[index2], multiply_res))!= VECTOR_OPERATION_OK){
                    break;
                }
                else{
                    printf("Скалярное произведение векторов %d и %d: ", index1+1, index2+1);
                    vectors[index1]->type_info->print(multiply_res);
                }
                
                free(multiply_res);
                break;
            }
            case 4: {
                printf("Выберите индекс вектора: ");
                int index1;
                scanf("%d", &index1);
                index1-=1;
                printf("Введите скаляр: ");
                void* k = NULL;
                if(vectors[index1]->type_info == Get_double_type_info()){
                double* k_double = malloc(sizeof(double));
                scanf("%lf", k_double);
                k = k_double;
                }
                if(vectors[index1]->type_info == Get_complex_type_info()){
                    Complex_number* k_complex = malloc(sizeof(Complex_number));
                    scanf("%lf %lf", &k_complex->Re_part, &k_complex->Im_part);
                    k = k_complex;
                }
                Vector* v_mult_numb_res= add_vector(vectors[index1]->type_info, vectors[index1]->v_count, NULL, &operation_result);
                if(error_detection(multiply_by_a_number(vectors[index1], k, v_mult_numb_res))!= VECTOR_OPERATION_OK){
                    break;
                }
                else{
                    printf("Вектор %d умноженный на ", index1+1);
                    v_mult_numb_res->type_info->print(k);
                    printf(": ");
                    print_vector(v_mult_numb_res);
                }
                free(v_mult_numb_res);
                break;
        
            }
            case 5: { 
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
                    new_type_info = Get_double_type_info();
                }
                if(new_type==2){
                    new_type_info = Get_complex_type_info();
                }
                printf("Введите новые координаты для вектора %d:\n", index1+1);
                void* new_coord = malloc(new_count * new_type_info->size);
                
                for (int j = 0; j < new_count; j++) {
                    if (new_type == 1) {
                        scanf("%lf", (double*)((char*)new_coord + j * new_type_info->size));
                    } else if (new_type == 2) {
                        Complex_number* z = (Complex_number*)((char*)new_coord + j * new_type_info->size);
                        scanf("%lf %lf", &z->Re_part, &z->Im_part);
                    }
                }
                if(error_detection(vector_overwrite(new_type_info, vectors[index1], &new_count, new_coord))!= VECTOR_OPERATION_OK){
                    break;
                }
                else{
                    printf("Измененный вектор %d: ", index1+1);
                    print_vector(vectors[index1]);
                }
                free(new_coord);
                break;

            }
            case 6:{
                for(int j=0; j<vector_count; j++){
                    print_vector(vectors[j]);
                }
                break;
            }
            
            case 7:{
                printf("Выберите индекс вектора: ");
                int index1;
                scanf("%d", &index1);
                index1-=1;
                vectors = remove_vector_from_array(vectors, &vector_count, index1);
                break;
            }
            case 8:{
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

