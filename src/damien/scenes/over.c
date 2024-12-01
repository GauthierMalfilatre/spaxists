/*
** EPITECH PROJECT, 2024
** OVER
** File description:
** Spaxists game over scene
*/
#include "../../../include/my_hunter.h"

static int check_case(hunter_data_t *game, sfVector2f mouse)
{
    if (mouse.y >= 300 && mouse.y <= 400) {
        if (mouse.x >= 200 && mouse.x <= 628) {
            reset_game(game);
            sfMusic_stop(GETS(game->scenes, "s_over")->infos->theme);
            sfMusic_play(GETS(game->scenes, "s_game")->infos->theme);
        }
        if (mouse.x >= 1225 && mouse.x <= 1650) {
            free(game->actual_scene);
            game->actual_scene = my_strdup("s_menu");
            sfMusic_stop(GETM(game->musics, "m_chill"));
            sfMusic_play(GETM(game->musics, "m_menu"));
        }
    }
    return 0;
}

int over_events(hunter_data_t *game)
{
    sfVector2f mouse = sfSprite_getPosition(GETTA(GETS(game->scenes,
        "s_over")->actors, "a_cursor")->sprite);

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
