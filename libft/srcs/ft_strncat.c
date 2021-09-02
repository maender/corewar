/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 19:17:04 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int i;
	int j;

	i = ft_strlen(s1);
	j = 0;
	while (s2[j] && n > 0)
	{
		if (n == 0)
		{
			s1[i] = '\0';
			return (s1);
		}
		s1[i] = s2[j];
		i++;
		j++;
		n--;
	}
	s1[i] = '\0';
	return (s1);
}
