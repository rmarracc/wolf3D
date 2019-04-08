/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:19:53 by rmarracc          #+#    #+#             */
/*   Updated: 2018/12/21 21:17:17 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

static void	errormap2(uint8_t i)
{
	if (i == 1)
		ft_printf("\033[91mEXCEPTION \033[0m: broken malloc\n");
	else if (i == 2)
		ft_printf("\033[91mEXCEPTION \033[0m: sget_next_line() failed\n");
	else if (i == 3)
		ft_printf("\033[91mERROR \033[0m: invalid map pattern\n");
	else if (i == 4)
		ft_printf("\033[91mERROR \033[0m: no player\n");
	exit(1);
}

void		deltab(char ***t)
{
	int			i;

	i = 0;
	if (!(*t))
		return ;
	while ((*t)[i])
	{
		ft_strdel(&(*t)[i]);
		i++;
	}
	free(*t);
	*t = NULL;
}

static void	allocate(t_game *game)
{
	static int	i = 0;

	if (!(game->map.grid = (char**)ft_memalloc((game->map.ymap + 1)
					* sizeof(char*))))
		errormap2(1);
	game->map.grid[0] = NULL;
	while (i < game->map.ymap)
	{
		if (!(game->map.grid[i] = (char*)ft_memalloc(game->map.xmap + 1)))
		{
			deltab(&(game->map.grid));
			errormap2(1);
		}
		game->map.grid[i + 1] = NULL;
		i++;
	}
}

static void	mapget(t_game *game, int fd, char *line)
{
	static int	i = 0;

	while (i < game->map.ymap)
	{
		if (sget_next_line(fd, &line) < 1)
		{
			deltab(&(game->map.grid));
			errormap2(2);
		}
		if (ft_strlen(line) != game->map.xmap)
		{
			deltab(&(game->map.grid));
			ft_strdel(&line);
			errormap2(3);
		}
		if (!(validline(line, game, i)))
		{
			deltab(&(game->map.grid));
			ft_strdel(&line);
			errormap2(3);
		}
		ft_strcpy(game->map.grid[i], line);
		ft_strdel(&line);
		i++;
	}
}

void		parse_map2(t_game *game, int fd)
{
	char		*line;

	line = NULL;
	game->p.x = -1.;
	game->p.y = -1.;
	allocate(game);
	mapget(game, fd, line);
	if (game->p.x < 0 || game->p.y < 0)
	{
		deltab(&(game->map.grid));
		errormap2(4);
	}
}
