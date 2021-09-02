/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:08 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/16 16:03:05 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	no_modifier(t_lprintf *tmp)
{
	if (ft_matcha(tmp->conversion, "di"))
		handle_digit(tmp);
	else if (ft_matcha(tmp->conversion, "oxX"))
		handle_base(tmp);
	else if (ft_matcha(tmp->conversion, "u"))
		handle_unsigned(tmp);
	else if (ft_match(tmp->conversion, "b"))
		handle_binary(tmp);
	else if (ft_match(tmp->conversion, "f"))
		handle_float(tmp);
	else if (ft_matcha(tmp->conversion, "CcsSp%"))
		handle_string(tmp);
	else if (ft_match(tmp->conversion, "*42*"))
		tmp->to_swap = ft_strdup("");
	else if (ft_matcha(tmp->conversion, "T"))
		handle_title(tmp);
}

static void	modifier(t_lprintf *tmp)
{
	if (ft_matcha(tmp->conversion, "di")
		&& (ft_match(tmp->modifier, "*l*") || ft_match(tmp->modifier, "*ll*")
			|| ft_match(tmp->modifier, "t") || ft_match(tmp->modifier, "j")))
		handle_long(tmp);
	else if (ft_match(tmp->conversion, "f") && ft_match(tmp->modifier, "L"))
		handle_float_long(tmp);
	else if (ft_matcha(tmp->conversion, "u")
		&& (ft_match(tmp->modifier, "l") || ft_match(tmp->modifier, "ll")))
		handle_unsigned_long(tmp);
	else
		no_modifier(tmp);
}

int			ft_choose(char *str, t_lprintf **list)
{
	t_lprintf *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->modifier == NULL)
			no_modifier(tmp);
		else
			modifier(tmp);
		tmp = tmp->next;
	}
	return (ft_color(str, list, 0));
}
