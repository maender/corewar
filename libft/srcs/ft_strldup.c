/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:39:50 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(const char *s1, size_t n)
{
	int		i;
	char	*res;

	if (!(res = (char*)malloc(sizeof(char) * (n + 1))))
		return (0);
	i = 0;
	while (i < (int)n)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
