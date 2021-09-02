/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:41:18 by fldoucet          #+#    #+#             */
/*   Updated: 2019/08/10 16:21:11 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		help_encoded(t_op *instruction, char byte[3], int i, int *test)
{
	if (byte[i] == REG_CODE)
	{
		instruction->args[*test] = T_REG;
		*test = *test + 1;
		return (1);
	}
	else if (byte[i] == DIR_CODE)
	{
		instruction->args[*test] = T_DIR;
		*test = *test + 1;
		return (instruction->carry ? 2 : 4);
	}
	else if (byte[i] == IND_CODE)
	{
		instruction->args[*test] = T_IND;
		*test = *test + 1;
		return (2);
	}
	return (0);
}

int		get_size(unsigned char *instruct, t_op *instruction)
{
	char			byte[3];
	int				size;
	int				i;
	int				test;

	if (instruct[0] == 1)
		return (5);
	else if (instruct[0] == 9 || instruct[0] == 12 || instruct[0] == 15)
		return (3);
	size = 0;
	test = 0;
	byte[0] = (instruct[1] >> 6) & 3;
	byte[1] = (instruct[1] >> 4) & 3;
	byte[2] = (instruct[1] >> 2) & 3;
	i = 0;
	while (i < instruction->num_args)
	{
		size = size + help_encoded(instruction, byte, i, &test);
		i++;
	}
	return (size + 2);
}

void	get_instructions_bis(t_vm *vm, t_proc *tmp, t_op instruction, int size)
{
	if (tmp->cycle == 0)
		tmp->cycle = instruction.num_cycles;
	tmp->cycle = tmp->cycle - 1 >= 0 ? tmp->cycle - 1 : 0;
	if (tmp->cycle == 0)
	{
		op_exec(vm, tmp, instruction);
		if (instruction.opcode != 9)
		{
			tmp->pc += size;
			if (tmp->start + tmp->pc >= MEM_SIZE)
				tmp->pc -= MEM_SIZE;
		}
	}
}

void	get_instructions(t_vm *vm, t_proc **pc)
{
	t_proc			*tmp;
	t_op			instruction;
	int				size;

	tmp = *pc;
	while (tmp)
	{
		instruction = get_op_tab(vm->arena[(tmp->start
					+ tmp->pc) % MEM_SIZE] - 1);
		size = get_size(&vm->arena[(tmp->pc + tmp->start)
				% MEM_SIZE], &instruction);
		if (instruction.opcode <= 0 || instruction.opcode > 16)
		{
			tmp->pc++;
			if (tmp->start + tmp->pc >= MEM_SIZE)
				tmp->pc -= MEM_SIZE;
			tmp = tmp->next;
			continue ;
		}
		get_instructions_bis(vm, tmp, instruction, size);
		tmp = tmp->next;
	}
}
