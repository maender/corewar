/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:26:17 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 17:19:02 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(long long int n)
{
	char	*itoa;
	long	nbr;
	int		end;

	if (!(itoa = ft_strnew((size_t)ft_intlen(n))))
		return (NULL);
	nbr = n;
	end = ft_intlen(n);
	itoa[end--] = '\0';
	if (n < 0)
	{
		nbr = -nbr;
		itoa[0] = '-';
	}
	if (n == 0)
		*itoa = '0';
	while (nbr)
	{
		itoa[end] = nbr % 10 + '0';
		nbr /= 10;
		end--;
	}
	return (itoa);
}
