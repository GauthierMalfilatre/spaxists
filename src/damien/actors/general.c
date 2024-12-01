/*
** EPITECH PROJECT, 2024
** GENERAL_ACOTRS
** File description:
** General actors related functions
*/
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include "../../../include/my.h"
#include "../../../include/my_hunter.h"

actorinfo_t *create_teapot(sfTexture *texture, sfVector2f pos,
    sfVector2f vel, sfVector2f size)
{
    actorinfo_t *new = malloc(sizeof(actorinfo_t));

    new->sprite = sfSprite_create();
    sfSprite_setTexture(new->sprite, texture, sfTrue);
    sfSprite_setPosition(new->sprite, pos);
    sfSprite_setScale(new->sprite, size);
    new->is_alive = sfTrue;
    new->delta_t = 0;
    new->vel = vel;
    new->zindex = 0;
    new->clock = 0;
    new->texturex = 0;
    new->move = &move;
    new->render = &render;
    new->size = size;
    return new;
}

int move(hunter_data_t *infos, actorinfo_t *actor)
{
    sfVector2f pos = sfSprite_getPosition(actor->sprite);

    sfSprite_move(actor->sprite, actor->vel);
    if ((pos.x + (32 * actor->size.x) > WIND_W && actor->vel.x > 0) ||
        (pos.x - (32 * actor->size.x) < 0 && actor->vel.x < 0)) {
        actor->vel = fvectmul(actor->vel, -1.0f, 0.0f);
        sfSprite_move(actor->sprite, fvectmul(actor->vel,
            -1 * actor->size.x * 32, 1.0f));
        sfSprite_setScale(actor->sprite, (sfVector2f)
            {sfSprite_getScale(actor->sprite).x * -1, actor->size.y});
    }
    return 0;
}

int render(sfRenderWindow *window, actorinfo_t *actor)
{
    actor->texturex = my_fmod((actor->texturex + actor->delta_t), 3);
    if (actor->clock) {
        sfSprite_setTextureRect(actor->sprite, (sfIntRect) {(int)
            (actor->texturex) * 32.f, 0, 32, 32});
    }
    sfRenderWindow_drawSprite(window, actor->sprite, 0);
    return 0;
}
