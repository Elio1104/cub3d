/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:26:21 by alondot           #+#    #+#             */
/*   Updated: 2023/02/27 14:28:33 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubed.h"

void	check_layout(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0')
				check_error_map(game, i, j);
			j++;
		}
		i++;
	}
}

void	get_player(t_game *game)
{
	if (game->orientation == NORTH)
	{
		game->player.dir_y = -1;
		game->player.plane_x = (double)FOV;
	}
	else if (game->orientation == SOUTH)
	{
		game->player.dir_y = 1;
		game->player.plane_x = -(double)FOV;
	}
	else if (game->orientation == EAST)
	{
		game->player.dir_x = 1;
		game->player.plane_y = (double)FOV;
	}
	else if (game->orientation == WEST)
	{
		game->player.dir_x = -1;
		game->player.plane_y = -(double)FOV;
	}
}

int	nswe(t_game *game, int i, int j)
{
	if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
		|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
	{
		if (game->orientation != 0)
			ft_error_code(TOO_MUCH_PL, game);
		if (game->map[i][j] == 'N')
			game->orientation = NORTH;
		if (game->map[i][j] == 'S')
			game->orientation = SOUTH;
		if (game->map[i][j] == 'E')
			game->orientation = EAST;
		if (game->map[i][j] == 'W')
			game->orientation = WEST;
		game->player.x = j + 0.5;
		game->player.y = i + 0.5;
		game->map[i][j] = '0';
	}
	else if (game->map[i][j] != '1' && game->map[i][j] != '0'
		&& game->map[i][j] != ' ' && game->map[i][j] != '\n')
		ft_error_code(WRONG_FILL, game);
	return (0);
}

void	check_nswe(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			nswe(game, i, j);
			j++;
		}
		i++;
	}
	if (game->orientation == 0)
		ft_error_code(NO_PL, game);
	get_player(game);
}

char	**get_map(int fd, char *line)
{
	char	*buffer;
	char	**map;

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
