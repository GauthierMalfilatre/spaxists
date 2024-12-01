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

sfMusic *get_music_from_id(music_t *start, char *id)
{
    for (music_t *temp = start; temp; temp = temp->next) {
        if (!my_strcmp(id, temp->id)) {
            return temp->music;
        }
    }
    return (void *) 0;
}

music_t *add_music(music_t *current, char *id, char *path)
{
    music_t *new = malloc(sizeof(music_t));

    new->id = my_strdup(id);
    new->next = current;
    new->music = sfMusic_createFromFile(path);
    return new;
}
