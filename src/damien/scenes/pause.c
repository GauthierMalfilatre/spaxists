/*
** EPITECH PROJECT, 2024
** SPAXISTS_GAME
** File description:
** Spaxists game scene
*/
#include "../../../include/my_hunter.h"

static void restart_clock(actor_t *actors)
{
    for (actor_t *temp = actors; temp; temp = temp->next) {
        if (temp->infos->clock) {
            sfClock_restart(temp->infos->clock);
        }
    }
}

static int check_sub(hunter_data_t *game, sfVector2f mouse, int instant_resume)
{
    if ((mouse.x >= 625 && mouse.x <= 1260 && mouse.y >= 420 && mouse.y <= 580)
        || instant_resume) {
            free(game->actual_scene);
            game->actual_scene = my_strdup("s_game");
            restart_clock(GETS(game->scenes, "s_game")->actors);
            return 0;
        }
    if (mouse.x >= 625 && mouse.x <= 1260 && mouse.y >= 690 &&
        mouse.y <= 860) {
            free(game->actual_scene);
            game->actual_scene = my_strdup("s_menu");
            sfMusic_stop(GETM(game->musics, "m_game"));
            sfMusic_play(GETM(game->musics, "m_menu"));
        }
    return 0;
}

int pause_event(hunter_data_t *game)
{
    sfVector2f mouse = sfSprite_getPosition(GETTA(GETS(game->scenes,
        "s_pause")->actors, "a_cursor")->sprite);

    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        if (game->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window);
        }
        if (game->event.type == sfEvtResized) {
            case_view(game);
        }
        if (game->event.type == sfEvtMouseButtonPressed || (game->event.type
            == sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyEscape))) {
            check_sub(game, mouse, (game->event.type == sfEvtKeyPressed &&
                sfKeyboard_isKeyPressed(sfKeyEscape)));
        }
    }
    return 0;
}
