/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:57:50 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 17:19:33 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	join_free_loop(char **ret, int length, t_lprintf **list)
{
	int	i;

	i = 0;
	if (*ret && *ret[0] != '-')
		length--;
	if (((ft_atoi((*list)->field) > 0 || ft_strchr((*list)->special, '+')
				|| ((*list)->precision && *ret && *ret[0] == '-'))
			&& !ft_strchr((*list)->special, '0')))
		length++;
	else if ((*list)->precision && *ret
		&& *ret[0] == '-' && ft_strchr((*list)->special, '0'))
		length++;
	while (i++ < length)
		*ret = ft_strjoin_free(*ret, "0", 1);
}

static int	field_and_precision(t_lprintf **list, int pre, int field)
{
	if (ft_strchr((*list)->special, '0') && pre == 0
		&& !ft_strchr((*list)->special, '-'))
		return (1);
	else if (ft_strchr((*list)->special, '0')
		&& pre > 0 && (int)(long)(*list)->arg >= 0)
		return (2);
	else if ((pre > 0 && field == 0) || (pre > 0 && field > 0
			&& (ft_strchr((*list)->special, '+')
				|| ft_strchr((*list)->special, '0'))))
		return (3);
	else if (pre > 0 && field > 0 && (int)(long)(*list)->arg < 0)
		return (3);
	else if (pre > 0 && field > 0 && !ft_strchr((*list)->special, ' '))
		return (4);
	else
		return (0);
}

static char	*compose_arg(t_lprintf **list, int arg, int pre, int field)
{
	char	*ret;
	int		arglength;

	ret = NULL;
	arglength = (int)ft_strlen_free(ft_itoa(arg));
	if (arg < 0)
		ret = ft_strjoin_free(ret, "-", 1);
	if (ft_strchr((*list)->special, '+') && arg >= 0)
		ret = ft_strjoin_free(ret, "+", 1);
	else if (ft_strchr((*list)->special, ' ') && arg >= 0
		&& !ft_strchr((*list)->special, '+'))
		ret = ft_strjoin_free(ret, " ", 1);
	if (field_and_precision(list, pre, field) == 1)
		join_free_loop(&ret, field - arglength, list);
	else if (field_and_precision(list, pre, field) == 2)
		join_free_loop(&ret, field - arglength - 1, list);
	else if (field_and_precision(list, pre, field) == 3)
		join_free_loop(&ret, pre - arglength, list);
	else if (field_and_precision(list, pre, field) == 4)
		join_free_loop(&ret, pre - arglength - 1, list);
	else
		join_free_loop(&ret, pre - arglength, list);
	ret = ft_strjoin_free(ret, ft_itoa(arg < 0 ? arg * -1 : arg), 0);
	return (ret);
}

void		handle_digit(t_lprintf *list)
{
	int		precision;
	int		field;
	char	*arg;

	precision = list->dpp != NULL ? ft_atoi(list->dpp) : 0;
	field = list->field != NULL ? ft_atoi(list->field) : 0;
	if (list->modifier)
	{
		if (ft_match(list->modifier, "hh"))
			arg = compose_arg(&list, (char)(long)list->arg, precision, field);
		else if (ft_match(list->modifier, "h"))
			arg = compose_arg(&list, (short)(long)list->arg, precision, field);
		else if (ft_match(list->modifier, "z"))
			return (handle_unsigned(list));
		else
			arg = compose_arg(&list, (int)(long)list->arg, precision, field);
	}
	else
		arg = compose_arg(&list, (int)(long)list->arg, precision, field);
	if (list->precision && ft_match(list->precision, ".")
		&& (int)(long)list->arg == 0 && !(precision > 0))
		arg = ft_strsub_free(arg, ft_strlen_pro(arg), ft_strlen_pro(arg));
	padd_digit(&list, arg, field,
		(list->special != NULL && ft_strchr(list->special, '-') != NULL));
}
