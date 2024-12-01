/*
** EPITECH PROJECT, 2024
** GAME_STRUCTURE_GENERAL
** File description:
** Game struct related functions
*/
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include "../../include/my.h"
#include "../../include/my_hunter.h"

static int game_move(hunter_data_t *infos, scenes_t *scene)
{
    sfBool check_if_rastazer = sfFalse;

    sort_actor_by_index(&(scene->actors));
    for (actor_t *temp = scene->actors; temp; temp = temp->next) {
        if (!my_strcmp(temp->id, "a_rastazer") || !my_strcmp(temp->id,
            "a_yohann"))
            ++check_if_rastazer;
        if (temp->infos->move && my_strcmp(temp->id, "ab_button"))
            temp->infos->move(infos, temp->infos);
    }
    if (!check_if_rastazer && !my_strcmp(scene->id, "s_game")) {
        ++infos->n_rastazer;
        if (infos->n_rastazer > 100)
            add_yohann(&scene->actors, GETT(infos->textures, "t_yohann"));
        else
            add_n_rastazer(&scene->actors, GETT(infos->textures, "t_75"),
            infos->n_rastazer, &(sfVector2f) {800.0f, 0.0f});
    }
    return 0;
}

static int to_gameover(hunter_data_t *infos, actorinfo_t *station)
{
    int total_coin = load_save(SAVEPATH);

    infos->total_coin = total_coin + infos->coin;
    save(SAVEPATH, infos->total_coin);
    station->life = 1.0f;
    free(infos->actual_scene);
    infos->actual_scene = my_strdup("s_over");
    sfMusic_stop(GETM(infos->musics, "m_game"));
    sfMusic_play(GETM(infos->musics, "m_chill"));
    return 1;
}

static int game_render(hunter_data_t *infos, scenes_t *scene)
{
    actorinfo_t *station = GETTA(GETS(infos->scenes, "s_game")->actors,
        "a_station");

    if (station->life <= 0.0f)
        return to_gameover(infos, station);
    if (!my_strcmp(infos->actual_scene, "s_over")) {
        draw_string(infos->window, int_to_str(infos->total_coin), &(sfVector2f)
            {530, 180}, &(sfVector2f) {2, 2});
        draw_string(infos->window, my_strdup("Total coins earned : "),
            &(sfVector2f) {50, 180}, &(sfVector2f) {2, 2});
    }
    for (button_t *temp = scene->infos->button; temp; temp = temp->next) {
        sfRenderWindow_drawSprite(infos->window, temp->infos->sprite, 0);
    }
    for (actor_t *temp = scene->actors; temp; temp = temp->next) {
        if (temp->infos->render)
            temp->infos->render(infos->window, temp->infos);
    }
    return 0;
}

int game_globall(hunter_data_t *infos, char *scene_id)
{
    scenes_t *scene = GETS(infos->scenes, scene_id);

    sfRenderWindow_drawSprite(infos->window, scene->infos->background, 0);
    if (!my_strcmp(scene->id, "s_game")) {
        draw_string(infos->window, int_to_str(infos->coin), &(sfVector2f)
            {135, 180}, &(sfVector2f) {2, 2});
    }
    game_move(infos, scene);
    if (!game_render(infos, scene))
        update_rokets(infos, GETS(infos->scenes, scene_id));
    return 0;
}

sfView *setview(sfRenderWindow *window)
{
    sfView *new = sfView_create();

    sfView_setSize(new, (sfVector2f) {WIND_W, WIND_H});
    sfView_setCenter(new, (sfVector2f) {WIND_W / 2, WIND_H / 2});
    sfRenderWindow_setView(window, new);
    return new;
}

hunter_data_t *create_game(char *title)
{
    hunter_data_t *new = malloc(sizeof(hunter_data_t));

    srand(time(NULL));
    new->actual_scene = my_strdup("s_menu");
    new->video_mode = (sfVideoMode) {WIND_W, WIND_H, 32};
    new->window = sfRenderWindow_create(new->video_mode, title,
        sfClose | sfResize, 0);
    new->musics = load_musics();
    new->textures = load_textures();
    new->scenes = load_scenes(new->textures, new->musics);
    new->globall = &game_globall;
    new->sounds = load_sounds();
    new->view = setview(new->window);
    new->coin = 0;
    new->total_coin = 0;
    new->n_rastazer = 1;
    new->required_coin[SHIELDC] = 100;
    new->required_coin[CRUSADERC] = 100;
    sfRenderWindow_setMouseCursorVisible(new->window, sfFalse);
    return new;
}

void reset_game(hunter_data_t *game)
{
    srand(time(NULL));
    destroy_scenes(game->scenes);
    free(game->actual_scene);
    game->actual_scene = my_strdup("s_game");
    game->scenes = load_scenes(game->textures, game->musics);
    game->n_rastazer = 1;
    game->coin = 0;
    sfMusic_stop(GETM(game->musics, "m_menu"));
    sfMusic_play(GETM(game->musics, "m_game"));
}
