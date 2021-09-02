/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:23 by edjubert          #+#    #+#             */
/*   Updated: 2019/05/29 12:58:53 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_color_style(char *color_style)
{
	if (ft_strcmp(color_style, "{eoc}") == 0)
		return ("\033[0m");
	else if (ft_strcmp(color_style, "{black}") == 0)
		return ("\033[30m");
	else if (ft_strcmp(color_style, "{red}") == 0)
		return ("\033[91m");
	else if (ft_strcmp(color_style, "{green}") == 0)
		return ("\033[92m");
	else if (ft_strcmp(color_style, "{yellow}") == 0)
		return ("\033[93m");
	else if (ft_strcmp(color_style, "{blue}") == 0)
		return ("\033[34m");
	else if (ft_strcmp(color_style, "{magenta}") == 0)
		return ("\033[95m");
	else if (ft_strcmp(color_style, "{cyan}") == 0)
		return ("\033[96m");
	else if (ft_strcmp(color_style, "{bold}") == 0)
		return ("\033[1m");
	else if (ft_strcmp(color_style, "{underlined}") == 0)
		return ("\033[4m");
	else if (ft_strcmp(color_style, "{blink}") == 0)
		return ("\033[5m");
	else if (ft_strcmp(color_style, "{inverted}") == 0)
		return ("\033[7m");
	return (NULL);
}

static int	ft_check_color(char *str, char **color, int mode)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '}')
		i++;
	if (mode == 1)
		return (i);
	if (mode == 0)
	{
		*color = ft_strsub(str, 0, i + 1);
		if ((tmp = ft_color_style(*color)))
		{
			ft_strdel(color);
			*color = tmp;
			return (1);
		}
	}
	ft_strdel(color);
	return (0);
}

static int	ft_ended(char **taff, t_lprintf **list, int ret)
{
	t_lprintf	*tmp;
	int			size;
	int			error;

	tmp = *list;
	size = 0;
	error = 0;
	while (tmp)
	{
		if (tmp->error == 1)
			error = 1;
		if (ft_strchr(tmp->conversion, 'c'))
			if (tmp->arg == NULL)
				size++;
		if (ft_strchr(tmp->conversion, 'C'))
			if (ft_strlen(tmp->to_swap) == 0)
				size++;
		tmp = tmp->next;
	}
	ft_strdel(taff);
	ft_lst_del(list);
	if (error == 1)
		return (-1);
	else
		return (ret + size);
}

static int	toswap(char **taff, t_lprintf **list, int fd)
{
	t_lprintf	*tmp;
	char		*str;
	int			i;
	int			ret;

	str = *taff;
	tmp = *list;
	ret = 0;
	while (tmp && tmp->error != 1)
	{
		i = 0;
		while (str[i] != '%')
			i++;
		ret = ret + i + ft_strlen_pro(tmp->to_swap);
		write(fd, str, i);
		write(fd, tmp->to_swap, ft_strlen_swap(tmp));
		i = i + ft_strlen_pro(tmp->percent);
		str = &str[i];
		tmp = tmp->next;
	}
	if (!tmp)
		write(fd, str, ft_strlen_pro(str));
	ret += ft_strlen_pro(str);
	return (ft_ended(taff, list, ret));
}

int			ft_color(char *str, t_lprintf **list, int star)
{
	char	*color;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == '{')
		{
			if (ft_check_color(&str[i], &color, 0) == 1)
			{
				ret = ft_strjoin_free(ret, ft_strsub(str, star, i - star), 0);
				star = i + ft_check_color(&str[i], &color, 1) + 1;
				i = i + ft_check_color(&str[i], &color, 1);
				ret = ft_strjoin_free(ret, color, 1);
			}
		}
		i++;
	}
	ret = ft_strjoin_free(ret, ft_strsub(str, star, i - star), 0);
	return (toswap(&ret, list, (*list)->fd));
}
