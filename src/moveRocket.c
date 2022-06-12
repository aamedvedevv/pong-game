#include <stdlib.h>
#include <stdio.h>
#include "moveRocket.h"

void moveRocket(int *rocket_1_Y, int *rocket_2_Y) {
 char temp;
 system("stty -echo");
 system("stty raw");
 switch (temp = getchar()) {
  case 'a' : ((*rocket_1_Y - 2) != 0) ? (*rocket_1_Y -= 1) : *rocket_1_Y; break;
  case 'z' : ((*rocket_1_Y + 2) != 27 - 1) ? (*rocket_1_Y += 1) : *rocket_1_Y; break;
  case 'k' : ((*rocket_2_Y - 2) != 0) ? (*rocket_2_Y -= 1) : *rocket_2_Y; break;
  case 'm' : ((*rocket_2_Y + 2) != 27 - 1) ? (*rocket_2_Y += 1) : *rocket_2_Y; break;
  case 'c' : exit(1);
   default: ;
 }
 system("stty echo");
 system("stty cooked");
}
