/*
** EPITECH PROJECT, 2024
** LINKED_SOUNDS_LIST
** File description:
** Sounds linked list related functions
*/
#include "../../../include/my_hunter.h"

static void swap_actors(actor_t **begin, actor_t *current)
{
    actor_t *next = current->next;

    current->next = next->next;
    if (next->next)
        next->next->prev = current;
    next->prev = current->prev;
    if (current->prev)
        current->prev->next = next;
    else
        *begin = next;
    next->next = current;
    current->prev = next;
}

static void sort_sub(actor_t **begin, actor_t *current, int *swapped)
{
    *swapped = 0;
    for (current = *begin; current->next; current = current->next) {
        if (current->infos->zindex > current->next->infos->zindex) {
            swap_actors(begin, current);
            *swapped = 1;
        }
    }
}

void sort_actor_by_index(actor_t **begin)
{
    actor_t *current = *begin;
    int swapped;

    if (!begin || !*begin)
        return;
    do {
        sort_sub(begin, current, &swapped);
    } while (swapped);
}
