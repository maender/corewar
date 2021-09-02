/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:13:12 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/13 17:45:15 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nmatch(char *s1, char *s2)
{
	if (*s1 && *s2)
	{
		if (*s1 == '\0' && *s2 == '\0')
			return (1);
		if (*s2 == '*')
		{
			if (*s1 == '\0')
				return (ft_nmatch(s1, s2 + 1));
			else
				return (ft_nmatch(s1, s2 + 1) + ft_nmatch(s1 + 1, s2));
		}
		if (*s1 == '\0' || *s2 == '\0')
			return (0);
		if (*s1 != *s2)
			return (0);
		if (*s1 == *s2)
			return (ft_nmatch(s1 + 1, s2 + 1));
	}
	return (0);
}
