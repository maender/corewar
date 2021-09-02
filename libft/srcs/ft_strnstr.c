/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:59:20 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(needle) < 1)
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		if (needle[j] == haystack[i])
		{
			while (needle[j] && needle[j] == haystack[i + j])
				j++;
			if (needle[j] == '\0' && i + j <= len)
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
