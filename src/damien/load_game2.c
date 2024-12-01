/*
** EPITECH PROJECT, 2024
** LOAD_GAME
** File description:
** "Config file" to load game properly
*/
#include "../../include/my_hunter.h"

button_t *load_game_buttons(textures_t *texture)
{
    button_t *new = ADDB(0, "ab_button", create_button(GETT(texture,
        "tb_shield"), &add_shield, (sfVector2f) {WIND_W - 400, 900},
            (sfVector2f) {0.8f, 0.8f}));

    return new;
}

actor_t *load_menu_actors(textures_t *textures)
{
    actor_t *new = ADDA(0, "a_cursor",
        create_player(GETT(textures, "t_cursor")));

    return new;
}

actor_t *load_pause_actors(textures_t *textures)
{
    actor_t *new = ADDA(0, "a_cursor",
        create_player(GETT(textures, "t_cursor")));

    return new;
}

actor_t *load_over_actors(textures_t *textures)
{
    actor_t *new = ADDA(0, "a_cursor",
        create_player(GETT(textures, "t_cursor")));

    new = ADDA(new, "a_coin", create_teapot(GETT(textures, "t_coin"),
        (sfVector2f) {450, 175}, (sfVector2f) {0, 0},
            (sfVector2f) {2.5f, 2.5f}));
    return new;
}
