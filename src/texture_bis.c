/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:00:54 by alondot           #+#    #+#             */
/*   Updated: 2023/02/27 16:01:20 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubed.h"

void	stock_texture(t_game *game, char **tab, char **texture, char *line)
{
	if (!tab[0] || !tab[1] || (tab[2] && *tab[2] != '\n'))
	{
		free_close(line, tab);
		ft_error("Wrong arguments", game);
	}
	*texture = ft_strdup(tab[1]);
	if (!*texture)
	{
		free_close(line, tab);
		ft_error("Malloc in ft_strdup failed", game);
	}
}

int	strcmp_texture(t_game *game, char **tab, char *line)
{
	if (ft_strcmp(tab[0], "NO") == 0)
		stock_texture(game, tab, &game->texture.north, line);
	else if (ft_strcmp(tab[0], "SO") == 0)
		stock_texture(game, tab, &game->texture.south, line);
	else if (ft_strcmp(tab[0], "WE") == 0)
		stock_texture(game, tab, &game->texture.west, line);
	else if (ft_strcmp(tab[0], "EA") == 0)
		stock_texture(game, tab, &game->texture.east, line);
	else if (ft_strcmp(tab[0], "F") == 0)
		stock_rgb(game, tab, &game->texture.floor, line);
	else if (ft_strcmp(tab[0], "C") == 0)
		stock_rgb(game, tab, &game->texture.ceilling, line);
	else
	{
		free_tab(tab);
		return (0);
	}
	free_tab(tab);
	return (1);
}

int	is_texture(t_game *game, char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (!tab)
	{
		free(line);
		ft_error("Malloc split failed", game);
	}
	if (strcmp_texture(game, tab, line) == 0)
		return (0);
	return (1);
}

int ft_strisdigit(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}