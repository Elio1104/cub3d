#include "../inc/cubed.h"

void    ft_error(char *str)
{
    printf("Error\n%s\n", str);
    exit (1);
}

void    get_file(char **argv, t_game *game)
{
    int fd;
    char *buf;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("The map could not be read.");
    buf = get_map(fd);
    printf("%s", buf);
    check_nswe(buf, game);
    close(fd);
}

void	checking_arg(int argc, char **argv)
{
	if (argc != 2)
		ft_error("Invalid number of arguments. Must be 2.");
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		ft_error("Invalid file type. Must be: \"<name>.cub\"");
}

int main(int argc, char **argv)
{
    t_game game;
    char **map;

    game.orientation = 0;
    map = NULL;
    checking_arg(argc, argv);
    get_file(argv, &game);
}