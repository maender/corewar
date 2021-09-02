/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 12:20:01 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/10 17:00:07 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_colors(t_color colors[MEM_SIZE])
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		colors[i].opcode = 0;
		colors[i].lastchamp = 0;
		colors[i].champ = 7;
		colors[i].time = 0;
		colors[i].t = 0;
		i++;
	}
}

void	push_color(t_color colors[MEM_SIZE], int index, int length, int champ)
{
	int		i;

	i = 0;
	while (i < length)
	{
		colors[(index + i) % MEM_SIZE].lastchamp = colors[index + i].champ;
		colors[(index + i) % MEM_SIZE].champ = champ;
		colors[(index + i) % MEM_SIZE].opcode = length;
		colors[(index + i) % MEM_SIZE].time = length > 4 ? 0 : 100;
		i++;
	}
}
