/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:32:53 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/16 16:01:30 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return ((c == '\t' || c == '\n' || c == '\r' || c == '\v'
			|| c == '\f' || c == ' '));
}

long		ft_atol(const char *str)
{
	int			x;
	long long	entier;
	int			signe;
	int			i;

	x = 0;
	entier = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[x]))
		x++;
	signe = (str[x] == '-') ? -1 : 1;
	(str[x] == '-' || str[x] == '+') ? x++ : 0;
	i = 0;
	while (ft_isdigit((int)str[x]))
	{
		entier = entier * 10 + (str[x++] - '0');
		i++;
	}
	if (i > 19 || entier > 9223372036854775807)
		return (signe > 0 ? -1 : 0);
	return (entier * signe);
}
