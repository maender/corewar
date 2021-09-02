/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi_lldi_st.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:22:12 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/08 19:00:45 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ldi(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc	*tmp;
	short	index;

	tmp = *proc;
	if (args[0].flag == T_REG)
		args[0].data = tmp->reg[args[0].data - 1];
	else if (args[0].flag == T_IND)
	{
		index = get_index(tmp, args[0].data);
		fill_32bit(&args[0].data, index, vm->arena);
	}
	if (args[1].flag == T_REG)
		args[1].data = tmp->reg[args[1].data - 1];
	index = (tmp->start + tmp->pc + (short)(args[1].data
			+ args[0].data) % IDX_MOD) % MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	fill_32bit(&tmp->reg[args[2].data - 1], index, vm->arena);
}

void	op_lldi(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc	*tmp;
	short	index;

	tmp = *proc;
	if (args[0].flag == T_REG)
		args[0].data = tmp->reg[args[0].data - 1];
	else if (args[0].flag == T_IND)
	{
		index = get_index(tmp, args[0].data);
		fill_32bit(&args[0].data, index, vm->arena);
	}
	if (args[1].flag == T_REG)
		args[1].data = tmp->reg[args[1].data - 1];
	index = tmp->start + tmp->pc + (short)(args[1].data + args[0].data);
	index = index % MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	fill_32bit(&tmp->reg[args[2].data - 1], index, vm->arena);
	tmp->carry = tmp->reg[args[2].data - 1] ? 0 : 1;
}

void	op_st(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc			*tmp;
	short			index;

	tmp = *proc;
	index = 0;
	args[0].data = tmp->reg[args[0].data - 1];
	if (args[1].flag == T_REG)
		tmp->reg[args[1].data - 1] = args[0].data;
	else
	{
		index = (tmp->start + tmp->pc + (short)args[1].data % IDX_MOD)
			% MEM_SIZE;
		while (index < 0)
			index += MEM_SIZE;
		push_color(vm->colors, index, 4, tmp->player);
		vm->arena[index % MEM_SIZE] = args[0].data >> 24;
		vm->arena[(index + 1) % MEM_SIZE] = args[0].data >> 16;
		vm->arena[(index + 2) % MEM_SIZE] = args[0].data >> 8;
		vm->arena[(index + 3) % MEM_SIZE] = args[0].data;
	}
	*proc = tmp;
}
