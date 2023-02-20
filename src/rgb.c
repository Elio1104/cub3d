#include "../inc/cubed.h"

int line_not_empty(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if(!str || !*str)
        return(0);
    while(str[i])
    {
        if(str[i] != ' ' || str[i] != '\n')
            count++;
        i++;
    }
    return(count);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int get_rgb(char **tab)
{
    int r;
    int g;
    int b;

    r = ft_atoi(tab[0]);
    b = ft_atoi(tab[1]);
    g = ft_atoi(tab[2]);
    if(r < 0 || r > 255 || b < 0 || b > 255 || g < 0 || g > 255)
        return (-1);
    return(create_trgb(0, r, g, b));
}

void stock_rgb(t_game *game, char **tab, int *rgb, char *line)
{
    char **new_tab;

    if(!tab[0] || !tab[1] || tab[2])
    {
        free_close(game, line, tab);
        free_struct(game);
        ft_error("Wrong texture argument");
    }
    new_tab = ft_split(tab[1], ',');
    if(!new_tab)
    {
        free_close(game, line, tab);
        free_struct(game);
        ft_error("Malloc ft_split failed");
    }
    if(!new_tab[0] || !new_tab[1] || !new_tab[2] || new_tab[3])
    {
        free_tab(new_tab);
        free_close(game, line, tab);
        free_struct(game);
        ft_error("Wrong rgb");
    }
    *rgb = get_rgb(new_tab);
    free_tab(new_tab);
    if(*rgb == -1)
    {
        free_struct(game);
        free_close(game, line, tab);
        ft_error("Wrong rgb");
    }
}