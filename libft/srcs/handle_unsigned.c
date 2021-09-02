/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:56:33 by edjubert          #+#    #+#             */
/*   Updated: 2019/06/20 13:28:51 by doudzzz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*compose_arg(t_lprintf **list, unsigned long long arg,
						int precision, int field)
{
	int		i;
	char	*ret;
	char	*arglength;

	i = 0;
	ret = NULL;
	arglength = ft_utoa_long(arg);
	if (ft_strchr((*list)->special, '0') != NULL && precision == 0
		&& ft_strchr((*list)->special, '-') == NULL)
		while (i++ < field - (int)ft_strlen(arglength))
			ret = ft_strjoin_free(ret, "0", 1);
	else if (precision > 0)
		while (i++ < precision - (int)ft_strlen(arglength))
			ret = ft_strjoin_free(ret, "0", 1);
	ret = ft_strjoin_free(ret, ft_utoa_long(arg), 0);
	ft_strdel(&arglength);
	return (ret);
}

void		unsigned_extends(t_lprintf *list, int precision,
	int field, char **arg)
{
	if (ft_match(list->modifier, "l"))
		*arg = compose_arg(&list,
				(unsigned long)list->arg, precision, field);
	else if (ft_match(list->modifier, "ll"))
		*arg = compose_arg(&list,
				(unsigned long long)list->arg, precision, field);
	else if (ft_match(list->modifier, "z"))
		*arg = compose_arg(&list, (ssize_t)list->arg, precision, field);
	else if (ft_match(list->modifier, "j"))
		*arg = compose_arg(&list, (long long)list->arg, precision, field);
	else
		*arg = compose_arg(&list,
				(unsigned int)(long)list->arg, precision, field);
}

void		handle_unsigned(t_lprintf *list)
{
	int		precision;
	int		field;
	char	*arg;

	precision = list->dpp != NULL ? ft_atoi(list->dpp) : 0;
	field = list->field != NULL ? ft_atoi(list->field) : 0;
	if (list->modifier)
		unsigned_extends(list, precision, field, &arg);
	else
		arg = compose_arg(&list,
				(unsigned int)(long)list->arg, precision, field);
	padd_digit(&list, arg, field,
		list->special != NULL && ft_strchr(list->special, '-') != NULL);
}
