/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:56:15 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/09 15:56:59 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');
}

int		get_line(char *str, char *ptr)
{
	int line;

	line = 1;
	while (str < ptr)
	{
		str++;
		if (*(str - 1) == '\n')
			line++;
	}
	return (line);
}

int		get_row(char *str, char *ptr)
{
	int row;

	row = 1;
	while (str < ptr)
	{
		str++;
		row++;
		if (*(str - 1) == '\n')
			row = 1;
	}
	return (row);
}

char	*newline(char *str)
{
	while (*str && *str != '\n')
		str++;
	return (str);
}
