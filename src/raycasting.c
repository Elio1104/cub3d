/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:30:02 by alondot           #+#    #+#             */
/*   Updated: 2023/02/27 14:39:03 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubed.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

unsigned int	my_mlx_get_color(t_data *data, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	draw_verline(t_game *game, int i, int draw_start, int draw_end, int color)
{
	while (draw_start <= draw_end)
	{
		my_mlx_pixel_put(&game->mlx_img, i, draw_start, color);
		draw_start++;
	}
}

void	init_value(t_game *game, t_raycasting *ray, int i)
{
	ray->camera_x = 2 * i / (double)WIN_WIDTH - 1;
	ray->ray_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_x == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = ft_abs(1 / ray->ray_x);
	if (ray->ray_y == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = ft_abs(1 / ray->ray_y);
}

void	init_side_dist(t_game *game, t_raycasting *ray)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->sideDistX = (game->player.x - ray->map_x) * ray->deltaDistX;
	}
	else
	{
		ray->step_x = 1;
		ray->sideDistX = (ray->map_x + 1.0 - game->player.x) * ray->deltaDistX;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->sideDistY = (game->player.y - ray->map_y) * ray->deltaDistY;
	}
	else
	{
		ray->step_y = 1;
		ray->sideDistY = (ray->map_y + 1.0 - game->player.y) * ray->deltaDistY;
	}
}

void	dist_wall(t_game *game, t_raycasting *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
		}
	}
	if (ray->side == 0)
		ray->wall_distance = (ray->sideDistX - ray->deltaDistX);
	else
		ray->wall_distance = (ray->sideDistY - ray->deltaDistY);
}

void	draw_texture(t_game *game, t_raycasting *ray, int text_x, int i)
{
	int		j;
	double	step;
	double	pos;
	int		color;

	j = 0;
	step = 1.0 * texHeight / ray->line_height;
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

void	draw_line(t_game *game, t_raycasting *ray, int i)
{
	double	wall_x;
	int		text_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->wall_distance * ray->ray_y;
	else
		wall_x = game->player.x + ray->wall_distance * ray->ray_x;
	wall_x -= floor((wall_x));
	text_x = (int)(wall_x * (double)(texWidth));
	if (ray->side == 0 && ray->ray_x > 0)
		text_x = texWidth - text_x - 1;
	if (ray->side == 1 && ray->ray_y < 0)
		text_x = texWidth - text_x - 1;
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_distance);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->draw_start != 0)
		draw_verline(game, i, 0, ray->draw_start, game->texture.ceilling);
	if (ray->draw_end != WIN_HEIGHT - 1)
		draw_verline(game, i, ray->draw_end,
			WIN_HEIGHT - 1, game->texture.floor);
	draw_texture(game, ray, text_x, i);
}

int	raycasting(t_game *game)
{
	int				i;
	t_raycasting	*ray;

	game->mlx_img.img = mlx_new_image(game->mlx,
			(int)WIN_WIDTH, (int)WIN_HEIGHT);
	game->mlx_img.addr = mlx_get_data_addr(game->mlx_img.img,
			&game->mlx_img.bits_per_pixel, &game->mlx_img.line_length,
			&game->mlx_img.endian);
	ray = &game->raycast;
	move_y_player(game);
	move_x_player(game);
	move_cam(game);
	i = 0;
	while (i < WIN_WIDTH)
	{
		init_value(game, ray, i);
		init_side_dist(game, ray);
		dist_wall(game, ray);
		draw_line(game, ray, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->mlx_img.img);
	return (0);
}
