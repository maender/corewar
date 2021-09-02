/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:24:45 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/07 12:41:46 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_add(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc	*tmp;

	tmp = *proc;
	(void)vm;
	if ((args[0].data > REG_NUMBER || args[0].data < 1)
			|| (args[1].data > REG_NUMBER || args[1].data < 1)
			|| (args[2].data > REG_NUMBER || args[2].data < 1))
		return ;
	tmp->reg[args[2].data - 1] = tmp->reg[args[0].data - 1]
		+ tmp->reg[args[1].data - 1];
	tmp->carry = tmp->reg[args[2].data - 1] ? 0 : 1;
}

void	op_sub(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc	*tmp;

	tmp = *proc;
	(void)vm;
	if ((args[0].data > REG_NUMBER || args[0].data < 1)
			|| (args[1].data > REG_NUMBER || args[1].data < 1)
			|| (args[2].data > REG_NUMBER || args[2].data < 1))
		return ;
	tmp->reg[args[2].data - 1] = tmp->reg[args[0].data - 1]
		- tmp->reg[args[1].data - 1];
	tmp->carry = tmp->reg[args[2].data - 1] ? 0 : 1;
}

void	op_and(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc			*tmp;
	short			index;

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
	else if (args[1].flag == T_IND)
	{
		index = get_index(tmp, args[1].data);
		fill_32bit(&args[1].data, index, vm->arena);
	}
	tmp->reg[args[2].data - 1] = args[0].data & args[1].data;
	tmp->carry = tmp->reg[args[2].data - 1] ? 0 : 1;
}

void	op_or(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc			*tmp;
	short			index;

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
	else if (args[1].flag == T_IND)
	{
		index = get_index(tmp, args[1].data);
		fill_32bit(&args[1].data, index, vm->arena);
	}
	tmp->reg[args[2].data - 1] = args[0].data | args[1].data;
	tmp->carry = tmp->reg[args[2].data - 1] ? 0 : 1;
}

void	op_xor(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc			*tmp;
	short			index;

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
	else if (args[1].flag == T_IND)
	{
		index = get_index(tmp, args[1].data);
		fill_32bit(&args[1].data, index, vm->arena);
	}
	tmp->reg[args[2].data - 1] = args[0].data ^ args[1].data;
	tmp->carry = tmp->reg[args[2].data - 1] ? 0 : 1;
}
