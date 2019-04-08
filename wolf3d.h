/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:38:05 by rmarracc          #+#    #+#             */
/*   Updated: 2019/01/06 17:19:06 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdint.h>

# define XMAP 1600
# define YMAP 1200

typedef struct		s_point_i
{
	int				x;
	int				y;
}					t_point_i;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_map
{
	uint16_t		xmap;
	uint16_t		ymap;
	uint8_t			pal;
	char			**grid;
}					t_map;

typedef struct		s_player
{
	double			x;
	double			y;
	double			angle;
	double			fov;
}					t_player;

typedef struct		s_tex
{
	void			*n;
	void			*s;
	void			*e;
	void			*o;
	void			*sky;
	uint32_t		*naddr;
	uint32_t		*saddr;
	uint32_t		*eaddr;
	uint32_t		*oaddr;
	uint32_t		*skya;
}					t_tex;

typedef struct		s_game
{
	t_player		p;
	t_map			map;
	t_tex			tex;
	uint8_t			keytab[300];
	void			*init;
	void			*win;
	void			*img;
	void			*mini;
	double			zmap;
	uint32_t		*maddr;
	uint32_t		*addr;
	double			ratio;
	uint8_t			sw;
}					t_game;

typedef	struct		s_args
{
	t_game			*game;
	t_point			offset;
	t_point			delta;
	t_point_i		map;
	t_point_i		step;
	int				face;
	double			theta;
}					t_args;

/*
**	PARSING
*/

void				parse_map(t_game *game, int fd);
void				parse_map2(t_game *game, int fd);
int					validline(char *line, t_game *game, int id);
void				load_textures(t_game *game);

/*
**	MINIMAP
*/

void				init_pal(t_game *game);
void				calc_mini(t_game *game, int i);

/*
**	DISPLAY
*/

void				display_init(t_game *game);
void				display_hook(t_game *game);
void				display_rays(t_game *game);
int					moveplay(t_game *game);
int					get_texture(t_game *game, int face, t_point *t_pos);
void				draw_sky(t_game *game, t_point_i *p, double theta);
void				draw_wall(t_game *game, t_point_i *p, int face,
		t_point *t_pos);
void				draw_floor(t_game *game, t_point_i *coord, double dst,
		int we);
void				draw_column(t_game *game, t_point_i *face,
					t_point *infos, double theta);
int					is_in_wall(t_game *game, double x, double y);
void				get_offset(t_game *game, t_point *offset, t_point *delta);
void				initiate_map(t_game *game, t_args *args);
void				fix_fisheye(t_args *args, int i, t_point *infos, int face);
int					dda_logic(t_args *args);
int					enlighten(int color, double ratio, int palette);

/*
**	ERROR MANAGEMENT
*/

void				deltab(char ***t);
void				escapefailure(t_game *game, int i);

#endif
