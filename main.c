#include "vector.h"
#include "interface.h"

int main(){
    enter();
}

//не хочу изначально задавать кол-во векторов, хочу добавлять / удалять их по желанию +
//возникла ошибка в ситуации:
//перезаписал вещественный вектор на новый вещественный размером 3 с эл-нтами {1, 2, 3} +-

/*
if(error_detection(sum_vector(vectors[index1], vectors[index2], v_sum_res))){
                    break;
                }

интуитивно непонятное условие, если бы сравнивалось с OPERATION_OK - было бы лучше+
*/

//Vector_errors operation_result; - объявлено несколько раз +

//писать названия в одном стиле: some_name или someName +
//type info поменять с маленькой ьуквы +