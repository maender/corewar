/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:37 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	padding_left(t_lprintf *list)
{
	int to_pad;

	to_pad = ft_atoi(list->field) - ft_strlen_swap(list);
	while (to_pad > 0)
	{
		list->to_swap = ft_strjoin_free(list->to_swap, " ", 1);
		to_pad--;
	}
}

static void	padding_rigth(t_lprintf *list)
{
	int to_pad;

	to_pad = ft_atoi(list->field) - ft_strlen_swap(list);
	while (to_pad > 0)
	{
		list->to_swap = ft_strjoin_free(" ", list->to_swap, 2);
		to_pad--;
	}
}

static void	padding_zero(t_lprintf *list)
{
	int to_pad;

	to_pad = ft_atoi(list->field) - ft_strlen_swap(list);
	if (!ft_strchr(list->conversion, 'p'))
	{
		while (to_pad > 0)
		{
			list->to_swap = ft_strjoin_free("0", list->to_swap, 2);
			to_pad--;
		}
	}
	else
		padding_rigth(list);
}

void		padd_digit(t_lprintf **list, char *arg, int field, int left)
{
	int	i;
	int	arglength;

	i = 0;
	arglength = (int)ft_strlen_pro(arg);
	if (left)
	{
		(*list)->to_swap = ft_strjoin_free((*list)->to_swap, arg, 0);
		while (i++ < field - arglength)
			(*list)->to_swap = ft_strjoin_free((*list)->to_swap, " ", 1);
	}
	else
	{
		while (i++ < field - arglength)
			(*list)->to_swap = ft_strjoin_free((*list)->to_swap, " ", 1);
		(*list)->to_swap = ft_strjoin_free((*list)->to_swap, arg, 0);
	}
}

void		handle_padding(t_lprintf *list)
{
	if (ft_strchr(list->special, '-'))
		padding_left(list);
	else if (ft_strchr(list->special, '0'))
		padding_zero(list);
	else
		padding_rigth(list);
}
