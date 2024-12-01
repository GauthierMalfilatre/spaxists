/*
** EPITECH PROJECT, 2024
** POPE_STATION
** File description:
** Pope station related functions
*/
#include "../../../include/my.h"
#include "../../../include/my_hunter.h"

actorinfo_t *create_station(sfTexture *texture, double pv, double shield)
{
    actorinfo_t *new = malloc(sizeof(actorinfo_t));

    new->sprite = sfSprite_create();
    new->clock = sfClock_create();
    new->vel = (sfVector2f) {0.0f, 0.0f};
    new->size = (sfVector2f) {8.0f, 8.0f};
    sfSprite_setTexture(new->sprite, texture, sfTrue);
    sfSprite_setScale(new->sprite, new->size);
    sfSprite_setPosition(new->sprite, (sfVector2f) {(WIND_W - 32 *
        new->size.x) / 2, 800});
    new->move = 0;
    new->render = &station_render;
    new->life = pv;
    new->delta_t = 0;
    new->texturex = 0;
    new->shield = shield;
    new->zindex = 0;
    return new;
}

int station_render(sfRenderWindow *window, actorinfo_t *actor)
{
    float elapsed;
    int x;

    if (actor->clock) {
        elapsed = sfTime_asSeconds(sfClock_getElapsedTime(actor->clock));
        x = my_fmod(elapsed, 3.0f);
        sfSprite_setTextureRect(actor->sprite,
            (sfIntRect) {(x * 32.0f), 0, 32, 32});
    }
    draw_string(window, int_to_str(actor->life), &(sfVector2f) {130, 40},
        &(sfVector2f) {2.0f, 2.0f});
    draw_string(window, int_to_str(actor->shield), &(sfVector2f) {130, 110},
        &(sfVector2f) {2, 2});
    sfRenderWindow_drawSprite(window, actor->sprite, 0);
    return 0;
}

int add_shield(hunter_data_t *game)
{
    if (game->coin >= game->required_coin[SHIELDC]) {
        GETTA(GETS(game->scenes, "s_game")->actors, "a_station")->shield += 10;
        game->coin -= game->required_coin[SHIELDC];
        game->required_coin[SHIELDC] += 10;
    }
    return 0;
}

int add_crusader(hunter_data_t *game)
{
    if (game->coin >= game->required_coin[CRUSADERC]) {
        game->coin -= game->required_coin[CRUSADERC];
        game->required_coin[CRUSADERC] += 10;
    }
    return 0;
}
