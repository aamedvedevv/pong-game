#include "stdio.h"
#include "stdlib.h"
#include <conio.h>
#include <unistd.h>

void clear_field(char **field);
void draw_field(char **field);
void collision_detection_wall(int *velocity_x, int *velocity_y, int ball_pos_x, int ball_pos_y);
int collision_detection_left(int *velocity_x, int *velocity_y, int ball_pos_x, int ball_pos_y, int left_rocket_pos_y);
int collision_detection_right(int *velocity_x, int *velocity_y, int ball_pos_x, int ball_pos_y, int right_rocket_pos_y);
void add_rocket_to_field(char **field, int rocket_y_pos, int rocket_x_pos);
void add_ball_to_field(char **field, int ball_y_pos, int ball_x_pos);
void draw_perimeter(char **field);

int main()
{
    setbuf(stdout, NULL);

    char buffer[25][80];
    char *field[25];
    for (int i = 0; i < 25; i++)
        field[i] = &buffer[i][0];

    int left_rocket_pos_y = 12, right_rocket_pos_y = 12;
    int ball_velocity_x = -1, ball_velocity_y = 1, ball_pos_x = 40, ball_pos_y = 12;

    int count_left = 0, count_right = 0;

    while (1)
    { 
        printf("SCORE:   left -> %d : %d <- right \n", count_left, count_right);

        if (count_left == 21 || count_right == 21)
        {
            printf("YOU WIN!");
            break;
        }

        clear_field(field);

        char c = getc(stdin);
        if (c == 'a')
            if (left_rocket_pos_y > 1)
                left_rocket_pos_y--;

        if (c == 'z')
            if (left_rocket_pos_y < 24)
                left_rocket_pos_y++;

        if (c == 'k')
            if (right_rocket_pos_y > 1)
                right_rocket_pos_y--;

        if (c == 'm')
            if (right_rocket_pos_y < 24)
                right_rocket_pos_y++;

        collision_detection_wall(&ball_velocity_x, &ball_velocity_y, ball_pos_x, ball_pos_y);

        if (collision_detection_left(&ball_velocity_x, &ball_velocity_y, ball_pos_x, ball_pos_y, left_rocket_pos_y))
        {
            count_right++;
            left_rocket_pos_y = 12, right_rocket_pos_y = 12;
            ball_velocity_x = 1, ball_velocity_y = 1, ball_pos_x = 40, ball_pos_y = 12;
        }

        if (collision_detection_right(&ball_velocity_x, &ball_velocity_y, ball_pos_x, ball_pos_y, right_rocket_pos_y))
        {
            count_left++;
            left_rocket_pos_y = 12, right_rocket_pos_y = 12;
            ball_velocity_x = 1, ball_velocity_y = 1, ball_pos_x = 40, ball_pos_y = 12;
        }

        ball_pos_x += ball_velocity_x;
        ball_pos_y += ball_velocity_y;

        add_rocket_to_field(field, left_rocket_pos_y, 5);
        add_rocket_to_field(field, right_rocket_pos_y, 75);

        add_ball_to_field(field, ball_pos_y, ball_pos_x);
        draw_perimeter(field);
        system("cls");
        draw_field(field);
    }

    return 0;
}

void draw_perimeter(char **field)
{
    for (int i = 1; i < 79; i++)
    {
        field[0][i] = '-';
        field[24][i] = '-';
    }

    for (int i = 1; i < 24; i++)
    {
        field[i][0] = '|';
        field[i][79] = '|';
    }
}

void add_rocket_to_field(char **field, int rocket_y_pos, int rocket_x_pos)
{
    field[rocket_y_pos][rocket_x_pos] = '|';
    field[rocket_y_pos - 1][rocket_x_pos] = '|';
    field[rocket_y_pos + 1][rocket_x_pos] = '|';
}

void add_ball_to_field(char **field, int ball_y_pos, int ball_x_pos)
{
    field[ball_y_pos][ball_x_pos] = '*';
}

int collision_detection_right(int *velocity_x, int *velocity_y, int ball_pos_x, int ball_pos_y, int right_rocket_pos_y)
{
    int is_lose = 0;
    if ((ball_pos_x + *velocity_x) > 75)
        if (ball_pos_y <= right_rocket_pos_y + 1 && ball_pos_y >= right_rocket_pos_y - 1)
            *velocity_x = -*velocity_x;
        else
            is_lose = 1;

    return is_lose;
}

int collision_detection_left(int *velocity_x, int *velocity_y, int ball_pos_x, int ball_pos_y, int left_rocket_pos_y)
{
    int is_lose = 0;
    if ((ball_pos_x + *velocity_x) < 5)
        if (ball_pos_y <= left_rocket_pos_y + 1 && ball_pos_y >= left_rocket_pos_y - 1)
            *velocity_x = -*velocity_x;
        else
            is_lose = 1;

    return is_lose;
}

void collision_detection_wall(int *velocity_x, int *velocity_y, int ball_pos_x, int ball_pos_y)
{
    if ((ball_pos_y + *velocity_y) < 2 || (ball_pos_y + *velocity_y) > 23)
        *velocity_y = - *velocity_y;
}

void draw_field(char **field)
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
            putchar(field[i][j]);
        putchar('\n');
    }
}

void clear_field(char **field)
{
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++)
            field[i][j] = ' ';
}