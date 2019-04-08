/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 22:13:38 by rmarracc          #+#    #+#             */
/*   Updated: 2019/01/04 16:04:29 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

static void	ft_init_param(t_game *game)
{
	game->map.grid = NULL;
	game->ratio = (double)XMAP / (double)YMAP;
}

static void	check_param(char **s)
{
	int			tmp;
	char		*stock;

	tmp = ft_atoi(*s);
	if (tmp < 3 || tmp > 2000)
	{
		ft_printf("\033[91mERROR \033[0m: map size limits : [3~2000]\n");
		ft_strdel(s);
		exit(1);
	}
	if (!(stock = ft_itoa(tmp)))
	{
		ft_printf("\033[91mEXCEPTION \033[0m: broken malloc()\n");
		ft_strdel(s);
		exit(1);
	}
	if (ft_strcmp(stock, *s))
	{
		ft_printf("\033[91mERROR \033[0m: invalid parameter\n");
		ft_strdel(s);
		ft_strdel(&stock);
		exit(1);
	}
	ft_strdel(&stock);
}

static void	check_param2(char **s)
{
	int			tmp;
	char		*stock;

	tmp = ft_atoi(*s);
	if (tmp < 1 || tmp > 8)
	{
		ft_printf("\033[91mERROR \033[0m: palette must be 1~8\n");
		ft_strdel(s);
		exit(1);
	}
	if (!(stock = ft_itoa(tmp)))
	{
		ft_printf("\033[91mEXCEPTION \033[0m: broken malloc()\n");
		ft_strdel(s);
		exit(1);
	}
	if (ft_strcmp(stock, *s))
	{
		ft_printf("\033[91mERROR \033[0m: invalid parameter\n");
		ft_strdel(s);
		ft_strdel(&stock);
		exit(1);
	}
	ft_strdel(&stock);
}

static void	parse_coord(t_game *game, int fd, char *line)
{
	if (sget_next_line(fd, &line) < 1)
	{
		ft_printf("\033[91mEXCEPTION \033[0m: sget_next_line() failed\n");
		exit(1);
	}
	check_param(&line);
	game->map.xmap = (uint16_t)ft_atoi(line);
	ft_strdel(&line);
	if (sget_next_line(fd, &line) < 1)
	{
		ft_printf("\033[91mEXCEPTION \033[0m: sget_next_line() failed\n");
		exit(1);
	}
	check_param(&line);
	game->map.ymap = (uint16_t)ft_atoi(line);
	ft_strdel(&line);
	if (sget_next_line(fd, &line) < 1)
	{
		ft_printf("\033[91mEXCEPTION \033[0m: sget_next_line() failed\n");
		exit(1);
	}
	check_param2(&line);
	game->map.pal = (uint16_t)ft_atoi(line);
	ft_strdel(&line);
}

void		parse_map(t_game *game, int fd)
{
	char		*line;

	line = NULL;
	ft_init_param(game);
	parse_coord(game, fd, line);
	parse_map2(game, fd);
}
