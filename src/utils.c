#include "../inc/cubed.h"

void free_tab(char **tab)
{
    int i;

    if(tab)
    {
        i = 0;
        while(tab[i])
        {
            free(tab[i]);
            i++;
        }
    }
    free(tab);
}

void free_texture(t_game *game)
{
    if(game->texture.north)
        free(game->texture.north);
    if(game->texture.south)
        free(game->texture.south);
    if(game->texture.east)
        free(game->texture.east);
    if(game->texture.west)
        free(game->texture.west);
}

void free_struct(t_game *game)
{
    if (game->map)
        free_tab(game->map);
    if (game->fd != 0)
        close(game->fd);
    free_texture(game);
}

double ft_abs(double x)
{
    if (x >= 0)
      return (x);
    return (-x);
}

void print_map(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        printf("%d : %s\n", i, map[i]);
        i++;
    }
}
