#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/ft_printf.h"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

//main
void    ft_error(char *str);
void    get_map(char **map, char **argv);
void	checking_arg(int argc, char **argv);

#endif