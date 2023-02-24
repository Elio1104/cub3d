#include "../inc/cubed.h"

void    get_file(char **argv, t_game *game)
{
    char *buf;
    int ret;

	game->fd = open(argv[1], O_RDONLY);
	if (game->fd == -1)
		ft_error("The map could not be read.", game);
    buf = get_texture(game);
    game->map = get_map(game->fd, buf);
    ret = check_nswe(game);
    if (ret != 0)
        ft_error_code(ret, game);
    check_layout(game);
    print_map(game->map);
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

void init_player(t_game *game)
{
    game->orientation = 0;
    game->player.dir_x = 0;
    game->player.dir_y = 0;
    game->player.plane_x = 0;
    game->player.plane_y = 0;
}

void    init_struct(t_game *game)
{
    game->map = NULL;
    game->fd = 0;
    game->texture.ceilling = -1;
    game->texture.floor = -1;
    game->texture.north = NULL;
    game->texture.south = NULL;
    game->texture.east = NULL;
    game->texture.west = NULL;
    init_player(game);
    game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_error("Error\nMlx doesn't init", game);
	game->mlx_win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
}

int close_window(t_game *game)
{
    free_struct(game);
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit (1);
}

int main(int argc, char **argv)
{
    t_game game;

    init_struct(&game);
    checking_arg(argc, argv, &game);
    get_file(argv, &game);
    mlx_loop_hook(game.mlx, &raycasting, &game);
    mlx_hook(game.mlx_win, 2, 0, &key_events, &game);
	mlx_hook(game.mlx_win, 17, 0, &close_window, &game);
    mlx_loop(game.mlx);
}