/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:34:04 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strrev(char *s)
{
	size_t	i;
	int		j;
	char	*begin;
	char	*end;
	char	temp;

	begin = s;
	end = s;
	i = 0;
	j = ft_strlen(s) - 1;
	while (i < ft_strlen(s) / 2)
	{
		temp = end[j];
		end[j] = begin[i];
		begin[i] = temp;
		i++;
		j--;
	}
}
