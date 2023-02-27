/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:48:07 by alondot           #+#    #+#             */
/*   Updated: 2023/02/27 14:48:55 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubed.h"

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void	free_texture(t_game *game)
{
	if (game->texture.north)
		free(game->texture.north);
	if (game->texture.south)
		free(game->texture.south);
	if (game->texture.east)
		free(game->texture.east);
	if (game->texture.west)
		free(game->texture.west);
}

void	free_struct(t_game *game)
{
	if (game->map)
		free_tab(game->map);
	if (game->fd != 0)
		close(game->fd);
	free_texture(game);
    if(game->t_north.img)
        mlx_destroy_image(game->mlx, game->t_north.img);
    if(game->t_south.img)
        mlx_destroy_image(game->mlx, game->t_south.img);
    if(game->t_east.img)
        mlx_destroy_image(game->mlx, game->t_east.img);
    if(game->t_west.img)
        mlx_destroy_image(game->mlx, game->t_west.img);
}

double	ft_abs(double x)
{
	if (x >= 0)
		return (x);
	return (-x);
}

int	close_window(t_game *game)
{
	free_struct(game);
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit (1);
}
