/*
** EPITECH PROJECT, 2024
** rastazerS
** File description:
** rastazers related functions
*/
#include "../../../include/my_hunter.h"

int move_yohann(hunter_data_t *infos, actorinfo_t *actor)
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
    if (actor->cooldown < 0.f) {
        actor->cooldown = 0.1f;
        GETS(infos->scenes, "s_game")->actors = ADDA(GETS(infos->scenes,
            "s_game")->actors, "a_roket", create_roket(GETT(infos->textures,
                "t_roket"), sfSprite_getPosition(actor->sprite)));
    }
    return 0;
}
