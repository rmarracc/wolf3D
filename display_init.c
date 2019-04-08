/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:55:51 by rmarracc          #+#    #+#             */
/*   Updated: 2019/01/01 19:05:12 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "minilibx/mlx.h"
#include "libft/ft_printf/ft_printf.h"

static void	getset(t_game *game)
{
	game->init = NULL;
	game->win = NULL;
	game->img = NULL;
	game->tex.n = NULL;
	game->tex.s = NULL;
	game->tex.e = NULL;
	game->tex.o = NULL;
	game->tex.sky = NULL;
	game->mini = NULL;
	game->p.angle = 0.01;
	game->zmap = 10.;
}

void		escapefailure(t_game *game, int i)
{
	deltab(&(game->map.grid));
	free(game->tex.n);
	free(game->tex.s);
	free(game->tex.e);
	free(game->tex.o);
	free(game->tex.sky);
	free(game->mini);
	free(game->img);
	if (i != 4)
		mlx_destroy_window(game->init, game->win);
	if (i == 1 || i >= 4)
		ft_printf("\033[91mEXCEPTION \033[0m: broken malloc\n");
	if (i == 2)
	{
		ft_printf("\033[91mEXCEPTION \033[0m: textures missing\n");
		ft_printf("\033[94mNOTE \033[0m: palettes [4~8] release with DOOM\n");
	}
	exit(i);
}

void		display_init(t_game *game)
{
	int		bpp;
	int		size_l;
	int		endian;

	getset(game);
	if (!(game->init = mlx_init()))
		escapefailure(game, 4);
	if (!(game->win = mlx_new_window(game->init, XMAP, YMAP, "wolf3d")))
		escapefailure(game, 4);
	if (!(game->img = mlx_new_image(game->init, XMAP, YMAP)))
		escapefailure(game, 1);
	game->addr = (uint32_t*)mlx_get_data_addr(game->img, &bpp, &size_l
			, &endian);
}
