/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unicode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:51:05 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	*trans(char **to_trans, int byte)
{
	unsigned char	*ret;
	char			*bintmp;
	char			*str;
	int				i;
	int				j;

	str = *to_trans;
	if (!(ret = malloc(sizeof(unsigned char) * byte + 1)))
		return (NULL);
	i = 0;
	j = 0;
	ret[byte] = '\0';
	while (j < byte)
	{
		bintmp = ft_strsub(str, i, 8);
		ret[j] = ft_bindec(bintmp);
		ft_strdel(&bintmp);
		i = i + 8;
		j++;
	}
	ft_strdel(to_trans);
	return (ret);
}

unsigned char	*twob_unicode(char **bin)
{
	char	*mask;
	char	*str;
	int		i;
	int		j;

	str = *bin;
	j = ft_strlen(str) - 1;
	mask = ft_strdup("110xxxxx10xxxxxx");
	i = ft_strlen(mask) - 1;
	while (i > 0)
	{
		if (mask[i] == 'x')
		{
			if (j >= 0)
				mask[i] = str[j--];
			else
				mask[i] = '0';
		}
		i--;
	}
	ft_strdel(bin);
	return (trans(&mask, 2));
}

unsigned char	*threeb_unicode(char **bin)
{
	char	*mask;
	char	*str;
	int		i;
	int		j;

	str = *bin;
	j = ft_strlen(str) - 1;
	mask = ft_strdup("1110xxxx10xxxxxx10xxxxxx");
	i = ft_strlen(mask) - 1;
	while (i > 0)
	{
		if (mask[i] == 'x')
		{
			if (j >= 0)
				mask[i] = str[j--];
			else
				mask[i] = '0';
		}
		i--;
	}
	ft_strdel(bin);
	return (trans(&mask, 3));
}

unsigned char	*fourb_unicode(char **bin)
{
	char	*mask;
	char	*str;
	int		i;
	int		j;

	str = *bin;
	j = ft_strlen(str) - 1;
	mask = ft_strdup("11110xxx10xxxxxx10xxxxxx10xxxxxx");
	i = ft_strlen(mask) - 1;
	while (i > 0)
	{
		if (mask[i] == 'x')
		{
			if (j >= 0)
				mask[i] = str[j--];
			else
				mask[i] = '0';
		}
		i--;
	}
	ft_strdel(bin);
	return (trans(&mask, 4));
}

unsigned char	*handle_unicode(wchar_t unichar)
{
	char			*bin;
	unsigned char	*ret;

	bin = ft_itoa_base(unichar, 2, 'a');
	if (ft_strlen(bin) <= 7)
	{
		if (!(ret = malloc(sizeof(unsigned char) * 2)))
			return (NULL);
		ret[0] = (unsigned char)unichar;
		ret[1] = '\0';
		ft_strdel(&bin);
		return (ret);
	}
	else if (ft_strlen(bin) <= 11)
		return (twob_unicode(&bin));
	else if (ft_strlen(bin) <= 16)
		return (threeb_unicode(&bin));
	else
		return (fourb_unicode(&bin));
}
