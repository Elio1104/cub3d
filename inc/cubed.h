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
    int         orientation;
    t_texture   texture;
}   t_game;

# define NORTH 1;
# define SOUTH 2;
# define EAST 3;
# define WEST 4;

# define NO_PL 101
# define TOO_MUCH_PL 102
# define WRONG_FILL 103
# define WRONG_LAYOUT 104

//main
void    get_file(char **argv, t_game *game);
void	checking_arg(int argc, char **argv);

//map
int     check_line(char *line);
char    *get_map(int fd);
void    check_nswe(char *line, t_game *game);

//error
void    ft_error(char *str);
void    ft_error_code(int code);
char    *code_erreur(int code);

#endif