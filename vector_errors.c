#include"vector_errors.h"

Vector_errors error_detection(Vector_errors operation_result) {
    if (operation_result != VECTOR_OPERATION_OK) {
        switch (operation_result) {
            case MEMORY_ALLOCATION_FAILED:
                fprintf(stderr, "Ошибка: Не удалось выделить память.\n");
                return MEMORY_ALLOCATION_FAILED;
            case VECTOR_NOT_DEFINED:
                fprintf(stderr, "Ошибка: Вектор не определен.\n");
                return VECTOR_NOT_DEFINED;
            case OPERATION_NOT_DEFINED:
                fprintf(stderr, "Ошибка: Операция не определена.\n");
                return OPERATION_NOT_DEFINED;
            case INCOMPATIBLE_VECTOR_TYPES:
                fprintf(stderr, "Ошибка: Несовместимые типы векторов.\n");
                return INCOMPATIBLE_VECTOR_TYPES; 
            case DIFFERENT_LENGHT_VECTORS:
                fprintf(stderr, "Ошибка: Разные длины векторов.\n");
                return DIFFERENT_LENGHT_VECTORS;
            default:
                fprintf(stderr, "Неизвестная ошибка.\n");
                return UNKNOWN_ERROR;
        }
    }
    return VECTOR_OPERATION_OK;
}