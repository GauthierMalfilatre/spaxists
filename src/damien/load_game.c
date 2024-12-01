/*
** EPITECH PROJECT, 2024
** LOAD_GAME
** File description:
** "Config file" to load game properly
*/
#include "../../include/my_hunter.h"

music_t *load_musics(void)
{
    music_t *new = ADDM(0, "m_menu", MP("main_menu.ogg"));

    new = ADDM(new, "m_chill", MP("chillguy.ogg"));
    new = ADDM(new, "m_game", MP("main_theme.ogg"));
    return new;
}

textures_t *load_textures(void)
{
    textures_t *new = ADDT(0, "t_bg", PP("main_menu2.png"));

    new = ADDT(new, "t_yohann", PP("yohann.png"));
    new = ADDT(new, "t_pause", PP("pause2.png"));
    new = ADDT(new, "t_menu", PP("menu.png"));
    new = ADDT(new, "t_coin", PP("coin.png"));
    new = ADDT(new, "t_shield", PP("shield.png"));
    new = ADDT(new, "t_heart", PP("heart.png"));
    new = ADDT(new, "tb_shield", BP("buyshieldbutton.png"));
    new = ADDT(new, "t_roket", PP("roket2flip.png"));
    new = ADDT(new, "t_over", PP("gameover2.png"));
    new = ADDT(new, "t_75", PP("rastazer.png"));
    new = ADDT(new, "t_cursor", PP("cursor.png"));
    new = ADDT(new, "t_station", PP("pope_station2.png"));
    return new;
}

actor_t *load_game_actors(textures_t *textures)
{
    actor_t *new = ADDA(0, "a_cursor",
        create_player(GETT(textures, "t_cursor")));

    new = ADDA(new, "a_coin", create_teapot(GETT(textures, "t_coin"),
        (sfVector2f) {45, 185}, (sfVector2f) {0, 0},
            (sfVector2f) {2.5f, 2.5f}));
    new = ADDA(new, "a_shield", create_teapot(GETT(textures, "t_shield"),
        (sfVector2f) {40, 100}, (sfVector2f) {0, 0}, (sfVector2f) {3, 3}));
    new = ADDA(new, "a_heart", create_teapot(GETT(textures, "t_heart"),
        (sfVector2f) {10, 10}, (sfVector2f) {0, 0}, (sfVector2f) {5, 5}));
    new = ADDA(new, "a_station", create_station(GETT(textures, "t_station"),
        100.0f, 100.0f));
    add_n_rastazer(&new, GETT(textures, "t_75"), 1, &(sfVector2f)
        {800.0f, 0.0f});
    return new;
}

scenes_t *load_scenes(textures_t *textures, music_t *music)
{
    scenes_t *new = ADDS(0, "s_game", load_game_actors(textures),
        create_scene(GETM(music, "m_game"), GETT(textures, "t_bg"),
            &game_event, load_game_buttons(textures)));

    new = ADDS(new, "s_over", load_over_actors(textures),
        create_scene(GETM(music, "m_chill"), GETT(textures, "t_over"),
            &over_events, 0));
    new = ADDS(new, "s_menu", load_menu_actors(textures),
        create_scene(GETM(music, "m_menu"), GETT(textures, "t_menu"),
            &menu_event, 0));
    new = ADDS(new, "s_pause", load_pause_actors(textures), create_scene(0,
        GETT(textures, "t_pause"), &pause_event, 0));
    return new;
}

sound_t *load_sounds(void)
{
    sound_t *new = ADDSO(0, "so_shot", SP("holy_shot.ogg"));

    new = ADDSO(new, "so_sus", SP("sus.ogg"));
    new = ADDSO(new, "so_roket", SP("roketboom.ogg"));
    return new;
}
