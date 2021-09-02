/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:14 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/16 16:12:08 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parse_spec(t_lprintf *list)
{
	char	*str;
	int		start;
	int		i;

	str = list->percent;
	i = 1;
	start = i;
	if (str[1] == '#' || str[1] == '0' || str[1] == '-' || str[1] == ' '
		|| str[1] == '+' || str[1] == '\'')
	{
		while (str[i] == '#' || str[i] == '0' || str[i] == '-' || str[i] == ' '
			|| str[i] == '+' || str[i] == '\'')
			i++;
		list->special = ft_strsub(str, start, (i - start));
		return (i);
	}
	return (1);
}

static int	ft_parse_field(t_lprintf *list, int i)
{
	char	*str;
	int		start;

	str = list->percent;
	start = i;
	if (str[i] > 47 && str[i] < 58)
	{
		while (str[i] > 47 && str[i] < 58)
			i++;
		list->field = ft_strsub(str, start, (i - start));
	}
	if (str[i] == '.')
	{
		while (str[i] == '.')
			i++;
		list->precision = ft_strdup(".");
		start = i;
		while (str[i] > 47 && str[i] < 58)
			i++;
		list->dpp = ft_strsub(str, start, (i - start));
	}
	return (i);
}

static int	ft_parse_modifier(t_lprintf *list, int i)
{
	char	*str;
	int		start;

	str = list->percent;
	start = i;
	if (str[i] == 'h' && str[i + 1] == 'h')
	{
		list->modifier = ft_strdup("hh");
		return (i + 2);
	}
	else if (str[i] == 'l' && str[i + 1] == 'l')
	{
		list->modifier = ft_strdup("ll");
		return (i + 2);
	}
	else if (str[i] == 'h' || str[i] == 'l' || str[i] == 'j'
		|| str[i] == 't' || str[i] == 'z' || str[i] == 'q'
		|| str[i] == 'L')
	{
		list->modifier = ft_strsub(str, start, 1);
		return (i + 1);
	}
	return (i);
}

static int	ft_parse_conversion(t_lprintf *list, int i)
{
	char	*str;
	int		start;

	str = list->percent;
	while (str[i] && str[i] != 'd' && str[i] != 'i' && str[i] != 'o'
		&& str[i] != 'u' && str[i] != 'x' && str[i] != 'X' && str[i] != 'e'
		&& str[i] != 'f' && str[i] != 'g' && str[i] != 'a' && str[i] != 'c'
		&& str[i] != 's' && str[i] != 'p' && str[i] != 'n' && str[i] != '%'
		&& str[i] != 'b' && str[i] != 'f' && str[i] != 'T' && str[i] != 'C'
		&& str[i] != 'w' && str[i] != 'S')
		i++;
	start = i;
	if (str[i] && (str[i] == 'd' || str[i] == 'i' || str[i] == 'o'
			|| str[i] == 'u' || str[i] == 'x' || str[i] == 'X' || str[i] == 'e'
			|| str[i] == 'e' || str[i] == 'f' || str[i] == 'g' || str[i] == 'a'
			|| str[i] == 'c' || str[i] == 's' || str[i] == 'p' || str[i] == 'n'
			|| str[i] == '%' || str[i] == 'b' || str[i] == 'f' || str[i] == 'T'
			|| str[i] == 'C' || str[i] == 'w' || str[i] == 'S'))
		list->conversion = ft_strsub(str, start, 1);
	else
		list->conversion = ft_strdup("");
	return (0);
}

int			ft_parse(t_lprintf **list, char *format)
{
	t_lprintf	*tmp;
	int			i;

	tmp = *list;
	while (tmp)
	{
		i = ft_parse_spec(tmp);
		i = ft_parse_field(tmp, i);
		i = ft_parse_modifier(tmp, i);
		ft_parse_conversion(tmp, i);
		tmp = tmp->next;
	}
	ft_check(list);
	if (*list == NULL)
	{
		write(1, format, ft_strlen(format));
		return (ft_strlen(format));
	}
	else
		return (ft_choose(format, list));
}
