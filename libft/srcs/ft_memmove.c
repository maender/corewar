/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:59:16 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_tmp;
	char	*src_tmp;
	size_t	x;

	dst_tmp = (char*)dst;
	src_tmp = (char*)src;
	x = -1;
	if (src_tmp < dst_tmp)
		while ((int)--len >= 0)
			dst_tmp[len] = src_tmp[len];
	else
		while (++x < len)
			dst_tmp[x] = src_tmp[x];
	return (dst);
}
