/*
** EPITECH PROJECT, 2024
** UTILS
** File description:
** Utils file 1 for my_hunter
*/
#include "../../include/my_hunter.h"

void draw_string(sfRenderWindow *window, char *str, sfVector2f *pos,
    sfVector2f *size)
{
    sfFont *font = sfFont_createFromFile(FP("bebas_neue.ttf"));
    sfText *text = sfText_create();

    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setPosition(text, *pos);
    sfText_setScale(text, size ? *size : (sfVector2f) {1.0f, 1.0f});
    sfRenderWindow_drawText(window, text, sfFalse);
    sfFont_destroy(font);
    sfText_destroy(text);
    free(str);
    return;
}

char *int_to_str(int n)
{
    int size = my_nbrlen(n, 10);
    char *str = malloc(size + 1);
    int i = 0;

    if (size == 1) {
        str[0] = n + '0';
    if (size < 0) {
        size = -size;
        str[i] = '-';
        ++i;
    }
    } else {
        for (; n > 0; ++i) {
            str[i] = n % 10 + '0';
            n /= 10;
        }
    }
    str[size] = '\0';
    my_revstr(str);
    return str;
}
