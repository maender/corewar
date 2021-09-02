/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:39:57 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*rahc;
	size_t	i;

	i = 0;
	if (!(rahc = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (s)
	{
		while (i < len)
		{
			rahc[i] = s[start];
			i++;
			start++;
		}
		rahc[i] = '\0';
		return (rahc);
	}
	return (NULL);
}
