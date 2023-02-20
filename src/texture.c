#include "../inc/cubed.h"

void free_close(t_game *game, char *str, char **tab)
{
    free(str);
    close(game->fd);
    free_tab(tab);
}

void    stock_texture(t_game *game, char **tab, char **texture, char *line)
{
    if(!tab[0] || !tab[1] || tab[2])
    {
        free_close(game, line, tab);
        free_struct(game);
        ft_error("Wrong arguments");
    }
    *texture = ft_strdup(tab[1]);
    if(!*texture)
    {
        free_close(game, line, tab);
        free_struct(game);
        ft_error("Malloc in ft_strdup failed");
    }
}

int is_texture(t_game *game, char **tab, char *line)
{
    tab = ft_split(line, ' ');
    if(!tab)
    {
        free_close(game, line, 0);
        free_struct(game);
        ft_error("Malloc split failed");
    }
    if(ft_strcmp(tab[0], "NO") == 0)
        stock_texture(game, tab, &game->texture.north, line);
    else if(ft_strcmp(tab[0], "SO") == 0)
        stock_texture(game, tab, &game->texture.south, line);
    else if(ft_strcmp(tab[0], "WE") == 0)
        stock_texture(game, tab, &game->texture.west, line);
    else if(ft_strcmp(tab[0], "EA") == 0)
        stock_texture(game, tab, &game->texture.east, line);
    else if(ft_strcmp(tab[0], "F") == 0)
        stock_rgb(game, tab, &game->texture.ceilling, line);
    else if(ft_strcmp(tab[0], "C") == 0)
        stock_rgb(game, tab, &game->texture.floor, line);
    else
        return(0);
    return(1);
}

void check_texture(t_game *game)
{
    if(game->texture.ceilling == -1 || game->texture.floor == -1 || game->texture.south == NULL || game->texture.north == NULL || game->texture.east == NULL || game->texture.west == NULL)
    {
        close(game->fd);
        free_struct(game);
        ft_error("Not enough texture");
    }
}

void get_texture(t_game *game)
{
    char *line;
    char **tab;

    tab = NULL;
    while(1)
    {
        line = get_next_line(game->fd);
        if(!line)
            break;
        if(line_not_empty(line) == 0 || line[0] == '\n')
        {
            free(line);
            continue ;
        }
        if(!is_texture(game, tab, line))
            break;
        free(line);
        free_tab(tab);
    }
    if (line)
        free(line);
    free_tab(tab);
    check_texture(game);
}