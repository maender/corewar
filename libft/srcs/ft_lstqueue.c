/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstqueue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:39:21 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstqueue(t_list **alst, t_list *new)
{
	t_list	*temp;

	temp = *alst;
	if (temp->content == NULL)
		*alst = ft_lstnew(new->content, new->content_size);
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = ft_lstnew(new->content, new->content_size);
	}
}
