/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:39:16 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/29 12:52:13 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strlenuni(wchar_t *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		handle_stringuni(t_lprintf *list)
{
	wchar_t		*arg;
	char		*ret;
	int			i;

	if (list->arg != NULL)
	{
		arg = (wchar_t *)list->arg;
		i = 0;
		ret = NULL;
		while (arg[i])
		{
			ret = ft_strjoin_free(ret, (char *)handle_unicode(arg[i]), 0);
			i++;
		}
		ret = ft_strjoin_free(ret, "", 1);
	}
	else
		ret = ft_strdup("(null)");
	list->to_swap = ret;
}

static char	*ft_hextostr(long hex)
{
	char	*base;
	char	*ret;
	long	tmp;
	int		power;

	tmp = hex;
	base = "0123456789abcdef";
	power = 0;
	while (tmp > 0)
	{
		tmp = tmp / 16;
		power++;
	}
	if (!(ret = malloc((sizeof(char) * power))))
		return (NULL);
	ret[power] = '\0';
	while (power > 0)
	{
		power--;
		ret[power] = base[hex % 16];
		hex = hex / 16;
	}
	return (ret);
}

static void	handle_pointer(t_lprintf *list)
{
	char	*ret;
	int		to_pad;

	ret = ft_hextostr((long)list->arg);
	if (list->arg == NULL && !list->precision)
		ret = ft_strjoin_free(ret, "0", 1);
	if ((ft_strchr(list->special, '0') && !ft_strchr(list->special, '-'))
		|| ft_strchr(list->precision, '.'))
	{
		if (ft_strchr(list->precision, '.'))
			to_pad = ft_atoi(list->dpp) - ft_strlen(ret);
		if (ft_strchr(list->special, '0'))
			to_pad = ft_atoi(list->field) - ft_strlen(ret) - 2;
		while (to_pad > 0)
		{
			ret = ft_strjoin_free("0", ret, 2);
			to_pad--;
		}
	}
	ret = ft_strjoin_free("0x", ret, 2);
	list->to_swap = ret;
}

void		handle_string(t_lprintf *list)
{
	if (ft_strchr(list->conversion, '%'))
		list->to_swap = ft_strdup("%");
	else if (ft_strchr(list->conversion, 's'))
	{
		if (list->dpp)
			list->to_swap = ft_strldup((char *)list->arg,
					ft_atoi(list->dpp));
		else if (list->arg == NULL)
			list->to_swap = ft_strdup("(null)");
		else
			list->to_swap = ft_strdup((char *)list->arg);
	}
	else if (ft_matcha(list->conversion, "Cc"))
		handle_char(list);
	else if (ft_strchr(list->conversion, 'p'))
		handle_pointer(list);
	else if (ft_strchr(list->conversion, 'S'))
		handle_stringuni(list);
	handle_padding(list);
}
