/*
** EPITECH PROJECT, 2024
** SPAXISTS_GAME
** File description:
** Spaxists game scene
*/
#include "../../../include/my_hunter.h"

static int check_case(hunter_data_t *game, sfVector2f mouse)
{
    if (mouse.x >= 720 && mouse.x <= 1155) {
        if (mouse.y >= 475 && mouse.y <= 560) {
            reset_game(game);
            sfMusic_stop(GETS(game->scenes, "s_menu")->infos->theme);
            sfMusic_play(GETS(game->scenes, "s_game")->infos->theme);
        }
        if (mouse.y >= 740 && mouse.y <= 830) {
            sfRenderWindow_close(game->window);
        }
    }
    return 0;
}

int menu_event(hunter_data_t *game)
{
    sfVector2f mouse = sfSprite_getPosition(GETTA(GETS(game->scenes,
        "s_menu")->actors, "a_cursor")->sprite);

    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        if (game->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window);
        }
        if (game->event.type == sfEvtResized) {
            case_view(game);
        }
        if (game->event.type == sfEvtMouseButtonPressed) {
            check_case(game, mouse);
        }
    }
    return 0;
}
