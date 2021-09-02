/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:26:36 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/08 18:56:45 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_fork(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc	*tmp;
	t_proc	*new;
	int		reg;

	reg = -1;
	tmp = *proc;
	new = malloc_proc();
	while (++reg < REG_NUMBER)
		new->reg[reg] = tmp->reg[reg];
	new->carry = tmp->carry;
	new->cycle = tmp->cycle;
	new->pc = tmp->pc + (short)args[0].data % IDX_MOD;
	while (tmp->start + new->pc < 0)
		new->pc += MEM_SIZE;
	while (tmp->start + new->pc >= MEM_SIZE)
		new->pc -= MEM_SIZE;
	new->live = tmp->live;
	new->next = NULL;
	new->player = tmp->player;
	new->start = tmp->start;
	vm->pnum++;
	push_proc_front(&(vm->proc), new);
}

void	op_lfork(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc	*tmp;
	t_proc	*new;
	int		reg;

	reg = -1;
	tmp = *proc;
	new = malloc_proc();
	while (++reg < REG_NUMBER)
		new->reg[reg] = tmp->reg[reg];
	new->carry = tmp->carry;
	new->cycle = tmp->cycle;
	new->pc = tmp->pc + (short)args[0].data;
	while (tmp->start + new->pc < 0)
		new->pc += MEM_SIZE;
	while (tmp->start + new->pc >= MEM_SIZE)
		new->pc -= MEM_SIZE;
	new->live = tmp->live;
	new->next = NULL;
	new->player = tmp->player;
	new->start = tmp->start;
	vm->pnum++;
	push_proc_front(&(vm->proc), new);
}
