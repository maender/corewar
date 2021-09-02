/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:19:36 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_long(long int n)
{
	int			i;
	long long	nb;
	int			neg;
	char		*res;

	if (!(res = (char*)malloc(sizeof(char) * (ft_intlen((long int)n) + 1))))
		return (NULL);
	neg = n < 0;
	i = 0;
	ft_bzero(res, (ft_intlen(n) + 1));
	nb = neg ? (long)n * -1 : (long)n;
	if (nb == 0)
		res[i] = '0';
	while (nb)
	{
		res[i] = nb % 10 + 48;
		nb = nb / 10;
		i++;
	}
	if (neg)
		res[i] = '-';
	ft_strrev(res);
	res[ft_intlen(n) + 1] = '\0';
	return (res);
}
