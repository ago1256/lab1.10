#include <stdio.h>
#include <assert.h>
#include<math.h>
#include"test.h"
#include"vector_errors.h"


#define EPS 1e-9

void test_double_sum(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6, 5.9, -6.1};

    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_double_type_info(), 4, a1, &operation_result);
    Vector* v2 = add_vector(Get_double_type_info(), 4, a2, &operation_result);
    Vector* v_res_sum = add_vector(Get_double_type_info(), 4, NULL, &operation_result);
    Vector* v_mult_numb_res = add_vector(Get_double_type_info(), 4, NULL, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("проверка суммы\n");
    sum_vector(v1, v2, v_res_sum);
    double need_sum[] = {9.7, 1.6, 9.4, -1.3};
    for (int i = 0; i < 4; i++) {
        printf("Искомое значение: %lf, Полученное значение: %lf\n", need_sum[i], ((double*)v_res_sum->coord)[i]);
        assert(fabs(((double*)v_res_sum->coord)[i] - need_sum[i]) < EPS);
    }
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res_sum);
}

void test_double_scalar_multiply(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6, 5.9, -6.1};

    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_double_type_info(), 4, a1, &operation_result);
    Vector* v2 = add_vector(Get_double_type_info(), 4, a2, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL);
    printf("проверка скалярного произведения\n");
    double multiply_res;
    scalar_multiplication(v1, v2, &multiply_res);
    double need_multiply = -4.91;
    printf("Искомое значение: %lf, Полученное значение: %lf\n", need_multiply, multiply_res);
    assert(fabs(need_multiply - multiply_res) < EPS);
    free_vector(v1);
    free_vector(v2);

}

void test_double_multiply_by_a_number(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};

    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_double_type_info(), 4, a1, &operation_result);
    Vector* v_mult_numb_res = add_vector(Get_double_type_info(), 4, NULL, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL);

    printf("проверка умножения вектора на число\n");
    double scalar_double = 4;
    void* scalar = &scalar_double;
    multiply_by_a_number(v1, scalar, v_mult_numb_res);
    double need_mult_numb_res[] = {5.2, -8.0, 14.0, 19.2};
    for (int i = 0; i < 4; i++) {
        printf("Искомое значение: %lf, Полученное значение: %lf\n", need_mult_numb_res[i], ((double*)v_mult_numb_res->coord)[i]);
        assert(fabs(((double*)v_mult_numb_res->coord)[i] - need_mult_numb_res[i]) < EPS);
    }
    free_vector(v1);
    free_vector(v_mult_numb_res);
}

void test_double_vector_overwrite(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};

    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_double_type_info(), 4, a1, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL);
    printf("проверка изменения координат вектора\n");
    double overwrite_coord[] = {1.0, -2.5, 4.33, 5.0};
    size_t count=5;
    vector_overwrite(Get_double_type_info(),v1, &count, &overwrite_coord);
    for (int i = 0; i < 4; i++) {
        printf("Искомое значение: %lf, Полученное значение: %lf\n", overwrite_coord[i], ((double*)v1->coord)[i]);
        assert(fabs(((double*)v1->coord)[i] - overwrite_coord[i]) < EPS);
    }
    free_vector(v1);
}


void test_complex_sum(){
    Complex_number a1[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    Complex_number a2[] = {{1.0, -9.6}, {4.7, 6.8}, {-6.8, 3.1}};
    
    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_complex_type_info(), 3, a1, &operation_result);
    Vector* v2 = add_vector(Get_complex_type_info(), 3, a2, &operation_result);
    Vector* v_res_sum = add_vector(Get_complex_type_info(), 3, NULL, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("проверка суммы\n");
    sum_vector(v1, v2, v_res_sum);
    print_vector(v_res_sum);
    Complex_number need_sum[] = {{3.0, -12.6}, {5.9, -1.7}, {-11.3, 1.2}};
    Complex_number* res_coord = (Complex_number*) v_res_sum->coord;
    for (int i=0; i<3; i++) {
        printf("Искомое значение:");
        v1->type_info->print(&need_sum[i]);
        printf(" Полученное значение: ");
        v_res_sum->type_info->print((char*)v_res_sum->coord + i * v_res_sum->type_info->size);
        printf("\n");
        assert(fabs(res_coord[i].Re_part - need_sum[i].Re_part) < EPS);
        assert(fabs(res_coord[i].Im_part - need_sum[i].Im_part) < EPS);
        }
        free_vector(v1);
        free_vector(v2);
        free_vector(v_res_sum);
}
    
void test_complex_scalar_multiply(){
    Complex_number a1[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};
    Complex_number a2[] = {{1.0, -9.6}, {4.7, 6.8}, {-6.8, 3.1}};

    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_complex_type_info(), 3, a1, &operation_result);
    Vector* v2 = add_vector(Get_complex_type_info(), 3, a2, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL);

    printf("проверка скалярного произведения\n");
    Complex_number multiply_res;
    scalar_multiplication(v1, v2, &multiply_res);
    Complex_number need_multiply = {73.13, -55.02};
    printf("Искомое значение: %lf+%lfi, Полученное значение: %lf+%lfi\n", need_multiply.Re_part, need_multiply.Im_part,\
         multiply_res.Re_part, multiply_res.Im_part);
    assert(fabs(multiply_res.Re_part - need_multiply.Re_part) < EPS);
    assert(fabs(multiply_res.Im_part - need_multiply.Im_part) < EPS);
    free_vector(v1);
    free_vector(v2);
}

