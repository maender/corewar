/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_field_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 12:57:12 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/16 16:03:32 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_field(int field, t_lprintf **list)
{
	int	arg;
	int	i;

	field = field < 0 ? 0 : field;
	arg = (int)(long)(*list)->arg;
	if (ft_matcha((*list)->special, "+") && arg > 0
		&& !ft_matcha((*list)->conversion, "ouxX"))
		i = 1;
	else if (ft_matcha((*list)->special, " ") && field == 0 && arg > 0
		&& !ft_matcha((*list)->conversion, "o"))
		i = -1;
	else
		i = 0;
	while (i++ < field)
		(*list)->to_swap = ft_strjoin_free((*list)->to_swap, " ", 1);
}
