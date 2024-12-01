/*
** EPITECH PROJECT, 2024
** FRAMEBUFFER
** File description:
** Framebuffer functions
*/
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "../../include/my_hunter.h"

framebuffer_t *framebuffer_create(unsigned int width, unsigned int heigth)
{
    framebuffer_t *framebuffer = malloc(sizeof(framebuffer_t));

    framebuffer->width = width;
    framebuffer->heigth = heigth;
    framebuffer->buffer = malloc(sizeof(sfUint8) * 4 * width * heigth);
    if (!framebuffer->buffer) {
        return (void *) 0;
    }
    for (unsigned int i = 0; i < 4 * width * heigth; i++) {
        framebuffer->buffer[i] = 0;
    }
    return framebuffer;
}

void put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y,
    sfColor color)
{
    int i = 4 * (y * framebuffer->width + x);

    if (x >= framebuffer->width || y >= framebuffer->heigth) {
        return;
    }
    framebuffer->buffer[i] = color.r;
    framebuffer->buffer[i + 1] = color.g;
    framebuffer->buffer[i + 2] = color.b;
    framebuffer->buffer[i + 3] = color.a;
}

void draw_square(framebuffer_t *framebuffer, sfVector2u position,
    sfVector2u size, sfColor color)
{
    for (unsigned int i = position.y; i < position.y + size.y; i++) {
        for (unsigned int j = position.x; j < position.x + size.x; j++) {
            put_pixel(framebuffer, j, i, color);
        }
    }
}
