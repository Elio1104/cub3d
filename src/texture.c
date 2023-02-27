/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:42:57 by alondot           #+#    #+#             */
/*   Updated: 2023/02/27 14:47:13 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubed.h"

unsigned int	my_mlx_get_color(t_data *data, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	check_texture(t_game *game, char *line)
{
	if (game->texture.ceilling == -1 || game->texture.floor == -1
		|| game->texture.south == NULL || game->texture.north == NULL
		|| game->texture.east == NULL || game->texture.west == NULL)
	{
		free(line);
		ft_error("Not enough texture", game);
	}
}

t_data	texture_load(char *path, t_game *game)
{
	t_data	obj;
	int		i;

	i = ft_strlen(path);
	if (path[i - 1] == '\n')
		path[i - 1] = '\0';
	obj.img = mlx_xpm_file_to_image(game->mlx, path,
			&obj.bits_per_pixel, &obj.line_length);
	if (obj.img == 0)
		ft_error("Load texture", game);
	obj.addr = mlx_get_data_addr(obj.img, &obj.bits_per_pixel,
			&obj.line_length, &obj.endian);
	return (obj);
}

void	init_texture(t_game *game)
{
	game->t_north = texture_load(game->texture.north, game);
	game->t_south = texture_load(game->texture.south, game);
	game->t_east = texture_load(game->texture.east, game);
	game->t_west = texture_load(game->texture.west, game);
}

char	*get_texture(t_game *game)
{
	char	*line;

	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		if (line_not_empty(line) == 0 || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (!is_texture(game, line))
			break ;
		free(line);
	}
	check_texture(game, line);
	init_texture(game);
	return (line);
}
