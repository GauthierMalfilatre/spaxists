/*
** EPITECH PROJECT, 2024
** LINKED_TEXTURES_LIST
** File description:
** Textures linked list related functions
*/
#include "../../../include/my.h"
#include "../../../include/my_hunter.h"

actorinfo_t *create_player(sfTexture *texture)
{
    actorinfo_t *new = malloc(sizeof(actorinfo_t));

    new->sprite = sfSprite_create();
    new->clock = 0;
    new->texturex = 0;
    new->size = (sfVector2f) {2.0f, 2.0f};
    sfSprite_setTexture(new->sprite, texture, sfTrue);
    sfSprite_setScale(new->sprite, new->size);
    new->move = &cursor_move;
    new->render = &render;
    new->zindex = 100;
    new->delta_t = 0;
    new->life = 1;
    new->shield = 1;
    return new;
}

int cursor_move(hunter_data_t *infos, actorinfo_t *actor)
{
    sfVector2i mouse = sfMouse_getPosition((sfWindow *) infos->window);

    sfSprite_setPosition(actor->sprite, (sfVector2f) {mouse.x, mouse.y});
    return 0;
}
