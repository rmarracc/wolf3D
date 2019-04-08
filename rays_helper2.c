/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:10:47 by cpoirier          #+#    #+#             */
/*   Updated: 2019/01/01 17:10:57 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>
#include "minilibx/mlx.h"

int				is_in_wall(t_game *game, double x, double y)
{
	if ((int)x < 0 || (int)y < 0 || (int)x >= game->map.xmap
			|| (int)y >= game->map.ymap)
		return (1);
	return (game->map.grid[(int)y][(int)x] == 'w' ? 1 : 0);
}

void			get_offset(t_game *game, t_point *offset, t_point *delta)
{
	if (delta->x < 0)
	{
		offset->x = -(game->p.x - (double)(int)game->p.x
			- (game->p.x < 0 ? 1. : 0)) * delta->x;
	}
	else
	{
		offset->x = ((double)(int)game->p.x + (game->p.x < 0 ? 0 : 1.)
			- game->p.x) * delta->x;
	}
	if (delta->y < 0)
	{
		offset->y = -(game->p.y - (double)(int)game->p.y
			- (game->p.y < 0 ? 1. : 0)) * delta->y;
	}
	else
	{
		offset->y = ((double)(int)game->p.y + (game->p.y < 0 ? 0 : 1.)
				- game->p.y) * delta->y;
	}
	delta->x = delta->x < 0 ? -delta->x : delta->x;
	delta->y = delta->y < 0 ? -delta->y : delta->y;
}

void			initiate_map(t_game *game, t_args *args)
{
	if (args->theta < 0)
		args->theta += 2. * acos(-1);
	if (args->theta > 2. * acos(-1))
		args->theta -= 2. * acos(-1);
	args->map.x = (int)(game->p.x - (game->p.x < 0 ? 1. : 0));
	args->map.y = (int)(game->p.y - (game->p.y < 0 ? 1. : 0));
	args->delta.x = 1. / cos(args->theta);
	args->delta.y = 1. / sin(args->theta);
	args->step.x = args->delta.x < 0 ? -1 : 1;
	args->step.y = args->delta.y < 0 ? -1 : 1;
	get_offset(game, &args->offset, &args->delta);
	args->offset.x = args->offset.x < 0 ? -args->offset.x : args->offset.x;
	args->offset.y = args->offset.y < 0 ? -args->offset.y : args->offset.y;
}

void			fix_fisheye(t_args *args, int i, t_point *infos, int face)
{
	double		a;

	a = (((double)i / (double)XMAP) * 60.) - 30.;
	a = acos(-1) * (a / 180.);
	infos->x = (face ? args->offset.y - args->delta.y : args->offset.x
		- args->delta.x);
	infos->x = infos->x * cos(a) / (args->game->ratio * 1.7);
}

int				dda_logic(t_args *args)
{
	if (args->offset.x < args->offset.y)
	{
		args->map.x += args->step.x;
		args->offset.x += args->delta.x;
		return (0);
	}
	else
	{
		args->map.y += args->step.y;
		args->offset.y += args->delta.y;
		return (1);
	}
}