void test_complex_multiply_by_a_number(){
     Complex_number a1[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};

    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_complex_type_info(), 3, a1, &operation_result);
    Vector* v_mult_numb_res = add_vector(Get_complex_type_info(), 3, NULL, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL);

    printf("проверка умножения вектора на число\n");
    Complex_number scalar_complex = {3, 0};
    void* scalar = &scalar_complex;
    multiply_by_a_number(v1, scalar, v_mult_numb_res);
    Complex_number need_mult_numb_res[] = {{6.0, -9.0}, {3.6, -25.5},{-13.5, -5.7}};
    Complex_number* res_coord = (Complex_number*)  v_mult_numb_res->coord;
    for (int i=0; i<3; i++) {
        printf("Искомое значение:");
        v1->type_info->print(&need_mult_numb_res[i]);
        printf(" Полученное значение: ");
        v_mult_numb_res->type_info->print((char*)v_mult_numb_res->coord + i * v_mult_numb_res->type_info->size);
        printf("\n");
        assert(fabs(res_coord[i].Re_part - need_mult_numb_res[i].Re_part) < EPS);
        assert(fabs(res_coord[i].Im_part - need_mult_numb_res[i].Im_part) < EPS);
        }
}

void test_complex_vector_overwrite(){
    Complex_number a1[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};

    Vector_errors operation_result;
    Vector* v1 = add_vector(Get_complex_type_info(), 3, a1, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL);

    printf("проверка изменения координат вектора\n");
    Complex_number need_overwrite_coord[] = {{3.0, -12.6}, {5.9, -1.7}, {-11.3, 1.2}};
    size_t count = 3;
    vector_overwrite(Get_complex_type_info(), v1, &count, &need_overwrite_coord);
    Complex_number* res_overwrite_coord = (Complex_number*) v1->coord;
    for (int i=0; i<3; i++) {
        printf("Искомое значение:");
        v1->type_info->print(&need_overwrite_coord[i]);
        printf(" Полученное значение: ");
        v1->type_info->print((char*)v1->coord + i * v1->type_info->size);
        printf("\n");
        assert(fabs(res_overwrite_coord[i].Re_part - need_overwrite_coord[i].Re_part) < EPS);
        assert(fabs(res_overwrite_coord[i].Im_part - need_overwrite_coord[i].Im_part) < EPS);
        }
    free_vector(v1);
    }



void test_empty_vector() {
    Vector_errors operation_result;
    Vector* v = add_vector(Get_double_type_info(), 0, 0, &operation_result);
    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v != NULL);
    assert(v->v_count == 0);
    free_vector(v);
}

void test_error_different_lenght(){
    double a1[] = {1.3, -2.0, 3.5, 4.8};
    double a2[] = {8.4, 3.6};

    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_double_type_info(), 4, a1, &operation_result);
    Vector* v2 = add_vector(Get_double_type_info(), 2, a2, &operation_result);
    Vector* v_res_sum = add_vector(Get_double_type_info(), 2, NULL, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("проверка ошибки: разные длины векторов\n");

    error_detection(sum_vector(v1, v2, v_res_sum));
    assert(sum_vector(v1, v2, v_res_sum) == DIFFERENT_LENGHT_VECTORS);
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res_sum);

}

void test_error_different_types(){
    double a1[] = {1.3, -2.0, 3.5};
    Complex_number a2[] = {{2.0, -3.0}, {1.2, -8.5}, {-4.5, -1.9}};

    Vector_errors operation_result;

    Vector* v1 = add_vector(Get_double_type_info(), 4, a1, &operation_result);
    Vector* v2 = add_vector(Get_complex_type_info(), 3, a2, &operation_result);
    Vector* v_res_sum = add_vector(Get_complex_type_info(), 3, NULL, &operation_result);

    assert(operation_result == VECTOR_OPERATION_OK);
    assert(v1 != NULL && v2 != NULL && v_res_sum  != NULL);

    printf("проверка ошибки: разные типы векторов\n");

    error_detection(sum_vector(v1, v2, v_res_sum));
    assert(sum_vector(v1, v2, v_res_sum) == INCOMPATIBLE_VECTOR_TYPES);
    free_vector(v1);
    free_vector(v2);
    free_vector(v_res_sum);

}
int main(){
    test_double_sum();
    test_double_scalar_multiply();
    test_double_multiply_by_a_number();
    test_double_vector_overwrite();
    test_complex_sum();
    test_complex_scalar_multiply();
    test_complex_multiply_by_a_number();
    test_complex_vector_overwrite();
    test_empty_vector();
    test_error_different_lenght();
    test_error_different_types();
}