#include"vector_errors.h"

int error_detection(Vector_errors operation_result) {
    if (operation_result != VECTOR_OPERATION_OK) {
        switch (operation_result) {
            case MEMORY_ALLOCATION_FAILED:
                fprintf(stderr, "Ошибка: Не удалось выделить память.\n");
                return 1;
            case VECTOR_NOT_DEFINED:
                fprintf(stderr, "Ошибка: Вектор не определен.\n");
                return 1;
            case OPERATION_NOT_DEFINED:
                fprintf(stderr, "Ошибка: Операция не определена.\n");
                return 1;
            case INCOMPATIBLE_VECTOR_TYPES:
                fprintf(stderr, "Ошибка: Несовместимые типы векторов.\n");
                return 1; 
            case DIFFERENT_LENGHT_VECTORS:
                fprintf(stderr, "Ошибка: Разные длины векторов.\n");
                return 1;
            default:
                fprintf(stderr, "Неизвестная ошибка.\n");
                return 1;
        }
    }
    return 0;
}