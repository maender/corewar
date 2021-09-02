/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_title.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:43 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_ret(char **ret, char ***taff)
{
	char **title;

	title = *taff;
	*ret = ft_strjoin_free(*ret, title[0], 0);
	*ret = ft_strjoin_free(*ret, "\n", 1);
	*ret = ft_strjoin_free(*ret, title[1], 0);
	*ret = ft_strjoin_free(*ret, "\n", 1);
	*ret = ft_strjoin_free(*ret, title[2], 0);
	*ret = ft_strjoin_free(*ret, "\n", 1);
	*ret = ft_strjoin_free(*ret, title[3], 0);
	*ret = ft_strjoin_free(*ret, "\n", 1);
	*ret = ft_strjoin_free(*ret, title[4], 0);
	*ret = ft_strjoin_free(*ret, "\n", 1);
	free(*taff);
}

void			handle_title(t_lprintf *list)
{
	char	*str;
	char	*ret;
	char	**title;
	int		i;

	str = (char *)list->arg;
	ret = ft_strdup("\n");
	title = malloc(sizeof(char *) * 5);
	title[0] = NULL;
	title[1] = NULL;
	title[2] = NULL;
	title[3] = NULL;
	title[4] = NULL;
	i = 0;
	while (str[i])
	{
		ft_add(str[i], &title);
		i++;
	}
	ft_ret(&ret, &title);
	list->to_swap = ret;
}
