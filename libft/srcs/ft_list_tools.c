/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:28:28 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/16 16:11:43 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lprintf	*ft_create_argument_list(void)
{
	t_lprintf	*new;

	if (!(new = (t_lprintf*)malloc(sizeof(t_lprintf))))
		return (NULL);
	new->special = NULL;
	new->field = NULL;
	new->precision = NULL;
	new->dpp = NULL;
	new->modifier = NULL;
	new->conversion = NULL;
	new->percent = NULL;
	new->arg = NULL;
	new->to_swap = NULL;
	new->next = NULL;
	new->fd = 1;
	new->error = 0;
	new->f = 0;
	new->lf = 0;
	return (new);
}

void		ft_list_del(t_lprintf **list)
{
	(*list)->special ? ft_strdel(&(*list)->special) : NULL;
	(*list)->field ? ft_strdel(&(*list)->field) : NULL;
	(*list)->precision ? ft_strdel(&(*list)->precision) : NULL;
	(*list)->dpp ? ft_strdel(&(*list)->dpp) : NULL;
	(*list)->modifier ? ft_strdel(&(*list)->modifier) : NULL;
	(*list)->conversion ? ft_strdel(&(*list)->conversion) : NULL;
	(*list)->percent ? ft_strdel(&(*list)->percent) : NULL;
	(*list)->to_swap ? ft_strdel(&(*list)->to_swap) : NULL;
	(*list)->fd = 0;
	(*list)->error = 0;
	(*list)->f = 0;
	(*list)->lf = 0;
}

void		ft_lst_del(t_lprintf **list)
{
	t_lprintf	*tmp;

	while ((*list))
	{
		ft_list_del((t_lprintf**)&*list);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}
