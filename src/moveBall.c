#include "moveBall.h"

void moveBall(int *ball1_x, int *ball1_y, int *vector_X, int *vector_Y, 
    const int *rocket_1_Y, const int *rocket_2_Y) {                   // Функция отвечает за передвежение мяча  
 if (*ball1_y == 1 || *ball1_y == 27 - 2) {                           // Смотрим на положение мяча по координате Y.
  *vector_Y = -(*vector_Y);                                           // Меняем вектор направления на противоположный
 }
 if (*ball1_x == 2 + 1 &&                                             // Сравниваем положение ракетки 1 и мяча, чтобы в случае столкновения менялся
  (*ball1_y == *rocket_1_Y - 1 ||*ball1_y == *rocket_1_Y ||           // вектор направления на противоположный
   *ball1_y == *rocket_1_Y + 1)) {
  *vector_X = -(*vector_X);
 }
 if (*ball1_x == 79 - 1 &&                                            // Сравниваем положение ракетки 2 и мяча, чтобы в случае столкновения менялся
  (*ball1_y == *rocket_2_Y - 1 || *ball1_y == *rocket_2_Y ||          // вектор направления на противоположный
  *ball1_y == *rocket_2_Y + 1)) {
  *vector_X = -(*vector_X);
 }

 *ball1_y += *vector_Y;                                               // Складываем координаты мяча и значение вектора
 *ball1_x += *vector_X;
}