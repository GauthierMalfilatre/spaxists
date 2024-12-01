/*
** EPITECH PROJECT, 2024
** DAY13
** File description:
** Header file for day13
*/
#ifndef MY_HUNTER_H
    #define MY_HUNTER_H
    #define WIND_W 1920
    #define WIND_H 1080
    #define SAVEPATH "src/saves/mod49209.sav"
    #define PP(name) ("assets/pictures/" name) // PICTURES PATH
    #define MP(name) ("assets/musics/" name)   // MUSICS PATH
    #define SP(name) ("assets/sounds/" name)   // SOUNDS PATH
    #define FP(name) ("assets/fonts/" name)    // FONTS PATH
    #define BP(name) ("assets/buttons/" name)  // BUTTONS PATH
    #define ADDT(...) add_texture(__VA_ARGS__)
    #define ADDS(...) add_scene(__VA_ARGS__)
    #define ADDM(...) add_music(__VA_ARGS__)
    #define ADDA(...) add_actor(__VA_ARGS__)
    #define ADDSO(...) add_sound(__VA_ARGS__)
    #define ADDB(...) add_button(__VA_ARGS__)
    #define GETT(...) get_texture_from_id(__VA_ARGS__)
    #define GETS(...) get_scene_from_id(__VA_ARGS__)
    #define GETM(...) get_music_from_id(__VA_ARGS__)
    #define GETTA(...) get_actor_from_id(__VA_ARGS__)
    #define GETTO(...) get_sound_from_id(__VA_ARGS__)
    #define GETTB(...) get_button_from_id(__VA_ARGS__)
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #include "my.h"
    #include <math.h>

// Saving
int load_save(char *path);
int save(char *path, int coins);

// Textures && musics linked lists
typedef struct game_texture_s {
    sfTexture *texure;
    char *id;
    struct game_texture_s *next;
} textures_t;

textures_t *load_textures(void);
textures_t *add_texture(textures_t *current, char *id, char *path);
sfTexture *get_texture_from_id(textures_t *start, char *id);

typedef struct game_music_s {
    sfMusic *music;
    char *id;
    struct game_music_s *next;
} music_t;

music_t *load_musics(void);
music_t *add_music(music_t *current, char *id, char *path);
sfMusic *get_music_from_id(music_t *start, char *id);

typedef struct game_sound_s {
    sfSoundBuffer *soudbuffer;
    sfSound *sound;
    char *id;
    struct game_sound_s *next;
} sound_t;

sound_t *load_sounds(void);
sound_t *add_sound(sound_t *current, char *id, char *path);
sfSound *get_sound_from_id(sound_t *start, char *id);

// Button

typedef struct buttoninfo_s {
    sfSprite *sprite;
    sfClock *clock;
    sfVector2f size;
    int (*move)();
    int (*render)();
    int zindex;
    int (*action)();
} buttoninfo_t;

typedef struct game_button_s {
    buttoninfo_t *infos;
    char *id;
    struct game_button_s *prev;
    struct game_button_s *next;
} button_t;

// Actor

typedef struct actorinfo_s {
    sfSprite *sprite;
    sfVector2f vel;
    sfClock *clock;
    sfVector2f size;
    double delta_t;
    double texturex;
    int (*move)();
    int (*render)();
    int zindex;
    double life;
    double shield;
    double is_alive;
    double cooldown;
    int (*action)();
} actorinfo_t;

typedef struct game_actor_s {
    actorinfo_t *infos;
    char *id;
    struct game_actor_s *next;
    struct game_actor_s *prev;
} actor_t;

actor_t *load_actors(textures_t *textures);
actor_t *add_actor(actor_t *current, char *id, actorinfo_t *infos);
actorinfo_t *get_actor_from_id(actor_t *start, char *id);

// Scenes

typedef struct scene_info_s {
    sfSprite *background;
    sfMusic *theme;
    button_t *button;
    int (*event)();
    int (*render)();
} sceneinfo_t;

typedef struct game_scene_s {
    sceneinfo_t *infos;
    actor_t *actors;
    char *id;
    struct game_scene_s *next;
} scenes_t;

