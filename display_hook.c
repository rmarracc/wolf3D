/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:15:40 by rmarracc          #+#    #+#             */
/*   Updated: 2018/12/21 21:16:22 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "minilibx/mlx.h"
#include "libft/libft.h"

int			destroy_win(t_game *game)
{
	escapefailure(game, 0);
	return (0);
}

int			press_event(int key, t_game *game)
{
	if (key >= 0 && key < 300)
		game->keytab[key] = 1;
	if (key == 53)
		escapefailure(game, 0);
	if (key == 46)
	{
		if (game->sw == 0)
			game->sw = 1;
		else
			game->sw = 0;
	}
	return (0);
}

int			release_event(int key, t_game *game)
{
	if (key >= 0 && key < 300)
		game->keytab[key] = 0;
	return (0);
}

void		display_hook(t_game *game)
{
	game->sw = 0;
	ft_bzero(game->keytab, sizeof(uint8_t) * 300);
	mlx_hook(game->win, 17, 0L, destroy_win, game);
	mlx_hook(game->win, 2, (1L << 0), press_event, game);
	mlx_hook(game->win, 3, (1L << 1), release_event, game);
	mlx_loop_hook(game->init, moveplay, game);
	mlx_loop(game->init);
}
