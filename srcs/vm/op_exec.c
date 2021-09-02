/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:41:43 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/08 12:49:30 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	(*g_op_wrap[16])(t_vm*, t_proc**, t_type[]) =
{
	&op_live,
	&op_ld,
	&op_st,
	&op_add,
	&op_sub,
	&op_and,
	&op_or,
	&op_xor,
	&op_zjmp,
	&op_ldi,
	&op_sti,
	&op_fork,
	&op_lld,
	&op_lldi,
	&op_lfork,
	&op_aff
};

void		fill_16bit(uint32_t *arg, short index, unsigned char *arena)
{
	uint32_t	filled;
	uint32_t	tmp;

	filled = 0;
	tmp = arena[index % MEM_SIZE];
	filled |= tmp << 8;
	tmp = arena[(index + 1) % MEM_SIZE];
	filled |= tmp;
	*arg = filled;
}

void		fill_32bit(uint32_t *arg, short index, unsigned char *arena)
{
	uint32_t	filled;
	uint32_t	tmp;

	filled = 0;
	tmp = arena[index % MEM_SIZE];
	filled |= tmp << 24;
	tmp = arena[(index + 1) % MEM_SIZE];
	filled |= tmp << 16;
	tmp = arena[(index + 2) % MEM_SIZE];
	filled |= tmp << 8;
	tmp = arena[(index + 3) % MEM_SIZE];
	filled |= tmp;
	*arg = filled;
}

int			op_invalid_mask(t_vm *vm, t_proc *proc, t_op instruct)
{
	unsigned char	ocp;
	int				corrupt;

	ocp = vm->arena[(proc->pc + proc->start + 1) % MEM_SIZE];
	corrupt = 0;
	if ((ocp & 3) && instruct.num_args > 1)
		return (1);
	corrupt += check_ldstlld(ocp, instruct.opcode);
	corrupt += check_operations(ocp, instruct.opcode);
	corrupt += check_stildilldi(ocp, instruct.opcode);
	return (corrupt);
}

int			regchk(t_type args[], t_op instruct)
{
	int		i;

	i = -1;
	while (++i < instruct.num_args)
	{
		if (args[i].flag == T_REG)
		{
			if (args[i].data < 1 || args[i].data > REG_NUMBER)
				return (0);
		}
	}
	return (1);
}

void		op_exec(t_vm *vm, t_proc *proc, t_op instruct)
{
	t_type	args[instruct.num_args];
	int		i;
	short	index;

	i = -1;
	index = (proc->pc + proc->start + (instruct.args_mask ? 2 : 1)) % MEM_SIZE;
	if (op_invalid_mask(vm, proc, instruct))
		return ;
	while (++i < instruct.num_args)
	{
		if (instruct.args[i] == T_DIR)
			op_exec_dir(vm, &index, &args[i], instruct);
		else if (instruct.args[i] == T_IND)
			op_exec_ind(vm, &index, &args[i]);
		else if (instruct.args[i] == T_REG)
			op_exec_reg(vm, &index, &args[i]);
		else
		{
			args[i].data = 0;
			args[i].flag = 0;
		}
	}
	if (instruct.opcode > 0 && instruct.opcode < 17 && regchk(args, instruct))
		g_op_wrap[instruct.opcode - 1](vm, &proc, args);
}
