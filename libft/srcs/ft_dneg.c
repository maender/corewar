/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dneg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:59:52 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dneg(double val)
{
	char			*ret;
	unsigned		idx;
	unsigned char	*ptr;

	ptr = (unsigned char*)&val;
	idx = 8 * sizeof(val);
	ret = NULL;
	while (idx)
	{
		ret = ptr[idx / 8] & (1u << (idx % 8))
			? ft_strjoin_free(ret, "1", 1)
			: ft_strjoin_free(ret, "0", 1);
		idx--;
	}
	if (ret[1] == '1')
	{
		ft_strdel(&ret);
		return (1);
	}
	else
	{
		ft_strdel(&ret);
		return (0);
	}
}
