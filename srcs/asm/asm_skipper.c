/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_skipper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:00:49 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/10 12:30:20 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*skip_space_char(char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str == '\f'
		|| *str == '\n'))
		str++;
	return (str);
}

char	*skip_spaces_only(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

char	*skip_spaces_only_rev(char *ptr, char *str)
{
	str -= str > ptr ? 1 : 0;
	while (str > ptr && (*str == ' ' || *str == '\t'))
		str--;
	return (str);
}

char	*skip_useless(char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str == '\f'
		|| *str == '\n'))
		str++;
	if (*str && (*str == COMMENT_CHAR || *str == ';'))
		if (!(str = ft_strchr(str + 1, '\n')))
			str = str + ft_strlen(str);
	return (str);
}
