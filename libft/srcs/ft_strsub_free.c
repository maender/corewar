/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:39:17 by edjubert          #+#    #+#             */
/*   Updated: 2019/04/16 11:52:54 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub_free(char *s, unsigned int start, size_t len)
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
		ft_strdel(&s);
		return (rahc);
	}
	return (NULL);
}
