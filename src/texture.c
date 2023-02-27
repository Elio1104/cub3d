#include "../inc/cubed.h"

void free_close(char *str, char **tab)
{
    free(str);
    free_tab(tab);
}

void    stock_texture(t_game *game, char **tab, char **texture, char *line)
{
    if(!tab[0] || !tab[1] || (tab[2] && *tab[2] != '\n'))
    {
        free_close(line, tab);
        ft_error("Wrong arguments", game);
    }
    *texture = ft_strdup(tab[1]);
    if(!*texture)
    {
        free_close(line, tab);
        ft_error("Malloc in ft_strdup failed", game);
    }
}

int is_texture(t_game *game, char *line)
{
    char **tab;

    tab = ft_split(line, ' ');
    if(!tab)
    {
        free(line);
        ft_error("Malloc split failed", game);
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
    {
        free_tab(tab);
        return(0);
    }
    free_tab(tab);
    return(1);
}

void check_texture(t_game *game, char *line)
{
    if(game->texture.ceilling == -1 || game->texture.floor == -1 || game->texture.south == NULL || game->texture.north == NULL || game->texture.east == NULL || game->texture.west == NULL)
    {
        free(line);
        ft_error("Not enough texture", game);
    }
}

t_data texture_load(char *path, t_game *game)
{
    t_data	obj;
    int i;

    i = ft_strlen(path);
    if(path[i - 1] == '\n')
        path[i - 1] = '\0';
	obj.img = mlx_xpm_file_to_image(game->mlx, path,
			&obj.bits_per_pixel, &obj.line_length);
	if (obj.img == 0)
		ft_error("Load texture", game);
	obj.addr = mlx_get_data_addr(obj.img, &obj.bits_per_pixel,
			&obj.line_length, &obj.endian);
	return (obj);
}

void init_texture(t_game *game)
{
    game->t_north = texture_load(game->texture.north, game);
    game->t_south = texture_load(game->texture.south, game);
    game->t_east = texture_load(game->texture.east, game);
    game->t_west = texture_load(game->texture.west, game);
}

char    *get_texture(t_game *game)
{
    char *line;

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
        if(!is_texture(game, line))
            break;
        free(line);
    }
    check_texture(game, line);
    init_texture(game);
    return (line);
}
