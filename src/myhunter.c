/*
** EPITECH PROJECT, 2024
** SPAXISTS
** File description:
** Spaxists main file
*/
#include "../include/my.h"
#include "../include/my_hunter.h"

int spaxists_mainloop(hunter_data_t *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        sfRenderWindow_clear(game->window, sfBlack);
        GETS(game->scenes, game->actual_scene)->infos->event(game);
        game->globall(game, game->actual_scene);
        sfRenderWindow_display(game->window);
    }
    return 0;
}

int main(int argc, char *const *argv)
{
    hunter_data_t *game;

    if (argc == 2 && !my_strcmp(argv[1], "-h")) {
        my_printf("SPAXISTS, a game made by Gauthier Malfilatre\n");
    } else {
        game = create_game("SPAXISTS");
        sfRenderWindow_setVerticalSyncEnabled(game->window, sfTrue);
        sfMusic_play(GETS(game->scenes, game->actual_scene)->infos->theme);
        spaxists_mainloop(game);
        destroy_game(game);
    }
    return 0;
}
