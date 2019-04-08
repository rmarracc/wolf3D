/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:14:36 by rmarracc          #+#    #+#             */
/*   Updated: 2019/01/05 17:22:42 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "minilibx/mlx.h"

static char	*get_texid(int i, char *path)
{
	path[11] = i + '0';
	return (path);
}

static void	get_addr(t_game *game)
{
	int				bpp;
	int				size_l;
	int				endian;

	game->tex.naddr = (uint32_t*)mlx_get_data_addr(game->tex.n, &bpp, &size_l
		, &endian);
	game->tex.saddr = (uint32_t*)mlx_get_data_addr(game->tex.s, &bpp, &size_l
		, &endian);
	game->tex.eaddr = (uint32_t*)mlx_get_data_addr(game->tex.e, &bpp, &size_l
		, &endian);
	game->tex.oaddr = (uint32_t*)mlx_get_data_addr(game->tex.o, &bpp, &size_l
		, &endian);
	game->tex.skya = (uint32_t*)mlx_get_data_addr(game->tex.sky, &bpp, &size_l
		, &endian);
}

void		load_textures(t_game *game)
{
	static char		path[] = "textures/ / .xpm";
	int				w;
	int				h;

	w = 64;
	h = 64;
	path[9] = game->map.pal + '0';
	if (!(game->tex.n = mlx_xpm_file_to_image(game->init
		, get_texid(1, path), &w, &h)))
		escapefailure(game, 2);
	if (!(game->tex.s = mlx_xpm_file_to_image(game->init
		, get_texid(2, path), &w, &h)))
		escapefailure(game, 2);
	if (!(game->tex.e = mlx_xpm_file_to_image(game->init
		, get_texid(3, path), &w, &h)))
		escapefailure(game, 2);
	if (!(game->tex.o = mlx_xpm_file_to_image(game->init
		, get_texid(4, path), &w, &h)))
		escapefailure(game, 2);
	w = 1600;
	h = 1200;
	if (!(game->tex.sky = mlx_xpm_file_to_image(game->init
		, get_texid(5, path), &w, &h)))
		escapefailure(game, 2);
	get_addr(game);
}
