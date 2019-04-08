/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:50:39 by rmarracc          #+#    #+#             */
/*   Updated: 2019/01/01 14:06:20 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		validline(char *line, t_game *game, int id)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'p' && game->p.x == -1.)
		{
			game->p.x = (double)i + 0.5;
			game->p.y = (double)id + 0.5;
		}
		else if (line[i] != 32 && line[i] != 'w')
			return (0);
		i++;
	}
	return (1);
}
