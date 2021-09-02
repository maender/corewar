/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_needles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fldoucet <fldoucet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:19:21 by fldoucet          #+#    #+#             */
/*   Updated: 2019/04/29 15:21:08 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_count_needles(char *haystack, char *needle)
{
	int	i;
	int	j;
	int	nbr;

	nbr = 0;
	i = 0;
	if (!haystack || !needle)
		return (0);
	while (haystack[i])
	{
		if (needle[0] == haystack[i])
		{
			j = 1;
			while (needle[j] && needle[j] == haystack[i + j])
				j++;
			if (needle[j] == '\0')
				nbr++;
		}
		i++;
	}
	return (nbr);
}
