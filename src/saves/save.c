/*
** EPITECH PROJECT, 2024
** SAVE
** File description:
** Spaxists saves manager file
*/
#include "../../include/my_hunter.h"
#include <sys/stat.h>
#include <fcntl.h>

int load_save(char *path)
{
    char kronk_buffer[9];
    int fd = open(path, O_RDONLY | O_CREAT, 0755);
    int i = 0;

    if (fd == -1) {
        return 0 * my_printf("Error while loading file %s\n", path);
    }
    for (; read(fd, &kronk_buffer[i], 1) > 0 && i < 8; i++);
    kronk_buffer[i] = '\0';
    close(fd);
    return my_getnbr(kronk_buffer);
}

int save(char *path, int coins)
{
    char *kronk_buffer = int_to_str(coins);
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0755);

    if (fd == -1) {
        return my_printf("Error while loading file %s\n", path);
    }
    if (write(fd, kronk_buffer, my_strlen(kronk_buffer)) == -1) {
        return my_printf("Error while reading file %s\n", path);
    }
    free(kronk_buffer);
    close(fd);
    return 0;
}
