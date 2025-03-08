#include <stdio.h>
#include <assert.h>
#include<math.h>
#include"test.h"

#define EPS 1e-9



void test_double_sum(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6, 5.9, -6.1};

    Vector_errors operationResult;

    Vector* v1 = add_vector(Get_double_Type_info(), 4, a1, &operationResult);
    Vector* v2 = add_vector(Get_double_Type_info(), 4, a2, &operationResult);
    Vector* v_res_sum = add_vector(Get_double_Type_info(), 4, NULL, &operationResult);
    Vector* v_mult_numb_res = add_vector(Get_double_Type_info(), 4, NULL, &operationResult);

    assert(operationResult == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("проверка суммы\n");
    sum_vector(v1, v2, v_res_sum);
    double need_sum[] = {9.7, 1.6, 9.4, -1.3};
    for (int i = 0; i < 4; i++) {
        printf("Искомое значение: %lf, Полученное значение: %lf\n", need_sum[i], ((double*)v_res_sum->coord)[i]);
        assert(fabs(((double*)v_res_sum->coord)[i] - need_sum[i]) < EPS);
    }


    printf("проверка скалярного произведения\n");
    double multiply_res;
    scalar_multiplication(v1, v2, &multiply_res);
    double need_multiply = -4.91;
    printf("Искомое значение: %lf, Полученное значение: %lf\n", need_multiply, multiply_res);
    assert(fabs(need_multiply - multiply_res) < EPS);


    printf("проверка умножения вектора на число\n");
    double scalar = 4.0;
    multiply_by_a_number(v1, scalar, v_mult_numb_res);
    double need_mult_numb_res[] = {5.2, -8.0, 14.0, 19.2};
    for (int i = 0; i < 4; i++) {
        printf("Искомое значение: %lf, Полученное значение: %lf\n", need_mult_numb_res[i], ((double*)v_mult_numb_res->coord)[i]);
        assert(fabs(((double*)v_mult_numb_res->coord)[i] - need_mult_numb_res[i]) < EPS);
    }

    
    printf("проверка изменения координат вектора\n");
    double overwrite_coord[] = {1.0, -2.5, 4.33, 5.0};
    vector_overwrite(v1, &overwrite_coord);
    for (int i = 0; i < 4; i++) {
        printf("Искомое значение: %lf, Полученное значение: %lf\n", overwrite_coord[i], ((double*)v1->coord)[i]);
        assert(fabs(((double*)v1->coord)[i] - overwrite_coord[i]) < EPS);
    }

    free_vector(v1);
    free_vector(v2);
    free_vector(v_res_sum);
    free(&multiply_res);

}
void test_complex_sum(){
    Complex_number a1[] = {{-2.6, 3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    Complex_number a2[] = {{4.5, -9.6}, {4.7, 6.8}, {-6.8, 3.1}};
    Complex_number* multiply_res;

    Vector_errors operationResult = VECTOR_OPERATION_OK;

    Vector* v1 = add_vector(Get_complex_Type_info(), 3, a1, &operationResult);
    Vector* v2 = add_vector(Get_complex_Type_info(), 3, a2, &operationResult);
    Vector* v_res_sum = add_vector(Get_complex_Type_info(), 3, NULL, &operationResult);

    printf("Вектор 1: ");
    print_vector(v1);
    printf("\n");
    printf("Вектор 2: ");
    print_vector(v2);
    printf("\n");
    sum_vector(v1, v2, v_res_sum);
    printf("Сумма векторов: ");
    print_vector(v_res_sum);
    scalar_multiplication(v1, v2, &multiply_res);
    printf("\n");
    printf("Скалярное произведение векторов: ");
    complex_print(&multiply_res);

    free_vector(v1);
    free_vector(v2);
    free_vector(v_res_sum);

}

int main(){
    test_double_sum();
    test_complex_sum();
}