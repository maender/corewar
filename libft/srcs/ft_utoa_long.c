/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:33:23 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa_long(unsigned long long n)
{
	int					i;
	unsigned long long	nb;
	char				*res;

	if (!(res = (char*)malloc(sizeof(char) * (ft_intlen_unsigned(n) + 1))))
		return (NULL);
	i = 0;
	ft_bzero(res, (ft_intlen_unsigned(n) + 1));
	nb = n;
	if (nb == 0)
		res[i] = '0';
	while (nb != 0)
	{
		res[i] = (char)(nb % 10 + 48);
		nb = nb / 10;
		i++;
	}
	ft_strrev(res);
	res[ft_intlen_unsigned(n) + 1] = '\0';
	return (res);
}
