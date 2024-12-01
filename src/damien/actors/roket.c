/*
** EPITECH PROJECT, 2024
** ROKET
** File description:
** Plague roket related functions
*/
#include "../../../include/my_hunter.h"

static int move_roket_sub(hunter_data_t *infos, actorinfo_t *actor)
{
    actorinfo_t *station = GETTA(GETS(infos->scenes,
        infos->actual_scene)->actors, "a_station");

    if (check_collision_center(actor->sprite, GETTA(GETS(infos->scenes,
        "s_game")->actors, "a_station")->sprite) && actor->is_alive > 0) {
        actor->is_alive = 0;
        sfSound_play(GETTO(infos->sounds, "so_roket"));
        if (station->shield > 0) {
            station->shield -= 10.0f;
        } else {
            station->life -= 10.0f;
        }
    }
    if (actor->is_alive <= 0) {
        actor->is_alive -= actor->delta_t;
        return 1;
    }
    return 0;
}

static void delete_roket(actor_t **head, actor_t *roket)
{
    if (roket->infos->is_alive > -1.5) {
        return;
    }
    if (roket->prev)
        roket->prev->next = roket->next;
    else
        *head = roket->next;
    if (roket->next)
        roket->next->prev = roket->prev;
    free(roket->id);
    sfClock_destroy(roket->infos->clock);
    sfSprite_destroy(roket->infos->sprite);
    free(roket->infos);
    free(roket);
}

int update_rokets(hunter_data_t *game, scenes_t *scene)
{
    actor_t *temp = scene->actors;
    actor_t *next = NULL;

    while (temp) {
        next = temp->next;
        if (!my_strcmp(temp->id, "a_roket")) {
            delete_roket(&scene->actors, temp);
        }
        temp = next;
    }
    return 0;
}

actorinfo_t *create_roket(sfTexture *texture, sfVector2f pos)
{
    actorinfo_t *new = malloc(sizeof(actorinfo_t));

    new->size = (sfVector2f) {2.0f, 2.0f};
    new->clock = sfClock_create();
    new->sprite = sfSprite_create();
    sfSprite_setTexture(new->sprite, texture, sfTrue);
    sfSprite_setTextureRect(new->sprite, (sfIntRect) {0, 0, 32, 32});
    sfSprite_setScale(new->sprite, new->size);
    sfSprite_setPosition(new->sprite, pos);
    new->is_alive = 1;
    new->vel = (sfVector2f) {0.0f, 400.0f};
    new->move = &move_roket;
    new->render = &render_roket;
    new->life = 1;
    new->delta_t = 0;
    new->zindex = 1;
    new->texturex = 0;
    new->shield = 1;
    return new;
}

int move_roket(hunter_data_t *infos, actorinfo_t *actor)
{
    sfVector2f pos = sfSprite_getPosition(actor->sprite);
    sfVector2f station = sfSprite_getPosition(GETTA(GETS(infos->scenes,
        "s_game")->actors, "a_station")->sprite);
    double angle = asin(pos.y / get_norme(actor->vel, station)) * 180.0f
        / 3.141592653589793238;

    actor->delta_t = sfTime_asSeconds(sfClock_restart(actor->clock));
    if (move_roket_sub(infos, actor))
        return 0;
    station = (sfVector2f) {station.x + (32.0f * 8.0f) / 2, station.y +
        (32.0f * 8.0f) / 2};
    if (pos.y > 500 && !actor->vel.x) {
        actor->vel.y = get_dir(pos, station, 400.0f).y;
        actor->vel.x = get_dir(pos, station, 400.0f).x;
        sfSprite_setRotation(actor->sprite, pos.x > station.x ? angle : -1 *
            angle);
    }
    sfSprite_move(actor->sprite, fvectmul(actor->vel, actor->delta_t,
        actor->delta_t));
    return 0;
}

int render_roket(sfRenderWindow *window, actorinfo_t *actor)
{
    actor->texturex = my_fmod((actor->texturex + actor->delta_t), 0.3);
    if (!(!actor->vel.x && actor->vel.y == 400.0f)) {
        sfSprite_setTextureRect(actor->sprite, (sfIntRect)
            {32 + (int) (actor->texturex * 10) * 32.f, 0, 32, 32});
    }
    if (actor->is_alive <= 0)
        sfSprite_setTextureRect(actor->sprite, (sfIntRect) {128, 0, 32, 32});
    sfRenderWindow_drawSprite(window, actor->sprite, sfFalse);
    return 0;
}
