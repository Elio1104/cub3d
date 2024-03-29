/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:09:11 by alondot           #+#    #+#             */
/*   Updated: 2023/02/28 13:59:05 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubed.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_ceilling(t_game *game, int i, int draw_start, int draw_end)
{
	while (draw_start <= draw_end)
	{
		my_mlx_pixel_put(&game->mlx_img, i, draw_start, game->texture.ceilling);
		draw_start++;
	}
}

void	draw_floor(t_game *game, int i, int draw_start, int draw_end)
{
	while (draw_start <= draw_end)
	{
		my_mlx_pixel_put(&game->mlx_img, i, draw_start, game->texture.floor);
		draw_start++;
	}
}

void	draw_line(t_game *game, t_raycasting *ray, int i)
{
	double	wall_x;
	int		text_x;

	calculate_text_x(game, ray, &wall_x, &text_x);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->draw_start != 0)
		draw_ceilling(game, i, 0, ray->draw_start);
	if (ray->draw_end != WIN_HEIGHT - 1)
		draw_floor(game, i, ray->draw_end, WIN_HEIGHT - 1);
	draw_texture(game, ray, text_x, i);
}

void	draw_texture(t_game *game, t_raycasting *ray, int text_x, int i)
{
	int		j;
	double	step;
	double	pos;
	int		color;

	j = 0;
	step = 1.0 * TEX_HEIGHT / ray->line_height;
	pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	while (j + ray->draw_start < ray->draw_end)
	{
		if (game->raycast.side == 1 && game->raycast.ray_y < 0)
			color = my_mlx_get_color(&game->t_north, text_x, (int)pos);
		else if (game->raycast.side == 1 && game->raycast.ray_y > 0)
			color = my_mlx_get_color(&game->t_south, text_x, (int)pos);
		else if (game->raycast.side == 0 && game->raycast.ray_x < 0)
			color = my_mlx_get_color(&game->t_west, text_x, (int)pos);
		else
			color = my_mlx_get_color(&game->t_east, text_x, (int)pos);
		my_mlx_pixel_put(&game->mlx_img, i, j + ray->draw_start, color);
		pos += step;
		j++;
	}
}
