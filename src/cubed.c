#include "../inc/cubed.h"

void    get_file(char **argv, t_game *game)
{
    int fd;
    char *buf;
    int ret;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("The map could not be read.");
    buf = get_map(fd);
    printf("%s", buf); // a retirer
    ret = check_nswe(buf, game);
    if (ret != 0)
        ft_error_code(ret);
    close(fd);
}

void	checking_arg(int argc, char **argv)
{
    int len;

	if (argc != 2)
		ft_error("Invalid number of arguments. Must be 2.");
    len = ft_strlen(argv[1]) - 4;
	if (ft_strcmp(argv[1] + len, ".cub"))
		ft_error("Invalid file type. Must be: \"<name>.cub\"");
}

int main(int argc, char **argv)
{
    t_game game;

    game.orientation = 0;
    checking_arg(argc, argv);
    get_file(argv, &game);
}