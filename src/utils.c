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
    free_texture(game);
}