scenes_t *load_scenes(textures_t *textures, music_t *music);
scenes_t *add_scene(scenes_t *current, char *id, actor_t *actor,
    sceneinfo_t *infos);
scenes_t *get_scene_from_id(scenes_t *start, char *id);
sceneinfo_t *create_scene(sfMusic *theme, sfTexture *texture, int (*event)(),
    button_t *buttons);

// Gamestruct
typedef struct hunter_data_s {
    int n_rastazer;
    textures_t *textures;
    music_t *musics;
    scenes_t *scenes;
    char *actual_scene;
    sound_t *sounds;
    sfView *view;
    sfRenderWindow *window;
    sfVideoMode video_mode;
    sfEvent event;
    int required_coin[2];
    int coin;
    int total_coin;
    int regen;
    int (*globall)();
} hunter_data_t;

enum r_coin_e {
    SHIELDC,
    CRUSADERC
};

hunter_data_t *create_game(char *screen_title);
void reset_game(hunter_data_t *game);
int destroy_game(hunter_data_t *game);
int game_globall(hunter_data_t *infos, char *scene_id);

// Game
int move(hunter_data_t *infos, actorinfo_t *actor);
int render(sfRenderWindow *window, actorinfo_t *actor);
sfVector2f fvectmul(sfVector2f vector, double mul1, double mul2);
int check_collision(sfSprite *sprite1, sfSprite *sprite2);
int check_collision_center(sfSprite *sprite1, sfSprite *sprite2);
actorinfo_t *create_teapot(sfTexture *texture, sfVector2f pos,
    sfVector2f vel, sfVector2f size);
int destroy_scenes(scenes_t *scene);

// Game scene
int game_event(hunter_data_t *game);
int case_view(hunter_data_t *game);

// Menu scene
int menu_event(hunter_data_t *game);
actor_t *load_menu_actors(textures_t *textures);

// Pause scene
int pause_event(hunter_data_t *game);
actor_t *load_pause_actors(textures_t *textures);

// Over scene
int over_events(hunter_data_t *game);
actor_t *load_over_actors(textures_t *textures);

// Utils
sfVector2f get_dir(sfVector2f pos1, sfVector2f pos2, double speed);
double get_norme(sfVector2f pos1, sfVector2f pos2);
void sort_actor_by_index(actor_t **begin);
void draw_string(sfRenderWindow *window, char *str, sfVector2f *pos,
    sfVector2f *size);
char *int_to_str(int n);

// Player
actorinfo_t *create_player(sfTexture *texture);
int cursor_move(hunter_data_t *infos, actorinfo_t *actor);

// rastazer
void add_n_rastazer(actor_t **head, sfTexture *texture, int n,
    sfVector2f *velocity);
int move_rastazer(hunter_data_t *infos, actorinfo_t *actor);
int update_rastazers(hunter_data_t *infos, scenes_t *scene);
int update_rokets(hunter_data_t *game, scenes_t *scene);

// Station
actorinfo_t *create_station(sfTexture *texture, double pv, double shield);
int station_render(sfRenderWindow *window, actorinfo_t *actor);

// Roket
actorinfo_t *create_roket(sfTexture *texture, sfVector2f pos);
int move_roket(hunter_data_t *infos, actorinfo_t *actor);
int render_roket(sfRenderWindow *window, actorinfo_t *actor);

int add_shield(hunter_data_t *game);
int add_crusader(hunter_data_t *game);

// Button
int button_move(hunter_data_t *game, buttoninfo_t *actor);
buttoninfo_t *create_button(sfTexture *texture, int (*action)(), sfVector2f
    pos, sfVector2f size);
buttoninfo_t *get_button_from_id(button_t *start, char *id);
button_t *add_button(button_t *current, char *id, buttoninfo_t *infos);
button_t *load_game_buttons(textures_t *texture);
int check_buttons(hunter_data_t *game, button_t *buttons);

void add_yohann(actor_t **head, sfTexture *texture);
int move_yohann(hunter_data_t *infos, actorinfo_t *actor);


#endif
