/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:24:06 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/12 14:24:53 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "wolf3d.h"
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

static int	ft_usage(void)
{
	ft_printf("\033[95musage \033[0m: ./wolf3d [map]\n");
	return (0);
}

static int	ft_open(char *s)
{
	int		ret;

	if ((ret = open(s, O_RDONLY)) < 0)
	{
		ft_printf("\033[91mEXCEPTION \033[0m: open() failed\n");
		exit(1);
	}
	return (ret);
}

static void	ft_checksum(int fd)
{
	int		ret;
	char	buf[10];

	ft_bzero(buf, 10);
	ret = read(fd, buf, 9);
	if (ret != 9)
	{
		ft_printf("\033[91mERROR \033[0m: read() failed of invalid checksum\n");
		exit(1);
	}
	if (ft_strcmp(buf, "validmap\n"))
	{
		ft_printf("\033[91mERROR \033[0m: invalid checksum (%s)\n", buf);
		exit(1);
	}
}

int			main(int argc, char **argv)
{
	int		fd;
	t_game	game;

	if (argc != 2)
		return (ft_usage());
	if (XMAP < 10 || YMAP < 10)
	{
		ft_printf("\033[91mERROR \033[0m: XSIZE AND YSIZE TOO SMALL\n");
		exit(1);
	}
	fd = ft_open(argv[1]);
	ft_checksum(fd);
	parse_map(&game, fd);
	display_init(&game);
	load_textures(&game);
	game.p.fov = acos(-1) / 3;
	init_pal(&game);
	display_hook(&game);
	return (0);
}
