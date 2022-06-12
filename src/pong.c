//
// ****** Pong Game ******
//
// Created by Aleksandr(felishaa) Oleg(baggpite) Tamara(machampa) on 12.06.2022

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

void moveBall(int *ball1_x, int *ball1_y, int *vector_X, int *vector_Y,
    const int *rocket_1_Y, const int *rocket_2_Y);
void moveRocket(int *rocket_1_Y, int *rocket_2_Y);
void clearScreen();
void screenRender(const int *rocket_1_Y, const int *rocket_2_Y,
   const int *ball1_x, const int *ball1_y,
   int *scPlayer1, int *scPlayer2i);
int checkScore(int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y);
void setKeyboard();
void resetKeyboard();
void clearScreen();
int kbnit();
char getch();
void msSleep(float x);
struct termios initial_settings, new_settings;
int peek_character = -1;




int main() {
    int rocket_1_Y = 19;
// Переменные по умолчанию - положение рок 1
    int rocket_2_Y = 5;
// Переменные по умолчанию - положение рок 2
    int ball_X = 41;
// Переменные по умолчанию - положение мячик
    int ball_Y = 13;
    int vector_X = -1;
// Направление движения мячика
    int vector_Y = 1;
    int scorePlayer_1 = 0;
// счет 1 игрока
    int scorePlayer_2 = 0;
// счет 2 игрока

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

void moveBall(int *ball1_x, int *ball1_y, int *vector_X, int *vector_Y,
    const int *rocket_1_Y, const int *rocket_2_Y) {
// Функция отвечает за передвежение мяча
    if (*ball1_y == 1 || *ball1_y == 25) {
// Смотрим на положение мяча по координате Y
        *vector_Y = -(*vector_Y);
// Меняем вектор направления на противоположный
    }
    if (*ball1_x == 3 &&
// Сравниваем положение ракетки 1 и мяча, чтобы в случае столкновения менялся
        (*ball1_y == *rocket_1_Y - 1 ||*ball1_y == *rocket_1_Y ||
// Вектор направления на противоположный
         *ball1_y == *rocket_1_Y + 1)) {
        *vector_X = -(*vector_X);
    }
    if (*ball1_x == 78 &&
// Сравниваем положение ракетки 2 и мяча, чтобы в случае столкновения менялся
        (*ball1_y == *rocket_2_Y - 1 || *ball1_y == *rocket_2_Y ||
// вектор направления на противоположный
         *ball1_y == *rocket_2_Y + 1)) {
        *vector_X = -(*vector_X);
    }
        msSleep(0.08);
        *ball1_y += *vector_Y;
        *ball1_x += *vector_X;
// Складываем координаты мяча и значение вектора
    }

void screenRender(const int *rocket_1_Y, const int *rocket_2_Y,
   const int *ball1_x, const int *ball1_y,
   int *scPlayer1, int *scPlayer2) {
    for (int y = 0; y < 5; y++) {
// Цикл выполняет 5 итераций для прорисовки поля приветствия по оси y
        for (int x = 0; x < 82; x++) {
// Цикл выполняет 82 итерации для прорисовки поля приветствия по оси x
            if ((y == 0 && x != 0 && x != 81) ||
// Условие помогает сделать отрисовку y = 0 символами # исключая 0 и 81 ячейку по x
                (y == 4 && x != 0 && x != 81)) {
// Отрисовывает нижнюю границу y = 4
                printf("#");
            } else if (((x == 1 && y != 0 && y != 4) ||
// Отрисовка левой границы символом | по x = 1
              (x == 81 && y != 0 && y != 4))) {
// Отрисовка левой границы символом | по x = 81
                printf("|");
            } else if (x == 25 && y == 2) {
// Указание адреса, где необходимо реализовать надпись привествия
                printf("Добро пожаловать в пинг-понг ^_^");
            } else if ((y == 1 && x < 80) || (y != 2 && x < 80)) {
// Отступы y = 1 и y != 2 с ограничениями до x 80
                printf(" ");
            } else if (y == 2 && x < 82 - 33) {
// Отступы y = 2 со смещением надписи по x
                printf(" ");
  }
        }
    printf("\n");
// Отступ до другого поля
    }

    for (int y = 0; y < 27; ++y) {
// Цикл выполняет 27 итераций для прорисовки поля игры по оси y
        for (int x = 0; x < 82; ++x) {
// Цикл выполняет 82 итераций для прорисовки поля игры по оси x
            if ((x == 2 &&
                 (y == *rocket_1_Y - 1 || y == *rocket_1_Y || y == *rocket_1_Y + 1)) ||
// Условие считывает координату ракетки №1 игрока от 1 до 3, так как ракетка занимает 3 символа
                (x == 79 &&
                 (y == *rocket_2_Y - 1 || y == *rocket_2_Y || y == *rocket_2_Y + 1))) {
// Условие считывает координату ракетки №2 игрока от 1 до 3, так как ракетка занимает 3 символа
                printf("|");
// Прорисовка ракетки символом |
            } else if (x == *ball1_x && y == *ball1_y) {
// Условие считывает координату мяча
                printf("o");
// Прорисовка мяча символом o
            } else if ((y == 0 && x != 0 && x != 81) ||
// Отрисовка верхней и нижней границы символом - на y = 0 и y = 26
                       (y == 26 && x != 0 && x != 81)) {
                printf("-");
            } else if ((x == 0 && y != 0 && y != 26) ||
// Отрисовка левой, правой и центральной границ символом | на x = 0 и x = 81 и x = 41
                       (x == 81 && y != 0 && y != 26) ||
                       (x == 82 / 2)) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int y = 0; y < 3; y++) {
// Цикл выполняет 3 итераций для прорисовки поля счета игроков по оси y
        for (int x = 0; x < 82; x++) {
// Цикл выполняет 82 итерации для прорисовки поля счета игроков по оси x
            if ((y == 0 && x != 0 && x != 81) ||
// Условие помогает сделать отрисовку y = 0 символами # исключая 0 и 81 ячейку по x
                (y == 2 && x != 0 && x != 81)) {
// Отрисовывает нижнюю границу y = 2
                printf("#");
            } else if (((x == 1 && y != 0 && y != 2) ||
// Отрисовка левой границы символом | по x = 1 исключая y = 2 и y = 0
                        (x == 81 && y != 0 && y != 2))) {
// Отрисовка левой границы символом | по x = 81 исключая y = 2 и y = 0
                printf("|");
            } else if (x == 10) {
// Указание адреса, где необходимо реализовать надпись инструкции по управлению и счет игроков
                printf("Нажми \'c\' чтобы выйти           Первый игрок: %d | Второй игрок: %d"
                       , *scPlayer1, *scPlayer2);
            } else if ((*scPlayer1 >= 10 && *scPlayer1 <= 21) || (*scPlayer2 >= 10 && *scPlayer2 <= 21)) {
// Считывание счета игроков и смещение отрисовки правого поля в зависимости от счета
                if (*scPlayer1 >= 10 && *scPlayer2 >= 10) {
                    if ((y == 1 && x < 14) || (y != 1)) {
                        printf(" ");
                    }
                } else if ((y == 1 && x < 15) || (y != 1)) {
                    printf(" ");
                }
            } else if ((*scPlayer1 >= 0 && *scPlayer1 < 10) || (*scPlayer2 >= 0 && *scPlayer2 < 10)) {
                if ((y == 1 && x < 16) || (y != 1)) {
                    printf(" ");
                }
            } else if (*scPlayer1 >= 10 && *scPlayer2 >= 10) {
                if ((y == 1 && x < 15) || (y != 1)) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    }


void setKeyboard() {
    tcgetattr(0, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void resetKeyboard() {
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbnit() {
    char ch;
    int nread;
    if (peek_character != -1) return 1;
// Проверка на наличие символа в буфере
    new_settings.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0, &ch, 1);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
    if (nread == 1) {
        peek_character = ch;
        return 1;
    }
    return 0;
}

char readch() {
    char ch;

    if (peek_character != -1) {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0, &ch, 1);
    while(getchar() != '\n') continue;
    return ch;
}

int checkScore(int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y) {
// Проверка счета игроков, когда у кого нибудь 21 - победа
    if (*ball1_x < 2) {
        *scPlayer2 += 1;
        *ball1_x = 41;
// Возвращает мяч в начальную точку
        *ball1_y = 13;
    }
    if (*ball1_x > 79) {
        *scPlayer1 += 1;
        *ball1_x = 41;
// Возвращает мяч в начальную точку
        *ball1_y = 13;
    }
    if (*scPlayer1 == 21) {
        printf("\nОтлично сработано!!! Выиграл игрок 1 со счётом %d : %d", *scPlayer1, *scPlayer2);
// Выводит сообщение о победе в консоль
        return 1;
    } else if (*scPlayer2 == 21) {
        printf("\nОтлично сработано!!! Выиграл игрок 2 со счётом %d : %d", *scPlayer2, *scPlayer1);
        return 1;
    }
    return 0;
    }

void clearScreen() {
// Функция очищает экран от предыдущих отрисовок, что позволяет нам видеть только 1 игровую таблицу
    system("printf \033c");
}

void moveRocket(int *rocket_1_Y, int *rocket_2_Y) {
// Функция, двигающая ракетку

  setKeyboard();
  if (kbnit()) {
      char temp;
      temp = readch();
      
// Берем символ из буфера
      if (temp == 'a' && ((*rocket_1_Y - 2) != 0))
// Условия для игрока_1. Если нажата клавиша А и ракетка находится не в верхней границе
        *rocket_1_Y -= 1;
// то двигаем ее наверх

      else if (temp == 'z' && ((*rocket_1_Y + 2) != 26))
// Если нажата Z и ракетка не в нижней границе, то двигаем ее вниз
        *rocket_1_Y += 1;

      else if (temp == 'k' && ((*rocket_2_Y -2) != 0))
// Условия для игрока_2. Точно та же логика, что и для игрока_1, только с кнопками
        *rocket_2_Y -= 1;
// К и М

      else if (temp == 'm' && ((*rocket_2_Y + 2) != 26))
        *rocket_2_Y += 1;

      if (temp == 'c') {
        resetKeyboard();
// Условие выхода из игры
        exit(1);}
  }
}

void msSleep(float sec) {
    struct timespec tv;
    tv.tv_sec = floor(sec);
    tv.tv_nsec = ((sec - floor(sec)) * 1000000000);
    nanosleep(&tv, NULL);
}
