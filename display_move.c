/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:18:18 by rmarracc          #+#    #+#             */
/*   Updated: 2019/01/05 20:04:36 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>
#include "libft/ft_printf/ft_printf.h"

static void	rotplay(t_game *game)
{
	if (game->keytab[124])
		game->p.angle += 0.08;
	if (game->keytab[123])
		game->p.angle -= 0.08;
	if (game->p.angle >= (2 * acos(-1)))
		game->p.angle = fmod(game->p.angle, (2 * acos(-1)));
	else if (game->p.angle < 0)
		game->p.angle += (2 * acos(-1));
}

static void	forward(t_game *game, double x, double y)
{
	double	xmin;
	double	ymin;

	xmin = 1.05 * x;
	ymin = 1.05 * y;
	if (game->p.x + xmin < (double)game->map.xmap && game->p.x + xmin >= 0.)
		if (game->map.grid[(int)(game->p.y)][(int)(game->p.x + xmin)] != 'w')
			game->p.x += x;
	if (game->p.y + ymin < (double)game->map.ymap && game->p.y + ymin >= 0.)
		if (game->map.grid[(int)(game->p.y + ymin)][(int)(game->p.x)] != 'w')
			game->p.y += y;
}

static void	backward(t_game *game, double x, double y)
{
	double	xmin;
	double	ymin;

	xmin = 1.05 * x;
	ymin = 1.05 * y;
	if (game->p.x - xmin >= 0. && game->p.x - xmin < (double)game->map.xmap)
		if (game->map.grid[(int)(game->p.y)][(int)(game->p.x - xmin)] != 'w')
			game->p.x -= x;
	if (game->p.y - ymin >= 0. && game->p.y - ymin < (double)game->map.ymap)
		if (game->map.grid[(int)(game->p.y - ymin)][(int)(game->p.x)] != 'w')
			game->p.y -= y;
}

static void	strafe(t_game *game, double x, double y)
{
	double	angle;
	double	tmp;

	angle = acos(-1) / 2.;
	tmp = x;
	if (game->keytab[2])
	{
		x = cos(angle) * x - sin(angle) * y;
		y = sin(angle) * tmp + cos(angle) * y;
		forward(game, x, y);
	}
	if (game->keytab[0])
	{
		angle = -angle;
		x = cos(angle) * x - sin(angle) * y;
		y = sin(angle) * tmp + cos(angle) * y;
		forward(game, x, y);
	}
}

int			moveplay(t_game *game)
{
	double		x;
	double		y;
	double		speed;

	speed = 0.06;
	if (game->keytab[257])
		speed += 0.04;
	x = speed * cos(game->p.angle);
	y = speed * sin(game->p.angle);
	if (game->keytab[126] || game->keytab[13])
		forward(game, x, y);
	if (game->keytab[125] || game->keytab[1])
		backward(game, x, y);
	if (game->keytab[12] && game->zmap < 30.)
		game->zmap *= 1.1;
	if (game->keytab[14] && game->zmap > 0.2)
		game->zmap /= 1.1;
	rotplay(game);
	strafe(game, x, y);
	display_rays(game);
	if (game->mini)
		calc_mini(game, 0);
	return (0);
}
