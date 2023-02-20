#include "../inc/cubed.h"

int check_nswe(t_game *game)
{
    int i;
    int j;

    i = 0;
    while(game->map[i])
    {
        while(game->map[i][j])
        {
            if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' || game->map[i][j] == 'E')
            {
                if (game->orientation != 0)
                    return(TOO_MUCH_PL);
                if (game->map[i][j] == 'N')
                    game->orientation = NORTH;
                if (game->map[i][j] == 'S')
                    game->orientation = SOUTH;
                if (game->map[i][j] == 'E')
                    game->orientation = EAST;
                if (game->map[i][j] == 'W')
                    game->orientation = WEST;
            }
            else if (game->map[i][j] != '1' && game->map[i][j] != '0' && game->map[i][j] != ' ' && game->map[i][j] != '\n')
                return(WRONG_FILL);
            j++;
        }
        i++;
    }
    if (game->orientation == 0)
        return(NO_PL);
    return (0);
}

char **get_map(int fd, char *line)
{
    char    *buffer;
    char    **map;

    while (1)
    {
        buffer = get_next_line(fd);
        if (!buffer)
            break ;
        line = ft_strjoin(line, buffer);
    }
    map = ft_split(line, '\n');
    free(line);
    return (map);
}