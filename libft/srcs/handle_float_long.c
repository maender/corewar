/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_float_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:49:20 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/29 12:51:06 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_round(long double arg, char **ret,
							int precision, char *special)
{
	unsigned long long	uarg;

	uarg = ft_dneg(arg)
		? (unsigned long long)(arg * -1) : (unsigned long long)arg;
	if (ft_strchr(special, ' ') && !ft_strchr(special, '+') && !ft_dneg(arg))
		*ret = ft_strjoin_free(*ret, " ", 1);
	else if (ft_strchr(special, '+') && !ft_dneg(arg))
		*ret = ft_strjoin_free(*ret, "+", 1);
	else if (ft_dneg(arg))
		*ret = ft_strjoin_free(*ret, "-", 1);
	if ((unsigned long long)((uarg - uarg) * 10) % 10 >= 5 && precision <= 0)
		*ret = ft_strjoin_free(*ret, ft_utoa_long(uarg + 1), 0);
	else
		*ret = ft_strjoin_free(*ret, ft_utoa_long(uarg), 0);
	if (precision > 0 || ft_strchr(special, '#'))
		*ret = ft_strjoin_free(*ret, ".", 1);
}

static void	rewrite(char *tmp, int precision, char **ret)
{
	if ((int)ft_strlen_pro(tmp) == 0)
		while (precision--)
			*ret = ft_strjoin_free(*ret, "0", 1);
	if (tmp && !ft_strcmp(tmp, "1"))
		tmp = ft_strsub_free(tmp, 0, 0);
	if (tmp)
		*ret = ft_strjoin_free(*ret, tmp, 0);
}

static void	round_up(long double arg, char **ret,
							int precision, t_lprintf **list)
{
	unsigned long long	decimal;
	char				*tmp;

	decimal = (unsigned long long)((ft_dabs(arg)
				- (unsigned long long)(ft_dabs(arg)))
			* ft_pow(10, precision + 1));
	decimal = decimal % 10 > 4 ? decimal / 10 + 1 : decimal / 10;
	tmp = NULL;
	while (decimal)
	{
		tmp = ft_strjoin_free(tmp, ft_utoa_long(decimal % 10), 0);
		decimal /= 10;
	}
	ft_strrev(tmp);
	if ((int)ft_strlen_pro(tmp) > precision && precision >= 0)
	{
		ft_strdel(ret);
		arg < 0
			? check_round(arg - 1, ret, precision, (*list)->special)
			: check_round(arg + 1, ret, precision, (*list)->special);
		tmp = ft_strsub_free(tmp, 1, precision);
	}
	rewrite(tmp, precision, ret);
}

void		handle_float_long(t_lprintf *list)
{
	int		precision;
	int		field;
	char	*arg;
	char	*mask;
	char	*cmp;

	arg = NULL;
	mask = "0111111111111100000000000000000000000000000000000000000000000000";
	precision = list->dpp != NULL ? ft_atoi(list->dpp) : 6;
	field = list->field != NULL ? ft_atoi(list->field) : 0;
	cmp = ft_dtob((long double)list->f);
	check_round(!ft_strcmp(mask, cmp)
		? 0.0L : (long double)list->lf, &arg, precision, list->special);
	round_up(!ft_strcmp(mask, cmp)
		? 0.0L : (long double)list->lf, &arg, precision, &list);
	if (list->special != NULL && ft_strchr(list->special, '-') != NULL)
		padd_digit(&list, arg, field, 1);
	else
		padd_digit(&list, arg, field, 0);
	ft_strdel(&cmp);
}
