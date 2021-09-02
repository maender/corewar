/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:49:59 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/16 16:02:13 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	no_problemo(t_lprintf **taff)
{
	t_lprintf	*list;
	t_lprintf	*tmp;
	void		*tmp2;
	void		*tmp3;

	list = *taff;
	while (list)
	{
		if (ft_strchr(list->conversion, '%') && list->arg != NULL)
		{
			tmp = list;
			tmp3 = list->arg;
			while (list && list->next)
			{
				tmp2 = tmp3;
				tmp3 = list->next->arg;
				list = list->next;
				list->arg = tmp2;
			}
			tmp->arg = NULL;
			list = *taff;
		}
		list = list->next;
	}
}

int			ft_25line(char c)
{
	if (c != '#' && c != '0' && c != '-' && c != ' '
		&& c != '+' && c != '\''
		&& (c < 48 || c > 57) && c != '.'
		&& c != 'h' && c != 'l' && c != 'd'
		&& c != 'i' && c != 'o' && c != 'u'
		&& c != 'x' && c != 'X' && c != 'f'
		&& c != 'c' && c != 's' && c != 'p'
		&& c != '%' && c != 'j' && c != 't'
		&& c != 'z' && c != 'q' && c != 'b'
		&& c != 'f' && c != 'L' && c != 'T'
		&& c != 'C' && c != 'w' && c != 'S')
		return (0);
	return (1);
}

static int	ft_check_percent(t_lprintf *list)
{
	char	*str;
	int		i;

	i = 0;
	str = list->percent;
	while (str[i])
	{
		if (ft_25line(str[i]) == 0)
		{
			ft_strdel(&list->conversion);
			list->conversion = ft_strdup("42");
			ft_strdel(&list->percent);
			list->percent = ft_strsub(str, 0, i);
		}
		i++;
	}
	if (ft_strlen_pro(list->conversion) == 0)
	{
		ft_strdel(&list->conversion);
		list->conversion = ft_strdup("42");
		ft_strdel(&list->percent);
		list->percent = ft_strsub(str, 0, i);
	}
	return (0);
}

void		ft_check(t_lprintf **list)
{
	t_lprintf	*tmp;
	int			fd;

	fd = 0;
	tmp = *list;
	while (tmp)
	{
		if (ft_strchr(tmp->conversion, 'w'))
		{
			tmp->to_swap = ft_strdup("");
			fd = (int)(long)tmp->arg;
		}
		ft_check_percent(tmp);
		tmp = tmp->next;
	}
	if (fd != 0)
	{
		tmp = *list;
		while (tmp)
		{
			tmp->fd = fd;
			tmp = tmp->next;
		}
	}
	no_problemo(list);
}
