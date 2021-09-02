/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 19:48:39 by edjubert          #+#    #+#             */
/*   Updated: 2019/04/18 16:47:48 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if ((s1[0] == '\0' && s2[0] == '\0') || n <= 0)
		return (0);
	while (*s1 && n > 0)
	{
		if (*s1 != *s2)
			return (*s1 < 0 ? 1 : *s1 - *s2);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	if (*s2)
		return (-*s2);
	return (0);
}
