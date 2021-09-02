/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:12:44 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_match(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	if (*s2 == '*')
	{
		if (*s1 == '\0')
			return (ft_match(s1, s2 + 1));
		else
			return (ft_match(s1, s2 + 1) || ft_match(s1 + 1, s2));
	}
	if (*s1 == '\0' || *s2 == '\0')
		return (0);
	if (*s1 != *s2)
		return (0);
	if (*s1 == *s2)
		return (ft_match(s1 + 1, s2 + 1));
	return (0);
}
