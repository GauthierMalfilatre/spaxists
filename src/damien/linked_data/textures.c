/*
** EPITECH PROJECT, 2024
** LINKED_TEXTURES_LIST
** File description:
** Textures linked list related functions
*/
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include "../../../include/my.h"
#include "../../../include/my_hunter.h"

sfTexture *get_texture_from_id(textures_t *start, char *id)
{
    for (textures_t *temp = start; temp; temp = temp->next) {
        if (!my_strcmp(id, temp->id)) {
            return temp->texure;
        }
    }
    return (void *) 0;
}

textures_t *add_texture(textures_t *current, char *id, char *path)
{
    textures_t *new = malloc(sizeof(textures_t));

    new->id = my_strdup(id);
    new->next = current;
    new->texure = sfTexture_createFromFile(path, (void *) 0);
    return new;
}
