#include "../inc/cubed.h"

int check_nswe(char *line, t_game *game)
{
    int i;

    i = 0;
    while(line[i])
    {
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
        {
            if (game->orientation != 0)
                return(TOO_MUCH_PL);
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
            return(WRONG_FILL);
        i++;
    }
    if (game->orientation == 0)
        return(NO_PL);
    return (0);
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

char *get_map(int fd, char *line)
{
    char    *buffer;

    while (1)
    {
        buffer = get_next_line(fd);
        if (!buffer)
            break ;
        line = ft_strjoin(line, buffer);
    }
    return (line);
}