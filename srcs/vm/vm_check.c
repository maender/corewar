/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 11:22:11 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/11 18:00:18 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_defines(void)
{
	if (IND_SIZE != 2 || REG_SIZE != 4 || DIR_SIZE != 4)
		vm_error(0, NULL);
	if (IND_CODE != 3 || REG_CODE != 1 || DIR_CODE != 2)
		vm_error(0, NULL);
	if (MAX_ARGS_NUMBER != 4 || MAX_PLAYERS != 4 || MEM_SIZE != (4 * 1024))
		vm_error(0, NULL);
	if (IDX_MOD != ((4 * 1024) / 8) || CHAMP_MAX_SIZE != ((4 * 1024) / 6))
		vm_error(0, NULL);
	if (REG_NUMBER != 16 || REG_SIZE != 4 || COREWAR_EXEC_MAGIC != 0xea83f3)
		vm_error(0, NULL);
	if (PROG_NAME_LENGTH != (128) || COMMENT_LENGTH != (2048))
		vm_error(0, NULL);
	if (T_IND != 4 || T_DIR != 2 || T_REG != 1)
		vm_error(0, NULL);
	if (CYCLE_TO_DIE < 1 || CYCLE_TO_DIE > 2147483647
		|| CYCLE_DELTA >= CYCLE_TO_DIE)
		vm_error(0, NULL);
}
