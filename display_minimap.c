/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 15:37:12 by rmarracc          #+#    #+#             */
/*   Updated: 2019/01/06 22:54:09 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"
#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

uint32_t	get_out_color(t_game *game)
{
	uint8_t	pal;

	pal = game->map.pal;
	if (pal == 1)
		return (0x883700);
	if (pal == 2)
		return (0x969530);
	if (pal == 3)
		return (0x601312);
	if (pal == 4)
		return (0x604F12);
	if (pal == 5)
		return (0x605AC0);
	if (pal == 7)
		return (0x440044);
	return (0);
}

uint32_t	get_wall_color(t_game *game)
{
	uint8_t	pal;

	pal = game->map.pal;
	if (pal == 1)
		return (0x443700);
	if (pal == 2)
		return (0x443700);
	if (pal == 3)
		return (0xD58A00);
	if (pal == 4)
		return (0x634200);
	if (pal == 5)
		return (0xE1E0F9);
	if (pal == 6)
		return (0xFFFFFF);
	if (pal == 7)
		return (0x000033);
	return (0);
}

uint32_t	get_field_color(t_game *game)
{
	uint8_t	pal;

	pal = game->map.pal;
	if (pal == 1)
		return (0xE1CFA0);
	if (pal == 2)
		return (0xC3E0BA);
	if (pal == 3)
		return (0xFFE4B9);
	if (pal == 4)
		return (0xE4D1AC);
	if (pal == 5)
		return (0xC6DBFD);
	if (pal == 6)
		return (0x666666);
	if (pal == 7)
		return (0x8822AA);
	return (0);
}

void		calc_mini(t_game *game, int i)
{
	double	x;
	double	y;
	int		xdist;
	int		ydist;

	while (i < (400 * 200))
	{
		x = fmod(i, 400);
		y = i / 400;
		xdist = (int)(game->p.x + (x - 200.) / game->zmap);
		ydist = (int)(game->p.y + (y - 100.) / game->zmap);
		if (y > 95 && y < 106 && x > 195 && x < 206)
			game->maddr[i] = 256 * 255;
		else if (xdist < 0 || xdist >= game->map.xmap || ydist < 0
			|| ydist >= game->map.ymap)
			game->maddr[i] = get_out_color(game);
		else if (game->map.grid[ydist][xdist] == 'w')
			game->maddr[i] = get_wall_color(game);
		else
			game->maddr[i] = get_field_color(game);
		i++;
	}
	if (game->sw == 1)
		mlx_put_image_to_window(game->init, game->win, game->mini
			, XMAP - 400, 0);
}

void		init_pal(t_game *game)
{
	int		bpp;
	int		endian;
	int		size_l;

	if (XMAP < 600 || YMAP < 400)
	{
		ft_printf("\033[93mWARNING \033[0m: window too small for minimap\n");
		return ;
	}
	if (!(game->mini = mlx_new_image(game->init, 400, 200)))
		escapefailure(game, 1);
	game->maddr = (uint32_t*)mlx_get_data_addr(game->mini, &bpp, &size_l
		, &endian);
	ft_bzero(game->maddr, 400 * 200);
	calc_mini(game, 0);
}
