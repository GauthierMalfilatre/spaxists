/*
** EPITECH PROJECT, 2024
** LINKED_MUSCIS_SCENES
** File description:
** Scenes linked list related functions
*/
#include "../../../include/my.h"
#include "../../../include/my_hunter.h"

sceneinfo_t *create_scene(sfMusic *theme, sfTexture *texture, int (*event)(),
    button_t *buttons)
{
    sceneinfo_t *new = malloc(sizeof(sceneinfo_t));

    new->background = sfSprite_create();
    sfSprite_setTexture(new->background, texture, sfFalse);
    new->button = buttons;
    new->theme = theme;
    new->event = event;
    return new;
}

scenes_t *get_scene_from_id(scenes_t *start, char *id)
{
    for (scenes_t *temp = start; temp; temp = temp->next) {
        if (!my_strcmp(id, temp->id)) {
            return temp;
        }
    }
    return (void *) 0;
}

scenes_t *add_scene(scenes_t *current, char *id, actor_t *actor,
    sceneinfo_t *infos)
{
    scenes_t *new = malloc(sizeof(scenes_t));

    new->actors = actor;
    new->infos = infos;
    new->id = my_strdup(id);
    new->next = current;
    return new;
}
