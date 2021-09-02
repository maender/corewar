/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ocp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 12:46:02 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/09 13:43:03 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_ldstlld(unsigned char ocp, int opcode)
{
	if (opcode != 2 && opcode != 3 && opcode != 13)
		return (0);
	if (opcode == 2 || opcode == 13)
		if (ocp != 144 && ocp != 208)
			return (1);
	if (opcode == 3)
		if (ocp != 112 && ocp != 80)
			return (1);
	return (0);
}

int		check_stildilldi(unsigned char ocp, int opcode)
{
	if (opcode != 11 && opcode != 10 && opcode != 14)
		return (0);
	if (opcode == 11)
		if (ocp != 164 && ocp != 228 && ocp != 116 && ocp != 180 && ocp
			!= 244 && ocp != 88 && ocp != 152 && ocp != 216 && ocp != 104
			&& ocp != 168 && ocp != 232 && ocp != 120 && ocp != 184 && ocp
			!= 248 && ocp != 100 && ocp != 212 && ocp != 148 && ocp != 84)
			return (1);
	if (opcode == 10)
		if (ocp != 84 && ocp != 148 && ocp != 212 && ocp != 100 && ocp
			!= 164 && ocp != 228)
			return (1);
	if (opcode == 14)
		if (ocp != 84 && ocp != 148 && ocp != 212 && ocp != 100 && ocp
			!= 164 && ocp != 228 && ocp != 88 && ocp != 152 && ocp != 216
			&& ocp != 104 && ocp != 168 && ocp != 232)
			return (1);
	return (0);
}

int		check_operations(unsigned char ocp, int opcode)
{
	if (opcode < 4 || opcode > 8)
		return (0);
	if (opcode == 4 || opcode == 5)
		if (ocp != 84)
			return (1);
	if (opcode == 6 || opcode == 7 || opcode == 8)
		if (ocp != 148 && ocp != 212 && ocp != 100 && ocp != 164 && ocp
			!= 228 && ocp != 116 && ocp != 180 && ocp != 244 && ocp
			!= 84)
			return (1);
	return (0);
}
