#include "../inc/cubed.h"

int check_line(char *line)
{
    int i;

    i = 0;
    if (!line)
        return (2); //vide
    while (line[i])
    {
        if (line[i] != ' ' || line[i] != '\n')
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
    }
    if (check_line(line) == 2)
        ft_error("Invalid map area");
    while (1)
    {
        buffer = get_next_line(fd);
        if (!buffer)
            break ;
        line = ft_strjoin(line, buffer);
    }
    return (line);
}