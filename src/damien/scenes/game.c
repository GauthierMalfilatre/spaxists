/*
** EPITECH PROJECT, 2024
** SPAXISTS_GAME
** File description:
** Spaxists game scene
*/
#include "../../../include/my_hunter.h"

static int check_win_size(hunter_data_t *game)
{
    sfVector2u size = sfRenderWindow_getSize(game->window);

    if (game->event.size.width > WIND_W) {
        size = sfRenderWindow_getSize(game->window);
        sfRenderWindow_setSize(game->window, (sfVector2u) {WIND_W, size.y});
    }
    if (game->event.size.width < 800) {
        size = sfRenderWindow_getSize(game->window);
        sfRenderWindow_setSize(game->window, (sfVector2u) {800, size.y});
    }
    if (game->event.size.height > WIND_H) {
        size = sfRenderWindow_getSize(game->window);
        sfRenderWindow_setSize(game->window, (sfVector2u) {size.x, WIND_H});
    }
    if (game->event.size.height < 600) {
        size = sfRenderWindow_getSize(game->window);
        sfRenderWindow_setSize(game->window, (sfVector2u) {size.x, 600});
    }
    return 0;
}

int case_view(hunter_data_t *game)
{
    float width = game->event.size.width;
    float height = game->event.size.height;
    float dr_ratio = (float) WIND_W / (float) WIND_H;
    float nwidht;
    float nheight;

    if (width / height > dr_ratio) {
        nwidht = dr_ratio * height;
        sfView_setViewport(game->view, (sfFloatRect){
            (width - nwidht) / (2.f * width), 0.f, nwidht / width, 1.f
        });
    } else {
        nheight = width / dr_ratio;
        sfView_setViewport(game->view, (sfFloatRect){
            0.f, (height - nheight) / (2.f * height), 1.f, nheight / height
        });
    }
    sfRenderWindow_setView(game->window, game->view);
    check_win_size(game);
    return 0;
}

int game_event(hunter_data_t *game)
{
    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        if (game->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window);
        }
        if (game->event.type == sfEvtMouseButtonPressed) {
            check_buttons(game, GETS(game->scenes,
                game->actual_scene)->infos->button);
            update_rastazers(game, GETS(game->scenes, game->actual_scene));
            sfSound_play(GETTO(game->sounds, "so_shot"));
        }
        if (game->event.type == sfEvtResized) {
            case_view(game);
        }
        if (game->event.type == sfEvtKeyPressed &&
            sfKeyboard_isKeyPressed(sfKeyEscape)) {
            free(game->actual_scene);
            game->actual_scene = my_strdup("s_pause");
        }
    }
    return 0;
}
