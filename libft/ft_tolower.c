/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:45:17 by rmarracc          #+#    #+#             */
/*   Updated: 2018/11/29 22:33:16 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_tolower(int c)
{
	if (c != -1 && c < 127 && c > -129)
		c = (char)c;
	return ((c >= 'A' && c <= 'Z') ? (c + 32) : c);
}
