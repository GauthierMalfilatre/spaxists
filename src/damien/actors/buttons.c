/*
** EPITECH PROJECT, 2024
** LINKED_TEXTURES_LIST
** File description:
** Textures linked list related functions
*/
#include "../../../include/my_hunter.h"

buttoninfo_t *create_button(sfTexture *texture, int (*action)(), sfVector2f
    pos, sfVector2f size)
{
    buttoninfo_t *new = malloc(sizeof(buttoninfo_t));

    new->sprite = sfSprite_create();
    new->size = size;
    new->clock = 0;
    sfSprite_setTexture(new->sprite, texture, sfTrue);
    sfSprite_setPosition(new->sprite, pos);
    sfSprite_setScale(new->sprite, new->size);
    new->action = action;
    new->move = &button_move;
    new->render = &render;
    new->zindex = 10;
    return new;
}

int button_move(hunter_data_t *game, buttoninfo_t *actor)
{
    if (check_collision(GETTA(GETS(game->scenes, game->actual_scene)->actors,
        "a_cursor")->sprite, actor->sprite)) {
        actor->action(game);
    }
    return 0;
}

int check_buttons(hunter_data_t *game, button_t *buttons)
{
    if (!buttons) {
        return 1;
    }
    for (button_t *temp = buttons; temp; temp = temp->next) {
        temp->infos->move(game, temp->infos);
    }
    return 0;
}
