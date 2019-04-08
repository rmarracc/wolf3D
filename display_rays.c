/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:37:11 by cpoirier          #+#    #+#             */
/*   Updated: 2019/01/06 22:51:11 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>
#include "minilibx/mlx.h"

double			find_wall_end(t_game *game, t_args *args, t_point *infos,
		int face)
{
	if (!face)
	{
		args->offset.y = sin(args->theta) * (args->offset.x - args->delta.x)
			+ game->p.y;
		infos->y = args->offset.y - (double)(int)args->offset.y;
		return ((args->theta < acos(-1) / 2. || args->theta > 3.
			* acos(-1) / 2.) ? 0 : 2);
	}
	else
	{
		args->offset.x = cos(args->theta) * (args->offset.y - args->delta.y)
			+ game->p.x;
		infos->y = args->offset.x - (double)(int)args->offset.x;
		return ((args->theta < acos(-1)) ? 1 : 3);
	}
}

int				is_wexp(t_game *game, t_args args)
{
	int			ret;

	ret = (args.map.x == (int)game->p.x && args.map.y == (int)game->p.y);
	if (ret == 0)
	{
		if (game->p.x == (int)game->p.x && (int)game->p.x >= 1)
			if (game->map.grid[(int)(game->p.y)][(int)(game->p.x) - 1] == 'w')
				return (1);
		if (game->p.y == (int)game->p.y && (int)game->p.y >= 1)
			if (game->map.grid[(int)(game->p.y) - 1][(int)(game->p.x)] == 'w')
				return (1);
	}
	return (ret);
}

void			find_wall(t_game *game, double theta, t_point *infos,
		t_point_i *in)
{
	t_args		args;
	int			face;

	args.game = game;
	args.theta = theta;
	initiate_map(game, &args);
	while (game->map.grid[args.map.y][args.map.x] != 'w' || is_wexp(game, args))
	{
		face = dda_logic(&args);
		if (args.map.x < 0 || args.map.x >= game->map.xmap || args.map.y < 0
				|| args.map.y >= game->map.ymap)
		{
			face = 0;
			args.offset.x = 10000000000000.0;
			break ;
		}
	}
	fix_fisheye(&args, in->y, infos, face);
	in->x = find_wall_end(game, &args, infos, face);
	infos->y = (infos->y < 0) ? -infos->y : infos->y;
}

void			display_rays(t_game *game)
{
	t_point_i	index;
	double		theta;
	t_point		infos;
	t_point_i	f;

	index.x = -1;
	while (++index.x < XMAP)
	{
		index.y = 0;
		theta = game->p.angle + game->p.fov * (-0.5 + (double)index.x
			/ (double)XMAP);
		f.y = index.x;
		find_wall(game, theta, &infos, &f);
		draw_column(game, &f, &infos, theta);
	}
	mlx_put_image_to_window(game->init, game->win, game->img, 0, 0);
}

int				enlighten(int color, double ratio, int palette)
{
	int r;
	int g;
	int b;

	b = color % 256;
	g = color % 65536 / 256;
	r = color / 65536;
	if (palette == 7)
	{
		r *= 0.3;
		g *= 0.1;
		b *= 0.4;
	}
	if (palette != 3 && palette != 4 && palette != 7)
		r *= ratio + (ratio * 0.8 * (palette == 5));
	if (palette != 5 && palette != 7)
		b *= ratio;
	if (palette != 2 && palette != 4 && palette != 7)
		g *= ratio + (ratio * 0.8 * (palette == 5));
	return ((r * 65536 + g * 256 + b));
}
