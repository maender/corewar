/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:32:53 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 15:06:51 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_isspace(char c)
{
	return ((c == '\t' || c == '\n' || c == '\r' || c == '\v'
			|| c == '\f' || c == ' '));
}

unsigned long		ft_atoul(const char *str)
{
	int				x;
	unsigned long	entier;
	int				i;

	x = 0;
	entier = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[x]))
		x++;
	if (str[x] == '-')
		return (0);
	(str[x] == '+') ? x++ : 0;
	i = 0;
	while (ft_isdigit((int)str[x]))
	{
		entier = entier * 10 + (str[x++] - '0');
		i++;
	}
	return (entier);
}
