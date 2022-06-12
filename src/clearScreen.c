//
// screenRender and clearScreen functions
//
// Created by Aleksandr Medvedev (felishaa) on 12.06.2022

#include <stdio.h>
#include <stdlib.h>
#include "clearScreen.h"

void clearScreen() {                    // Функция очищает экран от предыдущих отрисовок, что позволяет нам видеть только 1 игровую таблицу
 system("printf \033c");
}
