//
//
// Created by Tamara (machampa)
// 12.06.2022
#include <stdio.h>
#include "checkScore.h"

int checkScore(int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y) {                        // Проверка счета игроков, когда у кого нибудь 21 - победа
 if (*ball1_x < 2) {
 *scPlayer2 += 1;
 *ball1_x = 41;                                                                                     // Возвращает мяч в начальную точку
 *ball1_y = 13;
 }
 if (*ball1_x > 79) {
 *scPlayer1 += 1;
 *ball1_x = 41;                                                                                     // Возвращает мяч в начальную точку
 *ball1_y = 13;
 }
 if (*scPlayer1 == 21) {
     printf("\nОтлично сработано!!! Выиграл игрок 1 со счётом %d : %d", *scPlayer1, *scPlayer2);    // Выводит сообщение о победе в консоль
 return 1;
 } else if (*scPlayer2 == 21) {
   printf("\nОтлично сработано!!! Выиграл игрок 2 со счётом %d : %d", *scPlayer2, *scPlayer1);
 return 1;
 }
 return 0;
}
