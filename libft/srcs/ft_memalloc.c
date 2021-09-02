/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:16:44 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t			i;
	void			*my_alloc;
	unsigned char	*temp;

	if (!(my_alloc = (void*)malloc(sizeof(void) * size)))
		return (NULL);
	i = 0;
	temp = (unsigned char*)my_alloc;
	while (i < size)
	{
		temp[i] = 0;
		i++;
	}
	return (my_alloc);
}
