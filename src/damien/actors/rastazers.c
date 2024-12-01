/*
** EPITECH PROJECT, 2024
** rastazerS
** File description:
** rastazers related functions
*/
#include "../../../include/my.h"
#include "../../../include/my_hunter.h"
#include <time.h>

static void aa_sprite(actorinfo_t *new, sfTexture *texture)
{
    sfSprite_setTexture(new->sprite, texture, sfTrue);
    sfSprite_setTextureRect(new->sprite, (sfIntRect) {32, 0, 32, 32});
    sfSprite_setScale(new->sprite, new->size);
    sfSprite_setPosition(new->sprite, (sfVector2f) {rand() % WIND_W, rand()
        % (WIND_H - 32 * 5 - 500)});
    return;
}

static actorinfo_t *create_rastazer(sfTexture *texture, sfVector2f *velocity)
{
    actorinfo_t *new = malloc(sizeof(actorinfo_t));

    new->size = (sfVector2f) {5.0f, 5.0f};
    new->clock = sfClock_create();
    new->sprite = sfSprite_create();
    aa_sprite(new, texture);
    new->is_alive = sfTrue;
    new->vel = *velocity;
    new->move = &move_rastazer;
    new->render = &render;
    new->life = 1;
    new->zindex = 2;
    new->delta_t = 0;
    new->shield = 1;
    new->cooldown = 3;
    new->texturex = 0;
    return new;
}

static actorinfo_t *create_yohann(sfTexture *texture, sfVector2f *velocity)
{
    actorinfo_t *new = create_rastazer(texture, velocity);

    new->move = &move_yohann;
    new->vel.x = 2000.f;
    new->cooldown = 0.5;
    return new;
}

static void delete_rastazer(actor_t **head, actor_t *rastazer)
{
    if (rastazer->prev)
        rastazer->prev->next = rastazer->next;
    else
        *head = rastazer->next;
    if (rastazer->next)
        rastazer->next->prev = rastazer->prev;
    free(rastazer->id);
    sfClock_destroy(rastazer->infos->clock);
    sfSprite_destroy(rastazer->infos->sprite);
    free(rastazer->infos);
    free(rastazer);
}

int update_rastazers(hunter_data_t *game, scenes_t *scene)
{
    for (actor_t *temp = scene->actors; temp; temp = temp->next) {
        if (!my_strcmp(temp->id, "a_rastazer") && check_collision(temp->
            infos->sprite, GETTA(scene->actors, "a_cursor")->sprite)) {
            delete_rastazer(&scene->actors, temp);
            game->coin += 10;
            break;
        }
    }
    return 0;
}

int move_rastazer(hunter_data_t *infos, actorinfo_t *actor)
{
    sfVector2f pos = sfSprite_getPosition(actor->sprite);

    actor->delta_t = sfTime_asSeconds(sfClock_restart(actor->clock));
    actor->cooldown -= actor->delta_t;
    sfSprite_move(actor->sprite, fvectmul(actor->vel, actor->delta_t, 1.f));
    actor->texturex += actor->delta_t;
    if ((pos.x + (32 * actor->size.x) > WIND_W && actor->vel.x > 0) ||
        (pos.x - (32 * actor->size.x) < 0 && actor->vel.x < 0)) {
        actor->vel = fvectmul(actor->vel, -1.0f, 0.0f);
        sfSprite_setScale(actor->sprite, (sfVector2f)
            {sfSprite_getScale(actor->sprite).x * -1, actor->size.y});
    }
    if ((int) actor->cooldown < 0) {
        actor->cooldown = 3;
        GETS(infos->scenes, "s_game")->actors = ADDA(GETS(infos->scenes,
            "s_game")->actors, "a_roket", create_roket(GETT(infos->textures,
                "t_roket"), sfSprite_getPosition(actor->sprite)));
    }
    return 0;
}

void add_yohann(actor_t **head, sfTexture *texture)
{
    *head = ADDA(*head, "a_yohann", create_yohann(texture, &(sfVector2f)
        {1000.f, 0.f}));
}

void add_n_rastazer(actor_t **head, sfTexture *texture, int n,
    sfVector2f *velocity)
{
    for (int i = 0; i < n; i++) {
        *head = ADDA(*head, "a_rastazer", create_rastazer(texture, velocity));
    }
    return;
}
