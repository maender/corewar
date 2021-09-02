/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 12:23:34 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 15:07:28 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	join_free_loop(char **ret, int length, t_lprintf **list)
{
	int	i;

	if (ft_strchr((*list)->special, '0') && (int)(long)(*list)->arg == 0)
		i = -1;
	else if (ft_strchr((*list)->special, '0'))
		i = 1;
	else
		i = -1;
	while (++i < length)
		*ret = ft_strjoin_free(*ret, "0", 1);
}

static void	field_and_precision(t_lprintf **list,
	char **ret, int field, char *arglength)
{
	int	precision;

	precision = (*list)->dpp ? ft_atoi((*list)->dpp) : 0;
	if (ft_strchr((*list)->special, '0') != NULL && precision == 0
		&& ft_strchr((*list)->special, '-') == NULL)
		join_free_loop(ret, field - (int)ft_strlen_pro(arglength), list);
	else if (precision > 0)
		join_free_loop(ret, precision - (int)ft_strlen_pro(arglength), list);
}

static char	*hcompose_arg(t_lprintf **lst, int field, int ischar, char *ret)
{
	char	capital;
	char	*ox;
	char	*arglength;
	int		base;

	capital = ft_strchr((*lst)->conversion, 'x') ? 'a' : 'A';
	if (ft_matcha((*lst)->conversion, "xX"))
		ox = capital == 'A' ? "0X" : "0x";
	else
		ox = "0";
	base = ft_matcha((*lst)->conversion, "o") ? 8 : 16;
	arglength = ft_utoa_base(ischar ? (unsigned char)(long)(*lst)->arg
			: (unsigned short)(long)(*lst)->arg, base, capital);
	if (ft_strchr((*lst)->special, '#') != NULL && (int)(long)(*lst)->arg)
		ret = ft_strjoin_free(ret, ox, 1);
	field_and_precision(lst, &ret, field, arglength);
	if (!ft_strchr((*lst)->special, '#') && ft_atoi((*lst)->dpp) == 0
		&& ft_strchr((*lst)->special, '0' && ft_strchr((*lst)->special, '-')))
		ret = ft_strjoin_free(ret, "00", 1);
	ret = ft_strjoin_free(ret, ft_utoa_base(ischar
				? (unsigned char)(long)(*lst)->arg
				: (unsigned short)(long)(*lst)->arg, base, capital), 0);
	ft_strdel(&arglength);
	return (ret);
}

static char	*lcompose_arg(t_lprintf **list, int field, int islong, char *ret)
{
	char	capital;
	char	*ox;
	char	*arglength;
	int		base;

	capital = ft_strchr((*list)->conversion, 'x') ? 'a' : 'A';
	if (ft_matcha((*list)->conversion, "xX"))
		ox = capital == 'A' ? "0X" : "0x";
	else
		ox = "0";
	base = ft_matcha((*list)->conversion, "o") ? 8 : 16;
	arglength = ft_utoa_base(islong ? (u_int64_t)(*list)->arg
			: (unsigned int)(long)(*list)->arg, base, capital);
	if (ft_strchr((*list)->special, '#') != NULL
		&& (int)(long)(*list)->arg != 0)
		ret = ft_strjoin_free(ret, ox, 1);
	field_and_precision(list, &ret, field, arglength);
	if (!ft_strchr((*list)->special, '#') && ft_strchr((*list)->special, '0')
		&& !ft_strchr((*list)->special, '-') && ft_atoi((*list)->dpp) == 0)
		ret = ft_strjoin_free(ret, "00", 1);
	ret = ft_strjoin_free(ret, ft_utoa_base(islong ? (u_int64_t)(*list)->arg
				: (unsigned int)(long)(*list)->arg, base, capital), 0);
	ft_strdel(&arglength);
	return (ret);
}

void		handle_base(t_lprintf *lst)
{
	int		precision;
	int		field;
	char	*arg;

	precision = lst->dpp != NULL ? ft_atoi(lst->dpp) : 0;
	field = lst->field != NULL ? ft_atoi(lst->field) : 0;
	if (lst->modifier
		&& (ft_match(lst->modifier, "l") || ft_match(lst->modifier, "ll")))
		arg = lcompose_arg(&lst, field, 1, NULL);
	else if (lst->modifier && ft_match(lst->modifier, "hh"))
		arg = hcompose_arg(&lst, field, 1, NULL);
	else if (lst->modifier && ft_match(lst->modifier, "h"))
		arg = hcompose_arg(&lst, field, 0, NULL);
	else
		arg = lcompose_arg(&lst, field, 0, NULL);
	if (ft_strchr(lst->precision, '.') != NULL && precision == 0
		&& (unsigned int)(long)lst->arg == 0
		&& (ft_strchr(lst->conversion, 'o') && !ft_strchr(lst->special, '#')))
		arg = ft_strsub_free(arg, ft_strlen_pro(arg), ft_strlen_pro(arg));
	else if (ft_strchr(lst->precision, '.') != NULL
		&& precision == 0 && (unsigned int)(long)lst->arg == 0
		&& !ft_strchr(lst->conversion, 'o'))
		arg = ft_strsub_free(arg, ft_strlen_pro(arg), ft_strlen_pro(arg));
	padd_digit(&lst, arg, field,
		lst->special != NULL && ft_strchr(lst->special, '-') != NULL);
}
