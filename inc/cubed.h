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
    int     floor;
    int     ceilling;
}   t_texture;

typedef struct s_game {
    char        **map;
    int         fd;
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
void	checking_arg(int argc, char **argv, t_game *game);

//map
char    **get_map(int fd, char *line);
int     check_nswe(t_game *game);

//texture
void free_close(char *str, char **tab);
void    stock_texture(t_game *game, char **tab, char **texture, char *line);
int is_texture(t_game *game, char *line);
void check_texture(t_game *game);
char *get_texture(t_game *game);

//rgb
int line_not_empty(char *str);
int	create_trgb(int t, int r, int g, int b);
int get_rgb(char **tab);
void stock_rgb(t_game *game, char **tab, int *rgb, char *line);


//utils
void free_tab(char **tab);
void free_texture(t_game *game);
void free_struct(t_game *game);
void print_map(char **map);

//error
void    ft_error(char *str, t_game *game);
void    ft_error_code(int code, t_game *game);
char    *code_erreur(int code);

#endif