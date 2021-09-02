/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:52:30 by edjubert          #+#    #+#             */
/*   Updated: 2019/04/29 14:34:50 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == (char)c)
				return ((char*)&s[i]);
			s++;
		}
		return (s[i] == (char)c ? (char*)&s[i] : NULL);
	}
	return (NULL);
}
