/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:07:02 by cpoirier          #+#    #+#             */
/*   Updated: 2019/01/02 16:36:57 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>
#include "minilibx/mlx.h"

int				get_texture(t_game *game, int face, t_point *t_pos)
{
	t_point_i	p;
	int			col;

	p.x = (int)(t_pos->x * 64.0);
	p.y = (int)(t_pos->y * 64.0);
	p.x = (p.x < 0) ? 0 : p.x;
	p.y = (p.y < 0) ? 0 : p.y;
	p.x = (p.x > 63) ? 63 : p.x;
	p.y = (p.y > 63) ? 63 : p.y;
	if (face == 0)
		col = *(int *)(game->tex.naddr + p.x + p.y * 64);
	else if (face == 1)
		col = *(int *)(game->tex.saddr + p.x + p.y * 64);
	else if (face == 2)
		col = *(int *)(game->tex.eaddr + p.x + p.y * 64);
	else
		col = *(int *)(game->tex.oaddr + p.x + p.y * 64);
	return (col);
}

void			draw_sky(t_game *game, t_point_i *p, double theta)
{
	int i;
	int j;

	i = ((int)((theta / acos(-1) * 2.) * 1600.)) % 1600;
	j = (int)(1200. / (double)YMAP * (double)p->y);
	(void)game;
	if ((i + j * 1600) >= 0 && (i + j * 1600) < (1600 * 1200))
		*(int*)(game->addr + p->x + p->y * XMAP) =
			*(int *)(game->tex.skya + i + j * 1600);
}

void			draw_wall(t_game *game, t_point_i *p, int face, t_point *t_pos)
{
	if ((p->x + p->y * XMAP) >= 0 && p->x < XMAP && p->y < YMAP)
		*(int*)(game->addr + p->x + p->y * XMAP) = get_texture(game
				, face, t_pos);
}

void			draw_floor(t_game *game, t_point_i *coord, double dst, int sky)
{
	int wsize;

	wsize = (YMAP / 2 - sky) * 2;
	dst = 0;
	if (coord->y - (YMAP - sky) < wsize)
		*(int*)(game->addr + coord->x + coord->y * XMAP) = enlighten(
			*(int*)(game->addr + coord->x + (2 * (YMAP - sky) - coord->y)
				* XMAP), 0.5, game->map.pal);
	else
		*(int*)(game->addr + coord->x + coord->y * XMAP) = enlighten(
			*(int*)(game->addr + coord->x + (YMAP - coord->y) * XMAP),
				0.5, game->map.pal);
}

void			draw_column(t_game *game, t_point_i *face,
		t_point *infos, double theta)
{
	int			i;
	int			sky;
	t_point_i	p;
	t_point		t_pos;

	i = -1;
	sky = YMAP / 2 - (int)((double)YMAP / 2.0 * 1. / (infos->x * 2.));
	p.x = face->y;
	t_pos.x = infos->y;
	while (++i < sky)
	{
		p.y = i;
		draw_sky(game, &p, theta);
	}
	while (i < YMAP - sky + 1 && i < YMAP)
	{
		p.y = i++;
		t_pos.y = (double)(p.y - sky) / (double)(YMAP - 2 * sky);
		draw_wall(game, &p, face->x, &t_pos);
	}
	while (i < YMAP)
	{
		p.y = i++;
		draw_floor(game, &p, (double)(p.y - YMAP + sky) / 1000.0, sky);
	}
}
