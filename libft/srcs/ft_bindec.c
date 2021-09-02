/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bindec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:49:51 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/29 11:35:21 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_power(int nb, int pow)
{
	int ret;

	ret = nb;
	if (pow == 0)
		return (1);
	while (pow > 1)
	{
		ret = ret * nb;
		pow--;
	}
	return (ret);
}

int			ft_bindec(char *bin)
{
	int		ret;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(bin) - 1;
	ret = 0;
	while (bin[i])
	{
		ret = ret + ((bin[i] - 48) * ft_power(2, j));
		j++;
		i--;
	}
	return (ret);
}
