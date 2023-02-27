/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:12:19 by alondot           #+#    #+#             */
/*   Updated: 2023/02/27 15:37:55 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubed.h"

void	free_close(char *str, char **tab)
{
	free(str);
	free_tab(tab);
}

void	ft_error(char *str, t_game *game)
{
	printf("Error\n%s\n", str);
	free_struct(game);
	exit (1);
}

void	check_error_map(t_game *game, int i, int j)
{
	if (i == 0 || !(game->map[i - 1][j])
		|| (game->map[i - 1][j] && game->map[i - 1][j] == ' '))
		ft_error_code(WRONG_LAYOUT, game);
	if (!game->map[i + 1] || !(game->map[i + 1][j])
		|| (game->map[i + 1][j] && game->map[i + 1][j] == ' '))
		ft_error_code(WRONG_LAYOUT, game);
	if (!(game->map[i][j + 1]) || (game->map[i][j + 1]
		&& game->map[i][j + 1] == ' '))
		ft_error_code(WRONG_LAYOUT, game);
	if (i == 0 || !(game->map[i][j - 1]) || (game->map[i][j - 1]
		&& game->map[i][j - 1] == ' '))
		ft_error_code(WRONG_LAYOUT, game);
}

void	ft_error_code(int code, t_game *game)
{
	printf("Error\n%s\n", code_erreur(code));
	free_struct(game);
	exit (1);
}

char	*code_erreur(int code)
{
	if (code == 101)
		return ("There must be 1 player");
	if (code == 102)
		return ("There can only be 1 player");
	if (code == 103)
		return ("Map can only be '1', '0', ' ', 'W', 'E', 'S', 'N'");
	if (code == 104)
		return ("Wrong layout, map must be closed");
	return (NULL);
}
