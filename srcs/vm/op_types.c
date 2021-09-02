/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_types.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:18:48 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/08 10:22:48 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_exec_dir(t_vm *vm, short *index, t_type *arg, t_op instruct)
{
	if (instruct.carry)
		fill_16bit(&(arg->data), *index, vm->arena);
	else
		fill_32bit(&(arg->data), *index, vm->arena);
	*index = instruct.carry ? *index + 2 : *index + 4;
	arg->flag = T_DIR;
}

void	op_exec_ind(t_vm *vm, short *index, t_type *arg)
{
	fill_16bit(&(arg->data), *index, vm->arena);
	*index += 2;
	arg->flag = T_IND;
}

void	op_exec_reg(t_vm *vm, short *index, t_type *arg)
{
	arg->data = (uint8_t)vm->arena[*index % MEM_SIZE];
	*index += 1;
	arg->flag = T_REG;
}
