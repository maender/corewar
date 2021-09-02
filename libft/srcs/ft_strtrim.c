/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:48:58 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return ((c == '\t' || c == '\n' || c == ' '));
}

char		*ft_strtrim(char const *s)
{
	char	*tmp;
	size_t	x;
	size_t	len_tmp;

	x = 0;
	if (!s)
		return (NULL);
	len_tmp = ft_strlen(s);
	while (ft_isspace((int)s[x]))
		x++;
	while (ft_isspace((int)s[len_tmp - 1]))
		len_tmp--;
	if (x == ft_strlen(s))
	{
		tmp = ft_strsub(s, 0, 0);
		return (tmp);
	}
	if (!(tmp = ft_strsub(s, x, (len_tmp - x))))
		return (NULL);
	return (tmp);
}
