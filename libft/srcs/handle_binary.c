/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:59:03 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/16 16:13:34 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*compose_arg(t_lprintf **list, int arg,
						int precision, int field)
{
	int		i;
	char	*ret;
	char	*arglength;

	i = 0;
	ret = NULL;
	arglength = ft_itoa_base(arg, 2, 'a');
	if (ft_strchr((*list)->special, '0') != NULL && precision == 0
		&& ft_strchr((*list)->special, '-') == NULL)
		while (i++ < field - (int)ft_strlen(arglength))
			ret = ft_strjoin_free(ret, "0", 1);
	else if (precision > 0)
		while (i++ < precision - (int)ft_strlen(arglength))
			ret = ft_strjoin_free(ret, "0", 1);
	ret = ft_strjoin_free(ret, ft_itoa_base(arg, 2, 'a'), 0);
	ft_strdel(&arglength);
	return (ret);
}

void		handle_binary(t_lprintf *list)
{
	int		precision;
	int		field;
	char	*arg;

	precision = list->dpp != NULL ? ft_atoi(list->dpp) : 0;
	field = list->field != NULL ? ft_atoi(list->field) : 0;
	arg = compose_arg(&list, (int)(long)list->arg, precision, field);
	if (list->special != NULL && ft_strchr(list->special, '-') != NULL)
		padd_digit(&list, arg, field, 1);
	else
		padd_digit(&list, arg, field, 0);
}
