/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:28:35 by rmarracc          #+#    #+#             */
/*   Updated: 2019/01/04 16:04:45 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

static void	set_param(char **av, t_gen *p)
{
	p->x = ft_atoi(av[1]);
	p->y = ft_atoi(av[2]);
	p->pal = ft_atoi(av[3]);
	p->d = ft_atoi(av[4]);
	p->px = ft_atoi(av[5]);
	p->py = ft_atoi(av[6]);
	p->b = ft_atoi(av[7]);
}

static void	error_param(t_gen *p)
{
	static int		ret = 0;

	if (p->x > 2000 || p->y > 2000)
		ret = ft_printf("\033[91mERROR \033[0m: map too big\n");
	else if (p->x < 3 || p->y < 3)
		ret = ft_printf("\033[91mERROR \033[0m: map too small\n");
	else if (p->pal > 8 || p->pal < 1)
		ret = ft_printf("\033[91mERROR \033[0m: pal must be [1~8]\n");
	else if (p->d < 1 || p->d > 256)
		ret = ft_printf("\033[91mERROR \033[0m: density must be [1~256]\n");
	else if (p->px > p->x - 2 || p->px < 1)
		ret = ft_printf("\033[91mERROR \033[0m: player x is outside the map\n");
	else if (p->py > p->y - 2 || p->py < 1)
		ret = ft_printf("\033[91mERROR \033[0m: player y is outside the map\n");
	else if (p->b != 0 && p->b != 1)
		ret = ft_printf("\033[91mERROR \033[0m: borders must be [0~1]\n");
	if (ret != 0)
		exit(1);
}

static void	print_line(int fd, int i, t_gen *p)
{
	int				j;
	unsigned char	ubuf[1];

	j = 0;
	while (j < p->x)
	{
		if (i == 0 || i == p->y - 1 || j == 0 || j == p->x - 1)
			ft_putchar((p->b == 1) ? 'w' : ' ');
		else if (i == p->py && j == p->px)
			ft_putchar('p');
		else
		{
			if (read(fd, ubuf, 1) < 0)
			{
				ft_printf("\033[95mEXCEPTION \033[0m: urandom read failed\n");
				exit(1);
			}
			if (p->d != 256)
				ft_putchar((ubuf[0] % p->d == 0) ? 'w' : ' ');
			else
				ft_putchar(' ');
		}
		j++;
	}
}

static void	open_file(t_gen *p)
{
	static int		i = 0;
	int				fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("\033[95mEXCEPTION \033[0m: urandom not found\n");
		exit(1);
	}
	while (i < p->y)
	{
		print_line(fd, i, p);
		ft_putchar('\n');
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_gen			param;

	if (argc != 8)
	{
		ft_printf("\033[94musage \033[0m: ./generator ");
		ft_printf("[x] [y] [pal] [density] [px] [py] [borders]\n");
		return (0);
	}
	set_param(argv, &param);
	error_param(&param);
	ft_printf("validmap\n%d\n%d\n%d\n", param.x, param.y, param.pal);
	open_file(&param);
	return (0);
}
