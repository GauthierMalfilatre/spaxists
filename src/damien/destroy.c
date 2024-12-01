/*
** EPITECH PROJECT, 2024
** DESTROY
** File description:
** Destroy game related functions
*/
#include "../../include/my_hunter.h"

static int destroy_musics(music_t *music)
{
    if (!music) {
        return 1;
    }
    if (music->next) {
        destroy_musics(music->next);
    }
    sfMusic_destroy(music->music);
    free(music->id);
    free(music);
    return 0;
}

static int destroy_sounds(sound_t *sounds)
{
    if (!sounds) {
        return 1;
    }
    if (sounds->next) {
        destroy_sounds(sounds->next);
    }
    sfSoundBuffer_destroy(sounds->soudbuffer);
    sfSound_destroy(sounds->sound);
    free(sounds->id);
    free(sounds);
    return 0;
}

static int destroy_textures(textures_t *texture)
{
    if (!texture) {
        return 1;
    }
    if (texture->next) {
        destroy_textures(texture->next);
    }
    sfTexture_destroy(texture->texure);
    free(texture->id);
    free(texture);
    return 0;
}

static int destroy_buttons(button_t *button)
{
    if (!button) {
        return 1;
    }
    if (button->next) {
        destroy_buttons(button->next);
    }
    sfSprite_destroy(button->infos->sprite);
    if (button->infos->clock)
        sfClock_destroy(button->infos->clock);
    free(button->id);
    free(button->infos);
    free(button);
    return 0;
}

static int destroy_actors(actor_t *actor)
{
    if (!actor) {
        return 1;
    }
    if (actor->next) {
        destroy_actors(actor->next);
    }
    sfSprite_destroy(actor->infos->sprite);
    if (actor->infos->clock)
        sfClock_destroy(actor->infos->clock);
    free(actor->id);
    free(actor->infos);
    free(actor);
    return 0;
}

int destroy_scenes(scenes_t *scene)
{
    if (!scene) {
        return 1;
    }
    if (scene->next) {
        destroy_scenes(scene->next);
    }
    sfSprite_destroy(scene->infos->background);
    destroy_buttons(scene->infos->button);
    destroy_actors(scene->actors);
    free(scene->infos);
    free(scene->id);
    free(scene);
    return 0;
}

int destroy_game(hunter_data_t *game)
{
    sfRenderWindow_destroy(game->window);
    free(game->actual_scene);
    destroy_textures(game->textures);
    destroy_musics(game->musics);
    destroy_sounds(game->sounds);
    destroy_scenes(game->scenes);
    sfView_destroy(game->view);
    free(game);
    return 0;
}
