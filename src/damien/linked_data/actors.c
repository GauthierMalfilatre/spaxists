/*
** EPITECH PROJECT, 2024
** LINKED_MUSCIS_LIST
** File description:
** Musics linked list related functions
*/
#include <SFML/Audio.h>
#include <stdlib.h>
#include "../../../include/my.h"
#include "../../../include/my_hunter.h"
#include <stdlib.h>

actorinfo_t *get_actor_from_id(actor_t *start, char *id)
{
    for (actor_t *temp = start; temp; temp = temp->next) {
        if (!my_strcmp(id, temp->id)) {
            return temp->infos;
        }
    }
    return (void *) 0;
}

actor_t *add_actor(actor_t *current, char *id, actorinfo_t *infos)
{
    actor_t *new = malloc(sizeof(actor_t));

    new->id = my_strdup(id);
    new->next = current;
    if (current) {
        current->prev = new;
    }
    new->prev = (void *) 0;
    new->infos = infos;
    return new;
}
