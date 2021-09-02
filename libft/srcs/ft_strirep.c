/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strirep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 11:14:37 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/11 15:06:24 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strirep(unsigned char *dst, unsigned char *src, size_t index,
			size_t plen)
{
	size_t			i;

	i = 0;
	while (i < plen && index < 4096)
	{
		dst[index] = src[i];
		index++;
		i++;
	}
}
