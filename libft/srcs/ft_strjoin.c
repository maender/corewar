/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:37:22 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	if (!(res = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)))))
		return (NULL);
	i = 0;
	if (s1 && s2)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
		i = 0;
		while (s2[i])
		{
			res[i + ft_strlen(s1)] = s2[i];
			i++;
		}
	}
	res[i + ft_strlen(s1)] = '\0';
	return (res);
}
