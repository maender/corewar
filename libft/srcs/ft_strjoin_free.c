/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:20:14 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_free_mode(char *s1, char *s2, int mode)
{
	if (mode == 0)
	{
		if (s1)
			ft_strdel(&s1);
		if (s2)
			ft_strdel(&s2);
	}
	if (mode == 1)
		if (s1)
			ft_strdel(&s1);
	if (mode == 2)
		if (s2)
			ft_strdel(&s2);
}

char			*ft_strjoin_free(char *s1, char *s2, int mode)
{
	int		i;
	int		j;
	int		length;
	char	*res;

	i = 0;
	j = 0;
	length = ft_strlen_pro(s1) + ft_strlen_pro(s2);
	if (!(res = (char*)malloc(sizeof(char) * length + 1)))
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	ft_free_mode(s1, s2, mode);
	return (res);
}
