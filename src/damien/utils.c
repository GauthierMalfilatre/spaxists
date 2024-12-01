/*
** EPITECH PROJECT, 2024
** UTILS
** File description:
** Utils file 1 for my_hunter
*/
#include "../../include/my_hunter.h"

sfVector2f get_dir(sfVector2f pos1, sfVector2f pos2, double speed)
{
    sfVector2f vect = (sfVector2f) {pos2.x - pos1.x, pos2.y - pos1.y};
    double norme = sqrt(pow(vect.x, 2) + pow(vect.y, 2));

    vect.x = vect.x / norme * speed;
    vect.y = vect.y / norme * speed;
    return vect;
}

double get_norme(sfVector2f pos1, sfVector2f pos2)
{
    sfVector2f vect = (sfVector2f) {pos2.x - pos1.x, pos2.y - pos1.y};

    return sqrt(pow(vect.x, 2) + pow(vect.y, 2));
}

sfVector2f fvectmul(sfVector2f vector, double mul1, double mul2)
{
    return (sfVector2f) {vector.x * mul1, vector.y * mul2};
}

int check_collision(sfSprite *sprite1, sfSprite *sprite2)
{
    sfFloatRect bounds1 = sfSprite_getGlobalBounds(sprite1);
    sfFloatRect bounds2 = sfSprite_getGlobalBounds(sprite2);

    return sfFloatRect_intersects(&bounds1, &bounds2, NULL);
}

int check_collision_center(sfSprite *sprite1, sfSprite *sprite2)
{
    sfFloatRect bounds1 = sfSprite_getGlobalBounds(sprite1);
    sfFloatRect bounds2 = sfSprite_getGlobalBounds(sprite2);

    bounds2.width /= 2.0f;
    bounds2.height /= 2.0f;
    bounds2.left += bounds2.width / 2.0f;
    bounds2.top += bounds2.height;
    return sfFloatRect_intersects(&bounds1, &bounds2, NULL);
}
