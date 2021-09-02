/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:11:16 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/29 11:37:40 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_init(char *percent, t_lprintf **list, void *arg)
{
	t_lprintf *tmp;

	if (*list)
	{
		tmp = *list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ft_create_argument_list();
		tmp = tmp->next;
	}
	else
		tmp = ft_create_argument_list();
	tmp->percent = percent;
	tmp->arg = arg;
	if (!*list)
		*list = tmp;
	return (0);
}

int			ft_init_float(char *percent, t_lprintf **list, double arg)
{
	t_lprintf *tmp;

	if (*list)
	{
		tmp = *list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ft_create_argument_list();
		tmp = tmp->next;
	}
	else
		tmp = ft_create_argument_list();
	tmp->percent = percent;
	tmp->f = arg;
	if (!*list)
		*list = tmp;
	return (0);
}

int			ft_init_float_long(char *per, t_lprintf **list, long double arg)
{
	t_lprintf *tmp;

	if (*list)
	{
		tmp = *list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ft_create_argument_list();
		tmp = tmp->next;
	}
	else
		tmp = ft_create_argument_list();
	tmp->percent = per;
	tmp->lf = arg;
	if (!*list)
		*list = tmp;
	return (0);
}
