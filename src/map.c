#include "../inc/cubed.h"

void check_nswe(char *line, t_game *game)
{
    int i;

    i = 0;
    while(line[i])
    {
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
        {
            if (game->orientation != 0)
                ft_error("There can only be 1 player");
            if (line[i] == 'N')
                game->orientation = NORTH;
            if (line[i] == 'S')
                game->orientation = SOUTH;
            if (line[i] == 'E')
                game->orientation = EAST;
            if (line[i] == 'W')
                game->orientation = WEST;
        }
        else if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != '\n')
            ft_error("Map can only be '1', '0', ' ', 'W', 'E', 'S', 'N'");
        i++;
    }
    if (game->orientation == 0)
        ft_error("There must be 1 player");
}

int check_line(char *line)
{
    int i;

    i = 0;
    if (!line)
        return (2); //vide
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\n')
            return (1);//line remplie
        i++;
    }
    return (0); //que des espaces
}

char *get_map(int fd)
{
    char    *buffer;
    char    *line;

    if (fd < 1)
        return (NULL);
    while (1)
    {
        line = get_next_line(fd);
        if (check_line(line) != 0)
            break ;
        free(line);
    }
    while (1)
    {
        buffer = get_next_line(fd);
        if (!buffer)
            break ;
        line = ft_strjoin(line, buffer);
    }
    return (line);
}