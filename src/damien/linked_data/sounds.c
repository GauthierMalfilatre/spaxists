/*
** EPITECH PROJECT, 2024
** LINKED_SOUNDS_LIST
** File description:
** Sounds linked list related functions
*/
#include "../../../include/my.h"
#include "../../../include/my_hunter.h"

sfSound *get_sound_from_id(sound_t *start, char *id)
{
    for (sound_t *temp = start; temp; temp = temp->next) {
        if (!my_strcmp(id, temp->id)) {
            return temp->sound;
        }
    }
    return (void *) 0;
}

sound_t *add_sound(sound_t *current, char *id, char *path)
{
    sound_t *new = malloc(sizeof(sound_t));

    new->id = my_strdup(id);
    new->next = current;
    new->sound = sfSound_create();
    new->soudbuffer = sfSoundBuffer_createFromFile(path);
    sfSound_setBuffer(new->sound, new->soudbuffer);
    return new;
}
