/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlstsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:12:17 by sdincbud          #+#    #+#             */
/*   Updated: 2018/11/12 16:50:43 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(const char *str, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

static t_list	*ft_lstword(const char *str, char c, int *i)
{
	t_list	*list;
	char	*s;
	int		k;

	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
		return (NULL);
	k = 0;
	while (str[*i] != c && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while (str[*i] == c && str[*i])
		*i += 1;
	list = ft_lstnew(s, ft_strlen(s));
	return (list);
}

static char		*ft_word(const char *str, char c, int *i)
{
	char	*s;
	int		k;

	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
		return (NULL);
	k = 0;
	while (str[*i] != c && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while (str[*i] == c && str[*i])
		*i += 1;
	return (s);
}

t_list			*ft_strlstsplit(const char *str, char c)
{
	int		i;
	int		j;
	int		nbwrd;
	char	*s;
	t_list	*list;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	nbwrd = ft_count_words(str, c);
	while (str[i] == c && str[i])
		i++;
	while (j < nbwrd && str[i])
	{
		if (!j)
		{
			s = ft_word(str, c, &i);
			list = ft_lstnew(s, ft_strlen(s));
		}
		else
			ft_lstqueue(&list, ft_lstword(str, c, &i));
		j++;
	}
	return (list);
}
