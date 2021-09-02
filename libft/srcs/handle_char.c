/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:32 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 15:09:30 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strlen_swap(t_lprintf *list)
{
	int		i;

	i = 0;
	while ((list->to_swap)[i])
		i++;
	if (ft_strchr(list->conversion, 'c'))
		if (list->arg == NULL)
			i++;
	if (ft_strchr(list->conversion, 'C'))
		if (ft_strlen(list->to_swap) == 0)
			i++;
	return (i);
}

void			handle_char(t_lprintf *list)
{
	unsigned char	*ret;

	ret = NULL;
	if (ft_strchr(list->conversion, 'c'))
	{
		if (!(ret = malloc(sizeof(unsigned char) * 2)))
			return ;
		if (list->modifier && ft_strcmp(list->modifier, "l") == 0)
		{
			if ((long)list->arg < 0 || (long)list->arg > 255)
			{
				list->error = 1;
				ret[0] = '\0';
			}
			else
				ret[0] = (long)list->arg;
		}
		else
			ret[0] = (unsigned char)(long)list->arg;
		ret[1] = '\0';
	}
	else if (ft_strchr(list->conversion, 'C'))
		ret = handle_unicode((wchar_t)((long)list->arg));
	list->to_swap = (char *)ret;
}
