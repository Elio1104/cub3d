#include "../inc/cubed.h"

void    get_file(char **argv, t_game *game)
{
    char *buf;
    int ret;

	game->fd = open(argv[1], O_RDONLY);
	if (game->fd == -1)
		ft_error("The map could not be read.", game);
    get_texture(game);
    buf = get_map(game->fd);
    printf("%s", buf); // a retirer
    ret = check_nswe(buf, game);
    if (ret != 0)
        ft_error_code(ret, game);
    free(buf);
    close(game->fd);
    game->fd = 0;
}

void	checking_arg(int argc, char **argv, t_game *game)
{
    int len;

	if (argc != 2)
		ft_error("Invalid number of arguments. Must be 2.", game);
    len = ft_strlen(argv[1]) - 4;
	if (ft_strcmp(argv[1] + len, ".cub"))
		ft_error("Invalid file type. Must be: \"<name>.cub\"", game);
}

void    init_struct(t_game *game)
{
    game->fd = 0;
    game->orientation = 0;
    game->texture.ceilling = -1;
    game->texture.floor = -1;
    game->texture.north = NULL;
    game->texture.south = NULL;
    game->texture.east = NULL;
    game->texture.west = NULL;
}

int main(int argc, char **argv)
{
    t_game game;

    init_struct(&game);
    checking_arg(argc, argv, &game);
    get_file(argv, &game);
    free_struct(&game);
}