/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:23:50 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/29 11:37:55 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_conversion(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X'
		|| c == 'c' || c == 's' || c == 'p' || c == 'f' || c == '%' || c == 'b'
		|| c == 'T' || c == 'f' || c == 'C' || c == 'w' || c == 'S')
		return (1);
	else
		return (0);
}

static int		ft_correct_percent(char **percent)
{
	char	*tmp;
	int		i;

	tmp = *percent;
	i = 0;
	while (tmp[i])
	{
		if (ft_25line(tmp[i]) == 0)
		{
			ft_strdel(percent);
			*percent = ft_strsub(tmp, 0, ft_strlen(tmp) - 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

static void		is_float(char *percent, t_lprintf **list, va_list args)
{
	if (ft_strchr(percent, 'f'))
	{
		if (ft_strchr(percent, 'L'))
			ft_init_float_long(percent, list, va_arg(args, long double));
		else
			ft_init_float(percent, list, va_arg(args, double));
	}
	else
		ft_init(percent, list, va_arg(args, void*));
}

int				ft_printf(const char *restrict format, ...)
{
	va_list		args;
	char		*percent;
	int			i;
	int			start;
	t_lprintf	*list;

	va_start(args, format);
	i = -1;
	list = NULL;
	while (++i < (int)ft_strlen(format))
	{
		if (format[i] == '%')
		{
			start = i++;
			while (format[i] && ft_is_conversion(format[i]) == 0)
				i++;
			percent = ft_strsub(format, start, (i - start) + 1);
			if (percent[ft_strlen(percent) - 1] == '%'
				&& percent[ft_strlen(percent) - 2] != '%')
				i = i + ft_correct_percent(&percent);
			is_float(percent, &list, args);
		}
	}
	va_end(args);
	return (ft_parse(&list, (char *)format));
}
