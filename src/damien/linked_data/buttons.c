/*
** EPITECH PROJECT, 2024
** LINKED_MUSCIS_LIST
** File description:
** Musics linked list related functions
*/
#include "../../../include/my_hunter.h"

buttoninfo_t *get_button_from_id(button_t *start, char *id)
{
    for (button_t *temp = start; temp; temp = temp->next) {
        if (!my_strcmp(id, temp->id)) {
            return temp->infos;
        }
    }
    return (void *) 0;
}

button_t *add_button(button_t *current, char *id, buttoninfo_t *infos)
{
    button_t *new = malloc(sizeof(button_t));

    new->id = my_strdup(id);
    new->next = current;
    if (current) {
        current->prev = new;
    }
    new->prev = (void *) 0;
    new->infos = infos;
    return new;
}
