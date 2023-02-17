#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/ft_printf.h"
# include "../lib/libft/includes/get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_texture {
    char    *north;
    char    *south;
    char    *east;
    char    *west;
}   t_texture;

typedef struct s_game {
    char        **map;
    t_texture   texture;
}   t_game;

//main
void    ft_error(char *str);
void    get_file(char **map, char **argv);
void	checking_arg(int argc, char **argv);

//map
int check_line(char *line);
char *get_map(int fd);

#endif