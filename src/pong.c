// I WANT TO PLAY WITH YOU
//        YOUR FRIEND, AI

#include <stdio.h>
#include <stdlib.h>
#include "moveBall.h"
#include "moveRocket.h"
#include "screenRender.h"
#include "clearScreen.h"
#include "checkScore.h"

int main() {
    int rocket_1_Y = 19;       // Переменные по умолчанию - положение рок 1
    int rocket_2_Y = 5;        // Переменные по умолчанию - положение рок 2
    int ball_X = 41;           // Переменные по умолчанию - положение мячик
    int ball_Y = 13;
    int vector_X = -1;         // Направление движения мячика
    int vector_Y = 1;
    int scorePlayer_1 = 0;     // счет 1 игрока
    int scorePlayer_2 = 0;     // счет 2 игрока

while(1) {
        screenRender(&rocket_1_Y, &rocket_2_Y, &ball_X, &ball_Y,
              &scorePlayer_1, &scorePlayer_2);

        moveRocket(&rocket_1_Y, &rocket_2_Y);

        moveBall(&ball_X, &ball_Y,
         &vector_X, &vector_Y,
         &rocket_1_Y, &rocket_2_Y);

        clearScreen();
        if (checkScore(&scorePlayer_1, &scorePlayer_2,
              &ball_X, &ball_Y)) {
            break;
           }
    }
    return 0;
}
